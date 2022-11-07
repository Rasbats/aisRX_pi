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
class AISdisplay;
class asmMessages;

class AIS_Text_Data;

class AIS_Text_Data {
public:
    string Sector;
    string Hect;
    string ObjCode;
    string Text;
    string RISindex;
    double lat;
    double lon;
    string wwname;
    string location;
    string country;
};


WX_DECLARE_HASH_MAP(string, AIS_Text_Data*, wxStringHash, wxStringEqual, AIS_Text_Hash);
WX_DECLARE_HASH_MAP(string, wxString, wxStringHash, wxStringEqual, AIS_Text_Name_Hash);

class PlugIn_ViewPort;
class asmMessages;


class Dlg : public aisRXBase {
public:
    Dlg(wxWindow* parent, wxWindowID id = wxID_ANY,
        const wxString& title = _("aisRX"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = aisRX_DLG_STYLE);

    aisRX_pi* plugin;

    wxString DateTimeToTimeString(wxDateTime myDT);
    wxString DateTimeToDateString(wxDateTime myDT);

	AISdisplay* m_pAISdialog;
	bool m_bDisplayStarted;
	void SetAISMessage(wxString &msg);
	void SetNMEAMessage(wxString &msg);

    wxTextFile* nmeafile;

    bool m_bUseAis;
    bool m_bUseFile;
    wxString m_tMMSI;

    bool m_bAuto;
    wxDateTime m_GribTimelineTime;

    double myDir;

    	// For Text messages
        AIS_Text_Hash* AISTextList;
        AIS_Text_Data* pNewTextData;
        AIS_Text_Data* pTextData;

        string slotNumber;
        string theMMSI;
        vector<AIS_Text_Data> myTextDataCollection;

	int              m_n_targets;

	wxString testing;
	
    void SetViewPort( PlugIn_ViewPort *vp );

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
    void OnLocate(wxString risindex, wxString text, wxString location);

	void OnCloseList(wxCloseEvent& event);
    AIS_Text_Data FindObjectRISindex(int sect, string objcode, int hectomt);
    AIS_Text_Data FindLatLonObjectRISindex(wxString risindex, wxString text, wxString locname); 
    
    vector<AIS_Text_Data> myTextCollection;
    bool m_bUsingTest;

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
	void OnMessageList(wxCommandEvent& event);
	void OnLogging(wxCommandEvent& event);
	void Decode(wxString sentence);
    void OnTest(wxCommandEvent& event);
	wxString parseNMEASentence(wxString& sentence);
	void getAis8_200_26(string rawPayload);
	void getAis8_200_44(string rawPayload);
	void JumpTo( wxString lat, wxString lon, int scale);


    //long m_iHECT;

    virtual void Lock() { routemutex.Lock(); }
    virtual void Unlock() { routemutex.Unlock(); }
    wxMutex routemutex;


    bool m_bUsingWind;
    bool m_bUsingFollow;
    bool m_bInvalidPolarsFile;
    bool m_bInvalidGribFile;
   
};

#endif
