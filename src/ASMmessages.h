///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef _ASMGUI_IMPL_H_
#define _ASMGUI_IMPL_H_


#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/html/htmlwin.h>
#include <wx/button.h>
#include <wx/dialog.h>

#include "AISdisplay.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class asmMessages
///////////////////////////////////////////////////////////////////////////////
class asmMessages : public wxDialog
{
	private:

	protected:
		wxButton* m_buttonHide;

		// Virtual event handlers, overide them in your derived class
		void OnHideList( wxCommandEvent& event ); 
		


	public:
		wxListCtrl* m_pListCtrlAISTargets;
		wxStaticText* m_pHeaderText;
		wxHtmlWindow* m_htmlWin;

		asmMessages( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("ASM Messages"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 322,340 ), long style = wxCAPTION|wxMINIMIZE_BOX|wxRESIZE_BORDER );
		~asmMessages();

};

#endif
