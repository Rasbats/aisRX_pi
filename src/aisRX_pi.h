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

#ifndef _SDR_PI_H_
#define _SDR_PI_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include <wx/glcanvas.h>
#endif // precompiled headers

#include <wx/fileconf.h>
#include <wx/datetime.h>
#include <wx/tokenzr.h>

#include "config.h"

#include "json/reader.h"
#include "json/writer.h"

#include "ocpn_plugin.h" //Required for OCPN plugin functions
#include "aisRXgui_impl.h"
#include "wx/wxsqlite3.h"
#include <wx/thread.h>
#include <map>
#include <queue>

class Dlg;
class aisRX_pi;

class DbThread : public wxThread {
   public:
    DbThread(aisRX_pi* handler) : wxThread() {
        Create();
        m_pHandler = handler;
        m_bIsWriting = false;
    }
    ~DbThread();
    void* Entry();
    bool IsWriting() { return m_bIsWriting; }

   protected:
    aisRX_pi* m_pHandler;

   private:
    bool m_bIsWriting;
};




//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define aisRX_TOOL_POSITION                                               \
    -1 // Request default positioning of toolbar tool

class aisRX_pi : public opencpn_plugin_116 {
public:
    aisRX_pi(void* ppimgr);
    ~aisRX_pi(void);

    //    The required PlugIn Methods
    int Init(void);
    bool DeInit(void);

    int GetAPIVersionMajor();
    int GetAPIVersionMinor();
    int GetPlugInVersionMajor();
    int GetPlugInVersionMinor();
    wxBitmap* GetPlugInBitmap();
    wxString GetCommonName();
    wxString GetShortDescription();
    wxString GetLongDescription();

    //    The required override PlugIn Methods
    int GetToolbarToolCount(void);
    void OnToolbarToolCallback(int id);

    //    Optional plugin overrides
    void SetColorScheme(PI_ColorScheme cs);
	void SetAISSentence(wxString &sentence);

    //    The override PlugIn Methods
    void SetNMEASentence(wxString& sentence);

    //    Other public methods
    void SetaisRXDialogX(int x) { m_hr_dialog_x = x; };
    void SetaisRXDialogY(int x) { m_hr_dialog_y = x; };
    void SetaisRXDialogWidth(int x) { m_hr_dialog_width = x; };
    void SetaisRXDialogHeight(int x) { m_hr_dialog_height = x; };
    void SetaisRXDialogSizeX(int x) { m_hr_dialog_sx = x; }
    void SetaisRXDialogSizeY(int x) { m_hr_dialog_sy = x; }
    void OnaisRXDialogClose();

    int m_hr_dialog_x, m_hr_dialog_y;

    double GetCursorLat(void) { return m_cursor_lat; }
    double GetCursorLon(void) { return m_cursor_lon; }

    void ShowPreferencesDialog(wxWindow* parent);

    bool m_bGribValid;
    double m_grib_lat, m_grib_lon;
    double m_tr_spd;
    double m_tr_dir;

    wxString StandardPath();
    wxBitmap m_panelBitmap;
    Dlg* m_pDialog;

	// for the database
	wxSQLite3Database* initDB();
	int QueryDB(wxSQLite3Database* db, const wxString& sql);
	wxSQLite3ResultSet SelectFromDB(wxSQLite3Database* db, const wxString& sql);
	wxSQLite3Database* m_db;
	bool m_bDBUsable;
    bool m_bWaitForDB;
	bool m_db_thread_running;
    double followDir;
    wxDateTime dt;
	bool finishing;

	void SetDBThreadRunning(bool state) { m_db_thread_running = state; }
    bool IsDBThreadRunning() { return m_db_thread_running; }

	//
    aisRX_pi* plugin;

	DbThread* m_pThread;
    wxCriticalSection m_pThreadCS;  // protects the m_pThread pointer
    friend class DbThread;          // allow it to access our m_pThread

    std::queue<wxString> query_queue;

protected:
    int QueryDB(const wxString& sql) { return QueryDB(m_db, sql); }
    wxString GetQuery();
    bool HasQueries();



private:
    double m_cursor_lat;
    double m_cursor_lon;

    int m_position_menu_id;
    double m_GUIScaleFactor;
    void OnClose(wxCloseEvent& event);

    



    wxFileConfig* m_pconfig;
    wxWindow* m_parent_window;
    bool LoadConfig(void);
    bool SaveConfig(void);

    int m_hr_dialog_width, m_hr_dialog_height;
    int m_hr_dialog_sx, m_hr_dialog_sy;
    int m_display_width, m_display_height;
    int m_leftclick_tool_id;
    bool m_baisRXShowIcon;
    bool m_bShowaisRX;

    bool m_bCopyUseAis;
    bool m_bCopyUseFile;
    wxString m_tCopyMMSI;
};


#endif
