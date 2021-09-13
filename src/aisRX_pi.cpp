/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  aisRX Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                *
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

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif // precompiled headers

#include "aisRX_pi.h"
#include "aisRXgui.h"
#include "aisRXgui_impl.h"
#include "ocpn_plugin.h"

class aisRX_pi;
class Dlg;

using namespace std;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void* ppimgr)
{
    return new aisRX_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p) { delete p; }

//---------------------------------------------------------------------------------------------------------
//
//    aisRX PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

aisRX_pi::aisRX_pi(void* ppimgr)
    : opencpn_plugin_116(ppimgr)
{
    // Create the PlugIn icons
    initialize_images();

    wxFileName fn;

    auto path = GetPluginDataDir("aisRX_pi");
    fn.SetPath(path);
    fn.AppendDir("data");
    fn.SetFullName("aisRX_panel_icon.png");

    path = fn.GetFullPath();

    wxInitAllImageHandlers();

    wxLogDebug(wxString("Using icon path: ") + path);
    if (!wxImage::CanRead(path)) {
        wxLogDebug("Initiating image handlers.");
        wxInitAllImageHandlers();
    }
    wxImage panelIcon(path);
    if (panelIcon.IsOk())
        m_panelBitmap = wxBitmap(panelIcon);
    else
        wxLogWarning("aisRX panel icon has NOT been loaded");
    m_bShowaisRX = false;
}

aisRX_pi::~aisRX_pi(void)
{

    delete _img_aisRXIcon;

    if (m_pDialog) {

        wxFileConfig* pConf = GetOCPNConfigObject();
        ;

        if (pConf) {

            pConf->SetPath(_T("/Settings/aisRX"));

            pConf->Write(_T("aisRXUseAis"), m_bCopyUseAis);
            pConf->Write(_T("aisRXUseFile"), m_bCopyUseFile);
            pConf->Write(_T("aisRXMMSI"), m_tCopyMMSI);
        }
    }
}

int aisRX_pi::Init(void)
{
    AddLocaleCatalog(_T("opencpn-aisRX_pi"));

	m_db_thread_running = false;

    m_bDBUsable = true;

    m_bWaitForDB = true;

    finishing = false;

    m_db = initDB();

    wxSQLite3ResultSet set;

    // Set some default private member parameters
    m_hr_dialog_x = 40;
    m_hr_dialog_y = 80;
    m_hr_dialog_sx = 400;
    m_hr_dialog_sy = 300;
    ::wxDisplaySize(&m_display_width, &m_display_height);

    //    Get a pointer to the opencpn display canvas, to use as a parent for
    //    the POI Manager dialog
    m_parent_window = GetOCPNCanvasWindow();

    //    Get a pointer to the opencpn configuration object
    m_pconfig = GetOCPNConfigObject();

    //    And load the configuration items
    LoadConfig();

    //    This PlugIn needs a toolbar icon, so request its insertion
    if (m_baisRXShowIcon) {
#ifdef aisRX_USE_SVG
        m_leftclick_tool_id = InsertPlugInToolSVG(_T( "aisRX" ),
            _svg_aisRX, _svg_aisRX, _svg_aisRX_toggled,
            wxITEM_CHECK, _("aisRX"), _T( "" ), NULL,
            aisRX_TOOL_POSITION, 0, this);
#else
        m_leftclick_tool_id = InsertPlugInTool(_T(""), _img_aisRXIcon,
            _img_aisRXIcon, wxITEM_CHECK, _("aisRX"), _T(""), NULL,
            aisRX_TOOL_POSITION, 0, this);
#endif
    }
   

    m_pDialog = NULL;

    return (WANTS_OVERLAY_CALLBACK | WANTS_OPENGL_OVERLAY_CALLBACK
        | WANTS_TOOLBAR_CALLBACK | INSTALLS_TOOLBAR_TOOL | WANTS_CURSOR_LATLON
        | WANTS_NMEA_SENTENCES | WANTS_AIS_SENTENCES | WANTS_PREFERENCES
        | WANTS_PLUGIN_MESSAGING | WANTS_CONFIG);
}

