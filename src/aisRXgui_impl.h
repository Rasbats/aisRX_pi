/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  aisRX Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                   *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#ifndef _HRGUI_IMPL_H_
#define _HRGUI_IMPL_H_

#ifdef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "aisRXgui.h"
#include "ocpn_plugin.h"
#include "tinyxml.h"
#include "wx/process.h"
#include "json/reader.h"
#include "json/writer.h"
#include <cmath>
#include <sstream>
#include <wx/filedlg.h>
#include <wx/gdicmn.h>
#include <wx/listctrl.h>
#include <wx/stdpaths.h>
#include <wx/thread.h>
#include <wx/utils.h>

#include "ais.h"
#include "signal.h"
#include "widget.h"
#include "AIS_Bitstring.h"

#include <wx/hashmap.h>
#include <memory>

#include <wx/wxhtml.h>
#include <wx/html/htmlwin.h>
#include <wx/dynarray.h>
#include <wx/tglbtn.h>

#include "AISdisplay.h"
#include "ASMmessages.h"
#include <wx/textfile.h>

#ifdef __WXOSX__
#define aisRX_DLG_STYLE                                                   \
    wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxSTAY_ON_TOP
#else
#define aisRX_DLG_STYLE                                                   \
    wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
#endif

using namespace std;

class aisRX_pi;
class AisMaker;
class AISdisplay;
class asmMessages;

class AIS_Target_Data;
class Signalling;
class AIS_Text_Data;

class AIS_Text_Data {
public:
    string Sector;
    string Hect;
    string ObjCode;
    string TextIndex;
};


// lass rtept;
class AIS_Target_Data
{
public:
	/*
    AIS_Target_Data();
    ~AIS_Target_Data();

    wxString BuildQueryResult(void);
    wxString GetRolloverString(void);
    wxString Get_vessel_type_string(bool b_short = false);
    wxString Get_class_string(bool b_short = false);
    wxString GetFullName( void );
    wxString GetCountryCode(bool b_CntryLongStr);
    void Toggle_AIS_CPA(void);
    void ToggleShowTrack(void);
    void CloneFrom( AIS_Target_Data* q );
    */

    int                       MID;
    int                       HECT;
    int                       NavStatus;
    int                       SyncState;
    int                       SlotTO;
    double                    SOG;
    double                    COG;
    double                    HDG;
    double                    Lon;
    double                    Lat;
    int                       ROTAIS;
    int                       ROTIND;
    
    char                      ShipNameExtension[15];
    unsigned char             ShipType;
    int                       IMO;

    int                       DimA;
    int                       DimB;
    int                       DimC;
    int                       DimD;

    double                    Euro_Length;            // Extensions for European Inland AIS
    double                    Euro_Beam;
    double                    Euro_Draft;
    int                       UN_shiptype;
    bool                      b_isEuroInland;
    bool                      b_hasInlandDac;  // intermediate storage for EU Inland. SignalK
    bool                      b_blue_paddle;
    int                       blue_paddle;

    int                       ETA_Mo;
    int                       ETA_Day;
    int                       ETA_Hr;
    int                       ETA_Min;

	int						  hect;
	int                       signalForm;
	int                       signalStatus;
	string                    country;
	string					  RISindex;
	bool                      b_nameValid;
	bool                      b_nameFromCache;

  
};

//WX_DECLARE_HASH_MAP( int, AIS_Target_Data*, wxIntegerHash, wxIntegerEqual, AIS_Target_Hash );
//WX_DECLARE_HASH_MAP( int, wxString, wxIntegerHash, wxIntegerEqual, AIS_Target_Name_Hash );

WX_DECLARE_HASH_MAP(string, AIS_Text_Data*, wxStringHash, wxStringEqual, AIS_Text_Hash);
WX_DECLARE_HASH_MAP(string, wxString, wxStringHash, wxStringEqual, AIS_Text_Name_Hash);



// An identifier to notify the application when the // work is done #define
// ID_COUNTED_COLORS    100

class AisMaker;


// ECE-TRANS-SC3-2006-10e-RIS.pdf - River Information System
//section(0), type(0), objectnumber(0), hectometre(0), signal(0), orientation(0), impact(0),
      //light_status(0),spare(0)
// Signal status

// Decodes the payload of an AIS message and returns an AisMsg instance.
// Returns a nullptr on failure.
// The body is the armored text from 1 or more sentences that compose
// the encoded bits for an AIS message.
// The fill_bits are the number of pad bits in the last character of the
// body.  AIS messages are 8-bit aligned and the characters in the armored
// body are 6-bit aligned.

