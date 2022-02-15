#include <wx/wx.h>
#include "widget.h"
#include "signal.h"

int num[] = { 75, 150, 225, 300, 375, 450, 525, 600, 675 };
int asize = sizeof(num)/sizeof(num[1]);

#define NUM_1 11
#define NUM_2 11
#define NUM_6 14

static wxPoint SignalArray_1[NUM_1] = { wxPoint( 40, 100), wxPoint( 40, 95),
        wxPoint( 30, 95 ), wxPoint( 50, 95 ), wxPoint( 40, 95 ), wxPoint( 40, 70 ), wxPoint( 10, 70 ), 
	    wxPoint( 10, 10 ), wxPoint( 70, 10 ), wxPoint( 70, 70 ), wxPoint( 40, 70 ) };

static wxPoint SignalArray_2[NUM_2] = { wxPoint( 70, 100), wxPoint( 70, 95),
        wxPoint( 60, 95 ), wxPoint( 80, 95 ), wxPoint( 70, 95 ), wxPoint( 70, 70 ), wxPoint( 10, 70 ), 
	    wxPoint( 10, 10 ), wxPoint( 130, 10 ), wxPoint( 130, 70 ), wxPoint( 70, 70 ) };

static wxPoint SignalArray_6[NUM_6] = { wxPoint( 90, 160), wxPoint( 90, 155),
        wxPoint( 80, 155 ), wxPoint( 100, 155 ), wxPoint( 90, 155 ), wxPoint( 90, 130 ), wxPoint( 10, 130 ), 
	    wxPoint( 10, 10 ), wxPoint( 70, 10 ), wxPoint( 70, 70 ), wxPoint( 10, 70),
	    wxPoint( 190, 70 ), wxPoint( 190, 130 ), wxPoint( 90, 130 ) };

static wxColour ColourArray[8] = {"LIGHT GREY", "LIGHT GREY", "WHITE", "YELLOW", "GREEN", "RED", "FLW", "FLY" };

Widget::Widget(wxPanel *parent, int id, int signalForm, wxString signalLights)
      : wxPanel(parent, id, wxDefaultPosition, wxSize(-1, 300), wxSUNKEN_BORDER)
{
 
  m_parent = parent;

  Connect(wxEVT_PAINT, wxPaintEventHandler(Widget::OnPaint));

  mySignalForm = signalForm;
  wxString msg = wxString::Format("%i", mySignalForm);
  //wxMessageBox(msg);

  SetupSignal(signalForm, signalLights);

}

void Widget::SetupSignal(int signalForm, wxString signalLights) {

	
	//signalForm = 6;
	switch (signalForm) {
		case 1: {
			signal_1 = new Signal;
			//Usage

			for (int i = 0; i < NUM_1; i++) {
				points.push_back(SignalArray_1[i]);
			}

			wxRect rect = wxRect(10, 10, 70, 70);
			wxPoint lightCentre(40, 40);

			signal_1->myPointList = points;
			signal_1->myRectangleList.push_back(rect);
			signal_1->myLightList.push_back(lightCentre);

			signal_1->mySignalForm = signalForm;

			wxString stringLights = signalLights;
			wxString myLight;
			int strLength = stringLights.length();
			for (int ls = 0; ls < strLength ; ls++) {
				myLight = stringLights.Mid(ls, 1);
				int myLightNumber = atoi(myLight); // for 0 based array
				wxColour myC = wxColour(ColourArray[myLightNumber]);
				signal_1->myColourList.push_back(myC);
			}

			//signal_1->mySignalLights = signalLights;
			break;
		}
		case 2: {
			signal_2 = new Signal;
			//Usage

			for (int i = 0; i < NUM_2; i++) {
				points.push_back(SignalArray_2[i]);
			}
			signal_2->myPointList = points;
			
			wxRect rect = wxRect(10, 10, 130, 70);
			signal_2->myRectangleList.push_back(rect);
			
			wxPoint lightCentre1(40, 40);
			signal_2->myLightList.push_back(lightCentre1);
			wxPoint lc2(100, 40);
			signal_2->myLightList.push_back(lc2);

			signal_2->mySignalForm = signalForm;

			wxString stringLights = signalLights;
			wxString myLight;
			int strLength = stringLights.length();
			for (int ls = 0; ls < strLength ; ls++) {
				myLight = stringLights.Mid(ls, 1);
				int myLightNumber = atoi(myLight); // for 0 based array
				wxColour myC = wxColour(ColourArray[myLightNumber]);
				signal_2->myColourList.push_back(myC);
			}

			break;
		}
		case 6: {
			signal_6 = new Signal;
			//Usage

			for (int i = 0; i < NUM_6; i++) {
				points.push_back(SignalArray_6[i]);
			}
			signal_6->myPointList = points;

			wxRect rect1 = wxRect(10, 10, 70, 70);
			signal_6->myRectangleList.push_back(rect1);
			wxRect rect2 = wxRect(10, 70, 180, 60);
			signal_6->myRectangleList.push_back(rect2);

			wxPoint lightCentre1(40, 40);
			signal_6->myLightList.push_back(lightCentre1);
			wxPoint lc2(40, 100);
			signal_6->myLightList.push_back(lc2);
			wxPoint lc3(100, 100);
			signal_6->myLightList.push_back(lc3);
			wxPoint lc4(160, 100);
			signal_6->myLightList.push_back(lc4);

			signal_6->mySignalForm = signalForm;

			
			wxString stringLights = signalLights;
			wxString myLight;
			int strLength = stringLights.length();
			for (int ls = 0; ls < strLength; ls++) {
				myLight = stringLights.Mid(ls, 1);
				int myLightNumber = atoi(myLight);
				wxColour myC = ColourArray[myLightNumber];
				signal_6->myColourList.push_back(myC);
			}
			
			break;
		}
	}
}