bool aisRX_pi::DeInit(void)
{
    //    Record the dialog position
    if (NULL != m_pDialog) {
        // Capture dialog position
        wxPoint p = m_pDialog->GetPosition();
        wxRect r = m_pDialog->GetRect();
        SetaisRXDialogX(p.x);
        SetaisRXDialogY(p.y);
        SetaisRXDialogSizeX(r.GetWidth());
        SetaisRXDialogSizeY(r.GetHeight());

        
        m_pDialog->Close();
        delete m_pDialog;
        m_pDialog = NULL;

        m_bShowaisRX = false;
        SetToolbarItemState(m_leftclick_tool_id, m_bShowaisRX);
    }

    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

    return true;
}

int aisRX_pi::GetAPIVersionMajor()
{
    return atoi(API_VERSION);
}

int aisRX_pi::GetAPIVersionMinor()
{
    std::string v(API_VERSION);
    size_t dotpos = v.find('.');
    return atoi(v.substr(dotpos + 1).c_str());
}

int aisRX_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int aisRX_pi::GetPlugInVersionMinor() { return PLUGIN_VERSION_MINOR; }

wxBitmap* aisRX_pi::GetPlugInBitmap() { return &m_panelBitmap; }

wxString aisRX_pi::GetCommonName() { return _("aisRX"); }

wxString aisRX_pi::GetShortDescription() { return _("aisRX player"); }

wxString aisRX_pi::GetLongDescription() { return _("Almost a simulator"); }

int aisRX_pi::GetToolbarToolCount(void) { return 1; }

void aisRX_pi::SetColorScheme(PI_ColorScheme cs)
{
    if (NULL == m_pDialog)
        return;

    DimeWindow(m_pDialog);
}

void aisRX_pi::ShowPreferencesDialog(wxWindow* parent)
{
    aisRXPreferences* Pref = new aisRXPreferences(parent);

    Pref->m_cbTransmitAis->SetValue(m_bCopyUseAis);
    Pref->m_cbAisToFile->SetValue(m_bCopyUseFile);
    Pref->m_textCtrlMMSI->SetValue(m_tCopyMMSI);

    if (Pref->ShowModal() == wxID_OK) {

        bool copyAis = Pref->m_cbTransmitAis->GetValue();
        bool copyFile = Pref->m_cbAisToFile->GetValue();
        wxString copyMMSI = Pref->m_textCtrlMMSI->GetValue();

        if (m_bCopyUseAis != copyAis || m_bCopyUseFile != copyFile
            || m_tCopyMMSI != copyMMSI) {
            m_bCopyUseAis = copyAis;
            m_bCopyUseFile = copyFile;
            m_tCopyMMSI = copyMMSI;
        }

        if (m_pDialog) {
            m_pDialog->m_bUseAis = m_bCopyUseAis;
            m_pDialog->m_bUseFile = m_bCopyUseFile;
            m_pDialog->m_tMMSI = m_tCopyMMSI;
        }

        SaveConfig();

        RequestRefresh(m_parent_window); // refresh main window
    }
}

void aisRX_pi::OnToolbarToolCallback(int id)
{

    if (NULL == m_pDialog) {
        m_pDialog = new Dlg(m_parent_window);
        m_pDialog->plugin = this;
        
        m_pDialog->Move(wxPoint(m_hr_dialog_x, m_hr_dialog_y));
        m_pDialog->SetSize(m_hr_dialog_sx, m_hr_dialog_sy);
    }

    // m_pDialog->Fit();
    // Toggle
    m_bShowaisRX = !m_bShowaisRX;

    //    Toggle dialog?
    if (m_bShowaisRX) {
        m_pDialog->Move(wxPoint(m_hr_dialog_x, m_hr_dialog_y));
        m_pDialog->SetSize(m_hr_dialog_sx, m_hr_dialog_sy);
        m_pDialog->Show();

    } else {
        m_pDialog->Hide();
    }

    // Toggle is handled by the toolbar but we must keep plugin manager b_toggle
    // updated to actual status to ensure correct status upon toolbar rebuild
    SetToolbarItemState(m_leftclick_tool_id, m_bShowaisRX);

    // Capture dialog position
    wxPoint p = m_pDialog->GetPosition();
    wxRect r = m_pDialog->GetRect();
    SetaisRXDialogX(p.x);
    SetaisRXDialogY(p.y);
    SetaisRXDialogSizeX(r.GetWidth());
    SetaisRXDialogSizeY(r.GetHeight());

    RequestRefresh(m_parent_window); // refresh main window
}

void aisRX_pi::SetAISSentence(wxString &sentence) {
    if (NULL != m_pDialog) m_pDialog->SetAISMessage(sentence);
}

