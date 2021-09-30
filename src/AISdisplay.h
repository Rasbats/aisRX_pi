

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef _AISGUI_IMPL_H_
#define _AISGUI_IMPL_H_


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/msgdlg.h>

#include "ASMmessages.h"

///////////////////////////////////////////////////////////////////////////

enum {
    tlTRK = 0,
    tlNAME,
    tlCALL,
    tlMMSI,
    tlCLASS,
    tlTYPE,
    tlNAVSTATUS,
    tlBRG,
    tlRNG,
    tlCOG,
    tlSOG,
    tlCPA,
    tlTCPA
};// AISTargetListCtrl Columns;


///////////////////////////////////////////////////////////////////////////////
/// Class AISdisplay
///////////////////////////////////////////////////////////////////////////////

class AISdisplay : public wxDialog
{
	private:

	protected:
		wxButton* m_buttonHideDisplay;

		// Virtual event handlers, overide them in your derived class
		void OnList( wxCommandEvent& event ); 
		void OnHideDisplay( wxCommandEvent& event ); 


	public:
		wxTextCtrl* m_tcAIS;
		wxToggleButton* m_tbAISPause;
		wxToggleButton* m_tbAISList;

		AISdisplay( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("AIS Log"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 701,370 ), long style = wxCAPTION|wxRESIZE_BORDER );
		~AISdisplay();

};

#endif _AISGUI_IMPL_H_