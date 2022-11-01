///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ASMmessages.h"
#include "aisRXgui_impl.h"

///////////////////////////////////////////////////////////////////////////

asmMessages::asmMessages( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{	
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("label") ), wxVERTICAL );

	m_pListCtrlAISTargets = new wxListCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON|wxLC_REPORT );
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
    m_pListCtrlAISTargets->Connect(wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(asmMessages::GetItemSelected), NULL, this);
	m_buttonHide->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnHideList ), NULL, this );
}

asmMessages::~asmMessages()
{
	// Disconnect Events
    m_pListCtrlAISTargets->Disconnect(wxEVT_COMMAND_LIST_ITEM_SELECTED,wxListEventHandler(asmMessages::GetItemSelected), NULL, this);
	m_buttonHide->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( asmMessages::OnHideList ), NULL, this );

}
void asmMessages::OnHideList( wxCommandEvent& event) {
	this->Hide();
}

void asmMessages::GetItemSelected(wxListEvent& event)
{   
    long item = -1;
    long selectedItem = -1;
    for (;;) {
        item = m_pListCtrlAISTargets->GetNextItem(
            item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if (item == -1)
            break;
        // this item is selected - do whatever is needed with it
        selectedItem = item;
    }
	
    wxString risindex = GetCellContentsString(selectedItem, 5);
    wxString text = GetCellContentsString(selectedItem, 4);
    wxString location = GetCellContentsString(selectedItem, 3);

    myMainDialog->OnLocate(risindex, text, location);	
}

wxString asmMessages::GetCellContentsString(
    long row_number, int column)
{
    wxListItem row_info;
    wxString cell_contents_string;

    // Set what row it is (m_itemId is a member of the regular wxListCtrl class)
    row_info.m_itemId = row_number;
    // Set what column of that row we want to query for information.
    row_info.m_col = column;
    // Set text mask
    row_info.m_mask = wxLIST_MASK_TEXT;

    // Get the info and store it in row_info variable.
    m_pListCtrlAISTargets->GetItem(row_info);

    // Extract the text out that cell
    cell_contents_string = row_info.m_text;

    return cell_contents_string;
}