bool aisRX_pi::LoadConfig(void)
{
    wxFileConfig* pConf = (wxFileConfig*)m_pconfig;

    if (pConf) {
        pConf->SetPath(_T( "/Settings/aisRX_pi" ));
        pConf->Read(_T( "ShowaisRXIcon" ), &m_baisRXShowIcon, 1);
        pConf->Read(_T("aisRXUseAis"), &m_bCopyUseAis, 0);
        pConf->Read(_T("aisRXUseFile"), &m_bCopyUseFile, 0);
        m_tCopyMMSI = pConf->Read(_T("aisRXMMSI"), _T("12345"));

        m_hr_dialog_x = pConf->Read(_T ( "DialogPosX" ), 40L);
        m_hr_dialog_y = pConf->Read(_T ( "DialogPosY" ), 140L);
        m_hr_dialog_sx = pConf->Read(_T ( "DialogSizeX"), 330L);
#ifdef __WXOSX__
        m_hr_dialog_sy = pConf->Read(_T ( "DialogSizeY"), 250L);
#else
        m_hr_dialog_sy = pConf->Read(_T ( "DialogSizeY"), 300L);
#endif
        if ((m_hr_dialog_x < 0) || (m_hr_dialog_x > m_display_width))
            m_hr_dialog_x = 40;
        if ((m_hr_dialog_y < 0) || (m_hr_dialog_y > m_display_height))
            m_hr_dialog_y = 140;

        return true;
    } else
        return false;
}

bool aisRX_pi::SaveConfig(void)
{
    wxFileConfig* pConf = (wxFileConfig*)m_pconfig;

    if (pConf) {
        pConf->SetPath(_T ( "/Settings/aisRX_pi" ));
        pConf->Write(_T ( "ShowaisRXIcon" ), m_baisRXShowIcon);
        pConf->Write(_T("aisRXUseAis"), m_bCopyUseAis);
        pConf->Write(_T("aisRXUseFile"), m_bCopyUseFile);
        pConf->Write(_T("aisRXMMSI"), m_tCopyMMSI);

        pConf->Write(_T ( "DialogPosX" ), m_hr_dialog_x);
        pConf->Write(_T ( "DialogPosY" ), m_hr_dialog_y);
        pConf->Write(_T ( "DialogSizeX"), m_hr_dialog_sx);
        pConf->Write(_T ( "DialogSizeY"), m_hr_dialog_sy);

        return true;
    } else
        return false;
}

void aisRX_pi::OnaisRXDialogClose()
{
    m_bShowaisRX = false;
    SetToolbarItemState(m_leftclick_tool_id, m_bShowaisRX);
    m_pDialog->Hide();
	if (m_pDialog->signalling != NULL) {
		m_pDialog->signalling->Close();
	}
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window
}

void aisRX_pi::SetNMEASentence(wxString& sentence)
{

    // $GPAPB,A,A,0.10,R,N,V,V,011,M,DEST,011,M,011,M*3C

    if (NULL == m_pDialog)
        return;

    wxString token[40];
    wxString s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    token[0] = _T("");

    wxStringTokenizer tokenizer(sentence, wxT(","));
    int i = 0;

    while (tokenizer.HasMoreTokens()) {
        token[i] = tokenizer.GetNextToken();
        i++;
    }
    if (token[0].Right(3) == _T("APB")) {

        s11 = token[11];

        if (m_pDialog->m_bAuto) {

            double value;
            s11.ToDouble(&value);
            m_pDialog->myDir = value;
        }
        /*
        s6 = token[6];
        if (s6 == _T("A")) {
                wxMessageBox(_("Vessel has arrived at the final waypoint"));
        }
        */
    }
}