void Widget::OnSignal(int signalForm) {	
	int Form = signalForm;
	switch (Form) {
		case 1: {
		
		wxVector<wxPoint>myPoints = signal_1->myPointList;
		int numPoints = myPoints.size();

		wxPaintDC dc(this);
		wxPen signalPen;
		signalPen.SetWidth(2);
		signalPen.SetColour(90, 80, 60);
		dc.SetPen(signalPen);

		float xt = myPoints[0].x;
		float yt = myPoints[0].y;

		int x1 = xt;
		int y1 = yt;

		int x2, y2;

		x2 = x1;
		y2 = y1;

		x2 = myPoints[1].x;
		y2 = myPoints[1].y;

		dc.DrawLine(x1, y1, x2, y2);

		// Walk thru the point list
		for (int ip = 1; ip < numPoints; ip++) {
			x2 = myPoints[ip].x;
			y2 = myPoints[ip].y;

			dc.DrawLine(x1, y1, x2, y2);

			x1 = x2;
			y1 = y2;
		}

		wxPoint circleCentre = signal_1->myLightList.at(0);
		// draw light
		dc.DrawCircle(circleCentre, 20);


		wxRect myRect = signal_1->myRectangleList.at(0);
		// fill rectangle of light
		dc.SetBrush(wxBrush(wxColour("LIGHT GREY")));
		dc.DrawRectangle(myRect);



		// draw light circle
		dc.SetPen(wxPen(wxColour("BLACK")));
		dc.DrawCircle(circleCentre, 20);

		wxVector<wxColour>myColours = signal_1->myColourList;
		wxColour lightColour = myColours.at(0);
		
		dc.SetBrush(wxBrush(lightColour));
		dc.DrawCircle(circleCentre, 20);
		break;
		}

		case 2: {
		
		wxVector<wxPoint>myPoints = signal_2->myPointList;
		int numPoints = myPoints.size();

		wxPaintDC dc(this);
		wxPen signalPen;
		signalPen.SetWidth(2);
		signalPen.SetColour(90, 80, 60);
		dc.SetPen(signalPen);

		float xt = myPoints[0].x;
		float yt = myPoints[0].y;

		int x1 = xt;
		int y1 = yt;

		int x2, y2;

		x2 = x1;
		y2 = y1;

		x2 = myPoints[1].x;
		y2 = myPoints[1].y;

		dc.DrawLine(x1, y1, x2, y2);

		// Walk thru the point list
		for (int ip = 1; ip < numPoints; ip++) {
			x2 = myPoints[ip].x;
			y2 = myPoints[ip].y;

			dc.DrawLine(x1, y1, x2, y2);

			x1 = x2;
			y1 = y2;
		}

		wxPoint circleCentre = signal_2->myLightList.at(0);
		// draw light
		dc.DrawCircle(circleCentre, 20);


		wxRect myRect = signal_2->myRectangleList.at(0);
		// fill rectangle of light
		dc.SetBrush(wxBrush(wxColour("LIGHT GREY")));
		dc.DrawRectangle(myRect);

		int lz = signal_2->myLightList.size();
		for (int lr = 0; lr < lz; lr++) {
			// draw light circle
			circleCentre = signal_2->myLightList.at(lr); 

			dc.SetPen(wxPen(wxColour("BLACK")));
			dc.DrawCircle(circleCentre, 20);

			wxVector<wxColour>myColours = signal_2->myColourList;
		    wxColour lightColour = myColours.at(lr);

			dc.SetBrush(wxBrush(lightColour));
			dc.DrawCircle(circleCentre, 20);
		}		
		break;
		}

		case 6: {
		
		wxVector<wxPoint>myPoints = signal_6->myPointList;
		int numPoints = myPoints.size();


		wxPaintDC dc(this);
		wxPen signalPen;
		signalPen.SetWidth(2);
		signalPen.SetColour(90, 80, 60);
		dc.SetPen(signalPen);

		float xt = myPoints[0].x;
		float yt = myPoints[0].y;

		int x1 = xt;
		int y1 = yt;

		int x2, y2;

		x2 = x1;
		y2 = y1;

		x2 = myPoints[1].x;
		y2 = myPoints[1].y;

		dc.DrawLine(x1, y1, x2, y2);

		// Walk thru the point list
		for (int ip = 1; ip < numPoints; ip++) {
			x2 = myPoints[ip].x;
			y2 = myPoints[ip].y;

			dc.DrawLine(x1, y1, x2, y2);

			x1 = x2;
			y1 = y2;
		}

		wxRect myRect;
		wxPoint circleCentre;  // = signal_6->myLightList.at(0);
		// draw light
		//dc.DrawCircle(circleCentre, 20);

		int rlz = signal_6->myRectangleList.size();
		for (int ir = 0; ir < rlz; ir++) {
			myRect = signal_6->myRectangleList.at(ir);
			// fill rectangle of light
			dc.SetBrush(wxBrush(ColourArray[1]));
			dc.DrawRectangle(myRect);
		}

		int lz = signal_6->myLightList.size();
		for (int lr = 0; lr < lz; lr++) {
			// draw light circle
			circleCentre = signal_6->myLightList.at(lr); 

			dc.SetPen(wxPen(wxColour("BLACK")));
			dc.DrawCircle(circleCentre, 20);

			wxVector<wxColour>myColours = signal_6->myColourList;
		    wxColour lightColour = myColours.at(lr);

			dc.SetBrush(wxBrush(lightColour));
			dc.DrawCircle(circleCentre, 20);
		}
		break;
		}

	}
}


void Widget::OnPaint(wxPaintEvent& event)
{
  wxFont font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));


  OnSignal(mySignalForm);
}