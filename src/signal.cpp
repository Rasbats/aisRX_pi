#include "signal.h"
#include "widget.h"

int ID_SLIDER = 1;

Signalling::Signalling(const wxString& title, int signalForm, wxString signalLights)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400))
{

  int newSignalForm = signalForm;
  wxString mySignalForm = wxString::Format("%i", newSignalForm);

  wxString mySignalLights = signalLights;

  cur_width = 75;

  wxPanel *panel = new wxPanel(this, wxID_ANY);
  wxPanel *centerPanel = new wxPanel(panel, wxID_ANY);

  m_textCtrl1 = new wxTextCtrl( centerPanel, wxID_ANY, mySignalForm, wxDefaultPosition, wxDefaultSize, 0 );
  m_textCtrl2 = new wxTextCtrl( centerPanel, wxID_ANY, mySignalLights, wxDefaultPosition, wxDefaultSize, 0 );  
  
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);

  m_wid = new Widget(panel, wxID_ANY, signalForm, signalLights);
  hbox->Add(m_wid, 1, wxEXPAND);

  hbox2->Add(centerPanel, 0, wxEXPAND);
  hbox3->Add(m_textCtrl1, 0, wxTOP | wxLEFT, 35);
  hbox3->Add(m_textCtrl2, 0, wxTOP | wxLEFT, 35);

  centerPanel->SetSizer(hbox3);

  vbox->Add(hbox2, 1, wxEXPAND);
  vbox->Add(hbox, 0, wxEXPAND);

  panel->SetSizer(vbox);

  Centre();
}

void Signalling::OnScroll(wxScrollEvent& WXUNUSED(event))
{
 cur_width = m_slider->GetValue();
 m_wid->Refresh();
}


int Signalling::GetCurWidth() 
{
 return cur_width;
}
