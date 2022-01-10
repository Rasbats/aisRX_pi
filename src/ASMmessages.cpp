///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ASMmessages.h"
#include "aisRXgui_impl.h"

class Dlg;

///////////////////////////////////////////////////////////////////////////

asmMessages::asmMessages( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("label") ), wxVERTICAL );

	m_pListCtrlAISTargets = new wxListCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON|wxLC_REPORT|wxLC_SINGLE_SEL);
	sbSizer3->Add( m_pListCtrlAISTargets, 0, wxALL|wxEXPAND, 5 );


	mainSizer->Add( sbSizer3, 0, wxALL|wxEXPAND, 5 );

	m_pHeaderText = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_pHeaderText->Wrap( -1 );
	mainSizer->Add( m_pHeaderText, 0, wxALL|wxEXPAND, 5 );

	m_htmlWin = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	mainSizer->Add( m_htmlWin, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_buttonHide = new wxButton( this, wxID_ANY, _("Hide"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_buttonHide, 0, wxALL, 5 );


	mainSizer->Add( bSizer4, 1, wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonHide->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnHideList ), NULL, this );
}

asmMessages::~asmMessages()
{
	// Disconnect Events
	m_buttonHide->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnHideList ), NULL, this );

}
void asmMessages::OnHideList( wxCommandEvent& event) {

	this->Hide();
}

