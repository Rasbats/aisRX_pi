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

#include "AisMaker.h"
#include "aisRX_pi.h"
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

#include "ais2.h"
#include "signal.h"
#include "widget.h"
#include "AIS_Bitstring.h"

#include <wx/hashmap.h>
#include <memory>

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
class AIS_Target_Data;
class Signalling;

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
    int                       MMSI;
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
  
};

WX_DECLARE_HASH_MAP( int, AIS_Target_Data*, wxIntegerHash, wxIntegerEqual, AIS_Target_Hash );
WX_DECLARE_HASH_MAP( int, wxString, wxIntegerHash, wxIntegerEqual, AIS_Target_Name_Hash );





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


    AisMaker* myAIS;
	AisMaker* myaisRX;
	AISdisplay* m_pAISdialog;
	bool m_bDisplayStarted;
	void SetAISMessage(wxString &msg);
	wxString SetaisRXMessage(string &msg);

    wxTextFile* nmeafile;

    bool m_bUseAis;
    bool m_bUseFile;
    wxString m_tMMSI;

    bool m_bAuto;
    wxDateTime m_GribTimelineTime;

    double myDir;

	AIS_Target_Data*  pTargetData;
	AIS_Target_Hash* AISTargetList;
	AIS_Target_Name_Hash* AISTargetNamesC;
    AIS_Target_Name_Hash* AISTargetNamesNC;
	AIS_Target_Name_Hash* HashFile;

	AIS_Target_Hash *GetTargetList(void) {return AISTargetList;}
    //AIS_Target_Hash *GetAreaNoticeSourcesList(void) {return AIS_AreaNotice_Sources;}
    AIS_Target_Data *Get_Target_Data_From_MMSI(int mmsi);

    AIS_Target_Data* m_pLatestTargetData;

protected:
    bool m_bNeedsGrib;

private:
    wxString AIVDM;

    double followDir;

    wxDateTime dt;

	string m_sPayload;

    wxString m_sTimeSentence;
    wxString m_sTimeID;
    wxString m_sNmeaTime;

    bool dbg;

    bool m_bUseSetTime;
    bool m_bUseStop;
    bool m_bUsePause;

    void OnClose(wxCloseEvent& event);

	void OnAuto(wxCommandEvent& event);
    void OnTest(wxCommandEvent& event);
	void OnSignalShow(wxCommandEvent& event);
	wxString parseNMEASentence(wxString& sentence);
	void getAis8_200_25(string rawPayload);
	void getAis8_200_26(string rawPayload);
	void getAis8_200_41(string rawPayload);
	void getAis8_200_44(string rawPayload);
    // void SendAIS(double cse, double spd, double lat, double lon);

    void OnStandby(wxCommandEvent& event);
    void GoToStandby();

    

    long m_iMMSI;

    virtual void Lock() { routemutex.Lock(); }
    virtual void Unlock() { routemutex.Unlock(); }
    wxMutex routemutex;


    bool m_bUsingWind;
    bool m_bUsingFollow;
    bool m_bInvalidPolarsFile;
    bool m_bInvalidGribFile;
    bool m_baisRXHasStarted;
};

#endif
