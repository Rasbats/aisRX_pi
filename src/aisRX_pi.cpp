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

#define DATABASE_NAME "RIS.db"

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

	wxString dbpath;

	wxFileName fn;
    wxString tmp_path;

    tmp_path = GetPluginDataDir("aisRX_pi");
    fn.SetPath(tmp_path);
    fn.AppendDir(_T("data"));

    fn.SetFullName(_T("RIS.db"));
	dbpath = fn.GetFullPath();

    bool newDB = !wxFileExists(dbpath);
    b_dbUsable = true;

	ret = sqlite3_open_v2(dbpath.mb_str(), &m_database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
      if (ret != SQLITE_OK)
      {
          wxLogMessage (_T("AISRX_PI: cannot open '%s': %s\n"), DATABASE_NAME, sqlite3_errmsg (m_database));
	      sqlite3_close (m_database);
	      b_dbUsable = false;
      }

    //    This PlugIn needs a toolbar icon, so request its insertion
    if (m_baisRXShowIcon) {
#ifdef ocpnUSE_SVG
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

		if (m_pDialog->m_timer1.IsRunning()) { // need to stop the timer or crash on exit
            m_pDialog->m_timer1.Stop();
        }

        // Capture dialog position
        wxPoint p = m_pDialog->GetPosition();
        wxRect r = m_pDialog->GetRect();
        SetaisRXDialogX(p.x);
        SetaisRXDialogY(p.y);
        SetaisRXDialogSizeX(r.GetWidth());
        SetaisRXDialogSizeY(r.GetHeight());	

		if(m_pDialog) {
			m_pDialog->Close();
			delete m_pDialog;
			m_pDialog = NULL;
		}

    
	if (m_paisRXOverlayFactory) {
			delete m_paisRXOverlayFactory;
			m_paisRXOverlayFactory = NULL;
	}		

    m_bShowaisRX = false;
    SetToolbarItemState(m_leftclick_tool_id, m_bShowaisRX);

	}  		
	
	SaveConfig();
    
	int m = sqlite3_close(m_database);

	wxLogMessage (_T("AISRX_PI: Close Msg: %i\n"), m);

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

        // Create the drawing factory
        m_paisRXOverlayFactory = new aisRXOverlayFactory(*m_pDialog );
        m_paisRXOverlayFactory->SetParentSize( m_display_width, m_display_height);		
        
 

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

bool aisRX_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
	
	if(!m_pDialog ||
       !m_pDialog->IsShown() ||
       !m_paisRXOverlayFactory)
        return false;

    m_pDialog->SetViewPort( vp );
    m_paisRXOverlayFactory->RenderaisRXOverlay ( dc, vp );
    return true;
}

bool aisRX_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
	

	if(!m_pDialog ||
       !m_pDialog->IsShown() ||
       !m_paisRXOverlayFactory)
        return false;

    m_pDialog->SetViewPort( vp );
    m_paisRXOverlayFactory->RenderGLaisRXOverlay ( pcontext, vp );
    return true;
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
	
    SaveConfig();   
}

void aisRX_pi::SetAISSentence(wxString& sentence) {
  if (NULL != m_pDialog) m_pDialog->SetAISMessage(sentence);
}

void aisRX_pi::SetNMEASentence(wxString& sentence)
{
    if (NULL != m_pDialog) {
      m_pDialog->SetNMEAMessage(sentence);
    }     

    
}

void aisRX_pi::dbGetTable(wxString sql, char ***results, int &n_rows, int &n_columns)
{
      ret = sqlite3_get_table (m_database, sql.mb_str(), results, &n_rows, &n_columns, &err_msg);
      if (ret != SQLITE_OK)
      {
            wxLogMessage (_T("Database error: %s in query: %s\n"), *err_msg, sql.c_str());
	      sqlite3_free (err_msg);
            b_dbUsable = false;
      }
}

void aisRX_pi::dbFreeResults(char **results)
{
      sqlite3_free_table (results);
}
