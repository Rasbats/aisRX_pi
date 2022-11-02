#ifndef WIDGET_H
#define WIDGET_H

#include <wx/wx.h>
#include <wx/gdicmn.h>

class Signal 
{
public:
	wxVector<wxPoint> myPointList;
	wxVector<wxPoint> myLightList;
	wxVector<wxRect> myRectangleList;
	wxVector<int> mySignalColours;
	int mySignalForm;
	wxVector<wxColour> myColourList;

};

class Widget : public wxPanel
{
public:
  Widget(wxPanel *parent, int id, int signalForm, wxString signalLights);

  wxPanel *m_parent;

  Signal *signal_1;
  Signal *signal_2;
  Signal *signal_6;

  int mySignalForm;
  
  void OnPaint(wxPaintEvent& event);  
  void SetupSignal(int signalForm, wxString signalLights);
  void OnSignal(int signalForm);

  typedef wxVector<wxPoint> myPointList;
  myPointList points;

};

#endif