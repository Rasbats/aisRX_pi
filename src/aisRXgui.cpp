///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "aisRXgui.h"

///////////////////////////////////////////////////////////////////////////

aisRXBase::aisRXBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	this->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	this->SetBackgroundColour( wxColour( 201, 201, 201 ) );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Received sentence (For use with Test) :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer121->Add( m_staticText1, 0, wxALL, 5 );

	m_textCtrlTest = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( m_textCtrlTest, 0, wxALL|wxEXPAND, 5 );

	m_toggleBtn1 = new wxToggleButton( this, wxID_ANY, _("Pause"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toggleBtn1->SetValue( true );
	m_toggleBtn1->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer121->Add( m_toggleBtn1, 0, wxALL|wxEXPAND, 5 );


	bSizer10->Add( bSizer121, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer122;
	bSizer122 = new wxBoxSizer( wxVERTICAL );

	m_notebookMessage = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0|wxBORDER_SIMPLE );
	m_panelSignal = new wxPanel( m_notebookMessage, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxVSCROLL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText3 = new wxStaticText( m_panelSignal, wxID_ANY, _("MMSI"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer1->Add( m_staticText3, 0, wxALL, 5 );

	m_textMMSI = new wxTextCtrl( m_panelSignal, wxID_ANY, _("00000"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textMMSI, 0, wxALL, 5 );

	m_staticText2 = new wxStaticText( m_panelSignal, wxID_ANY, _("Country"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALL, 5 );

	m_textCountry = new wxTextCtrl( m_panelSignal, wxID_ANY, _("ZZ"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textCountry, 0, wxALL, 5 );

	m_staticText4 = new wxStaticText( m_panelSignal, wxID_ANY, _("Fairway Section"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALL, 5 );

	m_textFairwaySection = new wxTextCtrl( m_panelSignal, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textFairwaySection, 0, wxALL, 5 );

	m_staticText5 = new wxStaticText( m_panelSignal, wxID_ANY, _("Station Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer1->Add( m_staticText5, 0, wxALL, 5 );

	m_textStationType = new wxTextCtrl( m_panelSignal, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textStationType, 0, wxALL, 5 );

	m_staticText6 = new wxStaticText( m_panelSignal, wxID_ANY, _("Station Number"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gSizer1->Add( m_staticText6, 0, wxALL, 5 );

	m_textStationNumber = new wxTextCtrl( m_panelSignal, wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textStationNumber, 0, wxALL, 5 );

	m_staticText7 = new wxStaticText( m_panelSignal, wxID_ANY, _("Fairway Hectometre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gSizer1->Add( m_staticText7, 0, wxALL, 5 );

	m_textHectometre = new wxTextCtrl( m_panelSignal, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textHectometre, 0, wxALL, 5 );

	m_staticText8 = new wxStaticText( m_panelSignal, wxID_ANY, _("Signal Form"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	gSizer1->Add( m_staticText8, 0, wxALL, 5 );

	m_textSignalForm = new wxTextCtrl( m_panelSignal, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textSignalForm, 0, wxALL, 5 );

	m_staticText9 = new wxStaticText( m_panelSignal, wxID_ANY, _("Orientation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gSizer1->Add( m_staticText9, 0, wxALL, 5 );

	m_textOrientation = new wxTextCtrl( m_panelSignal, wxID_ANY, _("511"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textOrientation, 0, wxALL, 5 );

	m_staticText10 = new wxStaticText( m_panelSignal, wxID_ANY, _("Impact"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	gSizer1->Add( m_staticText10, 0, wxALL, 5 );

	m_textImpact = new wxTextCtrl( m_panelSignal, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textImpact, 0, wxALL, 5 );

	m_staticText11 = new wxStaticText( m_panelSignal, wxID_ANY, _("Light Status"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	gSizer1->Add( m_staticText11, 0, wxALL, 5 );

	m_textLightStatus = new wxTextCtrl( m_panelSignal, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_textLightStatus, 0, wxALL, 5 );


	m_panelSignal->SetSizer( gSizer1 );
	m_panelSignal->Layout();
	gSizer1->Fit( m_panelSignal );
	m_notebookMessage->AddPage( m_panelSignal, _("Signal"), true );
	m_panel3 = new wxPanel( m_notebookMessage, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText12 = new wxStaticText( m_panel3, wxID_ANY, _("MMSI"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	gSizer2->Add( m_staticText12, 0, wxALL, 5 );

	m_textMMSI1 = new wxTextCtrl( m_panel3, wxID_ANY, _("0000"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textMMSI1, 0, wxALL, 5 );

	m_staticText13 = new wxStaticText( m_panel3, wxID_ANY, _("Country"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	gSizer2->Add( m_staticText13, 0, wxALL, 5 );

	m_textCountry1 = new wxTextCtrl( m_panel3, wxID_ANY, _("ZZ"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textCountry1, 0, wxALL, 5 );

	m_staticText14 = new wxStaticText( m_panel3, wxID_ANY, _("Fairway Section"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	gSizer2->Add( m_staticText14, 0, wxALL, 5 );

	m_textFairwaySection1 = new wxTextCtrl( m_panel3, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textFairwaySection1, 0, wxALL, 5 );

	m_staticText15 = new wxStaticText( m_panel3, wxID_ANY, _("Object Code"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	gSizer2->Add( m_staticText15, 0, wxALL, 5 );

	m_textObjectCode1 = new wxTextCtrl( m_panel3, wxID_ANY, _("ZZZ"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textObjectCode1, 0, wxALL, 5 );

	m_staticText16 = new wxStaticText( m_panel3, wxID_ANY, _("Hectometre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	gSizer2->Add( m_staticText16, 0, wxALL, 5 );

	m_textHectometre1 = new wxTextCtrl( m_panel3, wxID_ANY, _("0000"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer2->Add( m_textHectometre1, 0, wxALL, 5 );


	bSizer131->Add( gSizer2, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxVERTICAL );

	m_staticText17 = new wxStaticText( m_panel3, wxID_ANY, _("Text"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	m_staticText17->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer101->Add( m_staticText17, 0, wxALL, 5 );

	m_textText1 = new wxTextCtrl( m_panel3, wxID_ANY, _("Replace this.\n"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer101->Add( m_textText1, 0, wxALL|wxEXPAND, 5 );


	bSizer131->Add( bSizer101, 1, wxEXPAND, 5 );


	m_panel3->SetSizer( bSizer131 );
	m_panel3->Layout();
	bSizer131->Fit( m_panel3 );
	m_notebookMessage->AddPage( m_panel3, _("Text"), false );
	m_panel4 = new wxPanel( m_notebookMessage, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer21;
	gSizer21 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText121 = new wxStaticText( m_panel4, wxID_ANY, _("MMSI"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText121->Wrap( -1 );
	gSizer21->Add( m_staticText121, 0, wxALL, 5 );

	m_textMMSI2 = new wxTextCtrl( m_panel4, wxID_ANY, _("0000"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_textMMSI2, 0, wxALL, 5 );

	m_staticText131 = new wxStaticText( m_panel4, wxID_ANY, _("Country"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText131->Wrap( -1 );
	gSizer21->Add( m_staticText131, 0, wxALL, 5 );

	m_textCountry2 = new wxTextCtrl( m_panel4, wxID_ANY, _("ZZ"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_textCountry2, 0, wxALL, 5 );

	m_staticText141 = new wxStaticText( m_panel4, wxID_ANY, _("Fairway Section"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText141->Wrap( -1 );
	gSizer21->Add( m_staticText141, 0, wxALL, 5 );

	m_textFairwaySection2 = new wxTextCtrl( m_panel4, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_textFairwaySection2, 0, wxALL, 5 );

	m_staticText151 = new wxStaticText( m_panel4, wxID_ANY, _("Object Code"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText151->Wrap( -1 );
	gSizer21->Add( m_staticText151, 0, wxALL, 5 );

	m_textObjectCode2 = new wxTextCtrl( m_panel4, wxID_ANY, _("ZZZ"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_textObjectCode2, 0, wxALL, 5 );

	m_staticText161 = new wxStaticText( m_panel4, wxID_ANY, _("Hectometre"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText161->Wrap( -1 );
	gSizer21->Add( m_staticText161, 0, wxALL, 5 );

	m_textHectometre2 = new wxTextCtrl( m_panel4, wxID_ANY, _("0000"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_textHectometre2, 0, wxALL, 5 );

	m_staticText28 = new wxStaticText( m_panel4, wxID_ANY, _("Bridge Clearance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	gSizer21->Add( m_staticText28, 0, wxALL, 5 );

	m_textBridgeClearance = new wxTextCtrl( m_panel4, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_textBridgeClearance, 0, wxALL, 5 );

	m_staticText29 = new wxStaticText( m_panel4, wxID_ANY, _("Time to last measurement"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	gSizer21->Add( m_staticText29, 0, wxALL, 5 );

	m_textTime = new wxTextCtrl( m_panel4, wxID_ANY, _("722"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_textTime, 0, wxALL, 5 );

	m_staticText30 = new wxStaticText( m_panel4, wxID_ANY, _("Accuracy"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	gSizer21->Add( m_staticText30, 0, wxALL, 5 );

	m_textAccuracy = new wxTextCtrl( m_panel4, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer21->Add( m_textAccuracy, 0, wxALL, 5 );


	m_panel4->SetSizer( gSizer21 );
	m_panel4->Layout();
	gSizer21->Fit( m_panel4 );
	m_notebookMessage->AddPage( m_panel4, _("Bridge_clearance"), false );
	m_panel5 = new wxPanel( m_notebookMessage, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText31 = new wxStaticText( m_panel5, wxID_ANY, _("MMSI"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	gSizer11->Add( m_staticText31, 0, wxALL, 5 );

	m_textMMSI3 = new wxTextCtrl( m_panel5, wxID_ANY, _("00000"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textMMSI3, 0, wxALL, 5 );

	m_staticText21 = new wxStaticText( m_panel5, wxID_ANY, _("Country"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	gSizer11->Add( m_staticText21, 0, wxALL, 5 );

	m_textCountry3 = new wxTextCtrl( m_panel5, wxID_ANY, _("ZZ"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textCountry3, 0, wxALL, 5 );

	m_staticText41 = new wxStaticText( m_panel5, wxID_ANY, _("Gauge ID 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	gSizer11->Add( m_staticText41, 0, wxALL, 5 );

	m_textGauge1 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textGauge1, 0, wxALL, 5 );

	m_staticText51 = new wxStaticText( m_panel5, wxID_ANY, _("Water level Ref 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	gSizer11->Add( m_staticText51, 0, wxALL, 5 );

	m_textWaterRef1 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textWaterRef1, 0, wxALL, 5 );

	m_staticText61 = new wxStaticText( m_panel5, wxID_ANY, _("Water level value 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	gSizer11->Add( m_staticText61, 0, wxALL, 5 );

	m_textValue1 = new wxTextCtrl( m_panel5, wxID_ANY, _("-65536"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textValue1, 0, wxALL, 5 );

	m_staticText71 = new wxStaticText( m_panel5, wxID_ANY, _("Gauge ID 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	gSizer11->Add( m_staticText71, 0, wxALL, 5 );

	m_textGauge2 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textGauge2, 0, wxALL, 5 );

	m_staticText81 = new wxStaticText( m_panel5, wxID_ANY, _("Water level Ref 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	gSizer11->Add( m_staticText81, 0, wxALL, 5 );

	m_textWaterRef2 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textWaterRef2, 0, wxALL, 5 );

	m_staticText91 = new wxStaticText( m_panel5, wxID_ANY, _("Water level value 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	gSizer11->Add( m_staticText91, 0, wxALL, 5 );

	m_textValue2 = new wxTextCtrl( m_panel5, wxID_ANY, _("-65536"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textValue2, 0, wxALL, 5 );

	m_staticText101 = new wxStaticText( m_panel5, wxID_ANY, _("Gauge ID 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	gSizer11->Add( m_staticText101, 0, wxALL, 5 );

	m_textGauge3 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textGauge3, 0, wxALL, 5 );

	m_staticText111 = new wxStaticText( m_panel5, wxID_ANY, _("Water level Ref 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	gSizer11->Add( m_staticText111, 0, wxALL, 5 );

	m_textWaterRef3 = new wxTextCtrl( m_panel5, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textWaterRef3, 0, wxALL, 5 );

	m_staticText511 = new wxStaticText( m_panel5, wxID_ANY, _("Water level value 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText511->Wrap( -1 );
	gSizer11->Add( m_staticText511, 0, wxALL, 5 );

	m_textValue3 = new wxTextCtrl( m_panel5, wxID_ANY, _("-65536"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_textValue3, 0, wxALL, 5 );


	m_panel5->SetSizer( gSizer11 );
	m_panel5->Layout();
	gSizer11->Fit( m_panel5 );
	m_notebookMessage->AddPage( m_panel5, _("Water_level"), false );

	bSizer122->Add( m_notebookMessage, 1, wxEXPAND | wxALL, 5 );


	bSizer10->Add( bSizer122, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer82;
	fgSizer82 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer82->AddGrowableCol( 0 );
	fgSizer82->AddGrowableCol( 1 );
	fgSizer82->AddGrowableCol( 2 );
	fgSizer82->AddGrowableCol( 3 );
	fgSizer82->AddGrowableRow( 0 );
	fgSizer82->AddGrowableRow( 1 );
	fgSizer82->SetFlexibleDirection( wxVERTICAL );
	fgSizer82->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_buttonStandby = new wxButton( this, wxID_ANY, _("Data"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonStandby->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_buttonStandby->SetBackgroundColour( wxColour( 0, 255, 0 ) );
	m_buttonStandby->SetMinSize( wxSize( 50,-1 ) );

	fgSizer82->Add( m_buttonStandby, 1, wxALL|wxEXPAND, 2 );

	m_buttonMessages = new wxButton( this, wxID_ANY, _("Log"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonMessages->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	fgSizer82->Add( m_buttonMessages, 0, wxALL|wxEXPAND, 5 );

	m_button7 = new wxButton( this, wxID_ANY, _("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button7->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_button7->SetMinSize( wxSize( 50,-1 ) );

	fgSizer82->Add( m_button7, 1, wxALL|wxEXPAND, 2 );

	m_buttonSignal = new wxButton( this, wxID_ANY, _("Signal"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonSignal->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_buttonSignal->SetBackgroundColour( wxColour( 0, 255, 0 ) );
	m_buttonSignal->SetMinSize( wxSize( 50,-1 ) );

	fgSizer82->Add( m_buttonSignal, 1, wxALL|wxEXPAND, 2 );

	m_button71 = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button71->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_button71->SetMinSize( wxSize( 50,-1 ) );

	fgSizer82->Add( m_button71, 0, wxALL|wxEXPAND, 5 );

	m_button72 = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_button72->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_button72->SetMinSize( wxSize( 50,-1 ) );

	fgSizer82->Add( m_button72, 0, wxALL|wxEXPAND, 5 );

	m_button73 = new wxButton( this, wxID_ANY, _("List"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button73->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_button73->SetMinSize( wxSize( 50,-1 ) );

	fgSizer82->Add( m_button73, 0, wxALL|wxEXPAND, 5 );

	m_button74 = new wxButton( this, wxID_ANY, _("Item"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button74->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_button74->SetMinSize( wxSize( 50,-1 ) );

	fgSizer82->Add( m_button74, 0, wxALL|wxEXPAND, 5 );


	bSizer10->Add( fgSizer82, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer10 );
	this->Layout();
	m_timer1.SetOwner( this, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( aisRXBase::OnClose ) );
	m_toggleBtn1->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnToggleButton ), NULL, this );
	m_buttonStandby->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnData ), NULL, this );
	m_buttonMessages->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnLogging ), NULL, this );
	m_button7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnTest ), NULL, this );
	m_buttonSignal->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnSignalShow ), NULL, this );
	m_button73->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnMessageList ), NULL, this );
	m_button74->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnSelectMessage ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( aisRXBase::OnTimer ) );
}

aisRXBase::~aisRXBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( aisRXBase::OnClose ) );
	m_toggleBtn1->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnToggleButton ), NULL, this );
	m_buttonStandby->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnData ), NULL, this );
	m_buttonMessages->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnLogging ), NULL, this );
	m_button7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnTest ), NULL, this );
	m_buttonSignal->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnSignalShow ), NULL, this );
	m_button73->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnMessageList ), NULL, this );
	m_button74->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( aisRXBase::OnSelectMessage ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( aisRXBase::OnTimer ) );

}

aisRXPreferences::aisRXPreferences( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("AIS") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_cbTransmitAis = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Transmit"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_cbTransmitAis, 0, wxALL, 5 );

	m_cbAisToFile = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Save to file"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_cbAisToFile, 0, wxALL, 5 );


	sbSizer1->Add( fgSizer2, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("MMSI") ), wxVERTICAL );

	m_textCtrlMMSI = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_textCtrlMMSI, 0, wxALL, 5 );


	sbSizer1->Add( sbSizer2, 1, wxEXPAND, 5 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( sbSizer1->GetStaticBox(), wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( sbSizer1->GetStaticBox(), wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();

	sbSizer1->Add( m_sdbSizer1, 1, wxEXPAND, 5 );


	this->SetSizer( sbSizer1 );
	this->Layout();
	sbSizer1->Fit( this );

	this->Centre( wxBOTH );
}

aisRXPreferences::~aisRXPreferences()
{
}
