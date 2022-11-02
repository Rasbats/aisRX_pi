#ifndef SIGNAL_H
#define SIGNAL_H

#include <wx/wx.h>
#include "widget.h"

class Signalling : public wxFrame
{
public:
  Signalling(const wxString& title, int signalForm, wxString signalLights);
  int signalForm;
  void OnScroll(wxScrollEvent& event);
  int GetCurWidth();

  wxTextCtrl* m_textCtrl1;
  wxTextCtrl* m_textCtrl2;
  wxSlider *m_slider;
  Widget *m_wid;

  int cur_width;

};

#endif
