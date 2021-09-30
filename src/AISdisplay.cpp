///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AISdisplay.h"
#include "aisRXgui_impl.h"

class Dlg;

///////////////////////////////////////////////////////////////////////////

AISdisplay::AISdisplay( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_tcAIS = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer1->Add( m_tcAIS, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	m_tbAISPause = new wxToggleButton( this, wxID_ANY, _("Pause"), wxDefaultPosition, wxDefaultSize, 0 );
	m_tbAISPause->SetValue( true );
	bSizer11->Add( m_tbAISPause, 0, wxALL, 5 );

	m_tbAISList = new wxToggleButton( this, wxID_ANY, _("Show List"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_tbAISList, 0, wxALL, 5 );

	m_buttonHideDisplay = new wxButton( this, wxID_ANY, _("Hide AIS Log"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_buttonHideDisplay, 0, wxALL, 5 );


	bSizer1->Add( bSizer11, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_tbAISList->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( AISdisplay::OnList ), NULL, this );
	m_buttonHideDisplay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AISdisplay::OnHideDisplay ), NULL, this );
}

AISdisplay::~AISdisplay()
{
	// Disconnect Events
	m_tbAISList->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( AISdisplay::OnList ), NULL, this );
	m_buttonHideDisplay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AISdisplay::OnHideDisplay ), NULL, this );

}

void AISdisplay::OnHideDisplay(wxCommandEvent& event) {

	this->Hide();
}

void AISdisplay::OnList(wxCommandEvent& event) {

	//
	//

}