namespace mylibais {

// Decodes the payload of an AIS message and returns an AisMsg instance.
// Returns a nullptr on failure.
// The body is the armored text from 1 or more sentences that compose
// the encoded bits for an AIS message.
// The fill_bits are the number of pad bits in the last character of the
// body.  AIS messages are 8-bit aligned and the characters in the armored
// body are 6-bit aligned.
std::unique_ptr<mylibais::AisMsg> CreateAisMsg(const string &body,
                                             const int fill_bits);

}  // namespace mylibais

class aisRXOverlayFactory;
class PlugIn_ViewPort;


class Dlg : public aisRXBase {
public:
    Dlg(wxWindow* parent, wxWindowID id = wxID_ANY,
        const wxString& title = _("aisRX"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = aisRX_DLG_STYLE);

    aisRX_pi* plugin;

    wxString DateTimeToTimeString(wxDateTime myDT);
    wxString DateTimeToDateString(wxDateTime myDT);

    wxString makeCheckSum(wxString mySentence);
	Signalling *signalling;

    AisMaker* myAIS;
	AisMaker* myaisRX;
	AISdisplay* m_pAISdialog;
	

	bool m_bDisplayStarted;
	void SetAISMessage(wxString &msg);
	void SetNMEAMessage(wxString &msg);
	void RenderHTMLQuery(AIS_Target_Data *td);
	//wxString BuildQueryResult(AIS_Target_Data *td);
	//AIS_Target_Data *td;

    wxTextFile* nmeafile;

    bool m_bUseAis;
    bool m_bUseFile;
    wxString m_tMMSI;

    bool m_bAuto;
    wxDateTime m_GribTimelineTime;

    double myDir;
    // Old hash data

	//AIS_Target_Data*  pTargetData;
	//AIS_Target_Hash* AISTargetList;
	//AIS_Target_Name_Hash* AISTargetNamesC;
    //AIS_Target_Name_Hash* AISTargetNamesNC;
	//AIS_Target_Name_Hash* HashFile;

    	// For Text messages
        AIS_Text_Hash* AISTextList;
        AIS_Text_Data* pNewTextData;
        AIS_Text_Data* pTextData;

        string slotNumber;
        string theMMSI;
        vector<AIS_Text_Data> myTextDataCollection;

	int              m_n_targets;

   //AIS_Target_Hash *GetTargetList(void) {return AISTargetList;}
   // AIS_Target_Data *Get_Target_Data_From_HECT(int mmsi);

   // AIS_Target_Data* m_pLatestTargetData;

	//vector<AIS_Target_Data>  FindSignalData(int hect);
	//vector<AIS_Target_Data>  FindSignalRISindex(int hect);

	wxString testing;
	
    void SetViewPort( PlugIn_ViewPort *vp );

	//AIS_Target_Data myTestData;
	//vector<AIS_Target_Data> myTestDataCollection;
	//vector<AIS_Target_Data> mySignalCollection;
	void UpdateAISTargetList(void);

	void CreateControlsMessageList();
	void OnTimer(wxTimerEvent& event);
	int  g_tick;

	wxArrayInt* myHect;
	
	bool listYN;
    PlugIn_ViewPort  *m_vp;
	bool m_baisRXHasStarted;
	asmMessages* m_pASMmessages1;
	AISdisplay* myAISdisplay;
	bool m_bHaveMessageList;
	bool m_bHaveDisplay;
	bool m_bUpdateTarget;

	wxString m_message;

	void OnCloseList(wxCloseEvent& event);

protected:
    bool m_bNeedsGrib;

private:

	
	

	wxString AIVDM;
	bool m_bShowaisRX;

	string m_sPayload;

    wxString m_sTimeSentence;
    wxString m_sTimeID;
    wxString m_sNmeaTime;

    bool dbg;

    bool m_bUseSetTime;
    bool m_bUseStop;
    bool m_bUsePause;

    void OnClose(wxCloseEvent& event);

	//void OnAuto(wxCommandEvent& event);
	void OnMessageList(wxCommandEvent& event);
	void OnLogging(wxCommandEvent& event);
	void Decode(wxString sentence);
    void OnTest(wxCommandEvent& event);
	wxString parseNMEASentence(wxString& sentence);
	void getAis8_200_26(string rawPayload);
	void getAis8_200_44(string rawPayload);

    void OnData(wxCommandEvent& event);
	void JumpTo( wxString lat, wxString lon, int scale);

    void OnFactory(wxCommandEvent& event);

    long m_iHECT;

    virtual void Lock() { routemutex.Lock(); }
    virtual void Unlock() { routemutex.Unlock(); }
    wxMutex routemutex;


    bool m_bUsingWind;
    bool m_bUsingFollow;
    bool m_bInvalidPolarsFile;
    bool m_bInvalidGribFile;
   
};

#endif