wxSQLite3Database* aisRX_pi::initDB() {
    bool have_to_create = false;
    wxString sDBName = *GetpPrivateApplicationDataLocation() + wxFileName::GetPathSeparator() + wxT("RIS.db");

    wxLogMessage(_T("OBJSEARCH_PI: Database file to be used: %s"), sDBName.c_str());
    if (!wxFileExists(sDBName)) {
        have_to_create = true;
    }
    wxSQLite3Database* db = new wxSQLite3Database();
    try {
        db->Open(sDBName);
    } catch (wxSQLite3Exception& e) {
        wxLogMessage(_T("OBJSEARCH_PI: DB Exception: %i : %s"), e.GetErrorCode(), e.GetMessage().c_str());
        m_bDBUsable = false;
    } catch (...) {
        wxLogMessage(_T("OBJSEARCH_PI: Unknown exception"));
        m_bDBUsable = false;
    }

    if (have_to_create && m_bDBUsable) {
        QueryDB(db,
                wxT("CREATE TABLE chart (id INTEGER PRIMARY KEY AUTOINCREMENT, chartname TEXT, scale REAL, nativescale INTEGER)"));
        QueryDB(db, wxT("CREATE TABLE feature (id INTEGER PRIMARY KEY AUTOINCREMENT, featurename TEXT)"));
        QueryDB(db, wxT("CREATE TABLE object (chart_id INTEGER, feature_id INTEGER, objname TEXT, lat REAL, lon REAL)"));
    }

    if (m_bDBUsable) {
       // db->CreateFunction(_T("distanceMercator"), 4, distMercFunc, true);
        // sqlite3_create_function(db, "distanceMercator", 4, SQLITE_UTF8, NULL, &distanceMercatorFunc, NULL, NULL));
        QueryDB(db, _T("PRAGMA synchronous=OFF"));
        QueryDB(db, _T("PRAGMA count_changes=OFF"));
        QueryDB(db, _T("PRAGMA journal_mode=MEMORY"));
        QueryDB(db, _T("PRAGMA temp_store=MEMORY"));

        // Fix the broken objects created by v 0.1 and 0.2
        QueryDB(db, _T("UPDATE object SET lon = lon - 360 WHERE lon > 180"));
        QueryDB(db, _T("UPDATE object SET lon = lon + 360 WHERE lon < - 180"));
        QueryDB(db, _T("DELETE FROM object WHERE lon < - 180 OR lon > 180 OR lat < -90 OR lat > 90"));
    }

    return db;
}

int aisRX_pi::QueryDB(wxSQLite3Database* db, const wxString& sql) {
    int ret = -1;
    try {
        ret = db->ExecuteUpdate(sql);
    } catch (wxSQLite3Exception& e) {
        wxLogMessage(_T("OBJSEARCH_PI: DB Exception: %i : %s"), e.GetErrorCode(), e.GetMessage().c_str());
        m_bDBUsable = false;
    } catch (...) {
        wxLogMessage(_T("OBJSEARCH_PI: Unknown exception during '%s'"), sql.c_str());
        m_bDBUsable = false;
    }

    return ret;
}

wxSQLite3ResultSet aisRX_pi::SelectFromDB(wxSQLite3Database* db, const wxString& sql) {
    if (!m_bDBUsable) return wxSQLite3ResultSet();
    try {
        return db->ExecuteQuery(sql);
    } catch (wxSQLite3Exception& e) {
        wxLogMessage(_T("OBJSEARCH_PI: DB Exception: %i : %s"), e.GetErrorCode(), e.GetMessage().c_str());
        m_bDBUsable = false;
    } catch (...) {
        wxLogMessage(_T("OBJSEARCH_PI: Unknown exception during '%s'"), sql.c_str());
        m_bDBUsable = false;
    }
    return wxSQLite3ResultSet();
}

void* DbThread::Entry() {
    m_pHandler->SetDBThreadRunning(true);
    while (!TestDestroy()) {
        m_pHandler->QueryDB(_T("BEGIN TRANSACTION"));
        m_bIsWriting = true;
        while (m_pHandler->HasQueries()) {
            m_pHandler->QueryDB(m_pHandler->GetQuery());
        }
        m_pHandler->QueryDB(_T("COMMIT TRANSACTION"));
        m_bIsWriting = false;
        Sleep(500);
        // wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_DBTHREAD_UPDATE));
    }
    // signal the event handler that this thread is going to be destroyed
    // NOTE: here we assume that using the m_pHandler pointer is safe,
    // (in this case this is assured by the MyFrame destructor)
    //    wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_DBTHREAD_COMPLETED));
    // return (wxThread::ExitCode)0; // success

    return 0;
}

DbThread::~DbThread() {
    wxCriticalSectionLocker enter(m_pHandler->m_pThreadCS);
    m_pHandler->m_pThread = NULL;
    m_pHandler->SetDBThreadRunning(false);
}

wxString aisRX_pi::GetQuery() {
    wxString query = query_queue.front();
    query_queue.pop();
    return query;
}

bool aisRX_pi::HasQueries() { return !query_queue.empty(); }