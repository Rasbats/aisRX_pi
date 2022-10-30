/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  aisRX Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                   *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#include "aisRXgui_impl.h"
#include "aisRX_pi.h"
#include <wx/progdlg.h>
#include <wx/wx.h>

#include "wx/textfile.h"
#include <stdio.h>
#include <wx/timer.h>
#include "signal.h"
#include "widget.h"
#include <memory>

/**************************************************************************/
/*          Some assorted utilities                                       */
/**************************************************************************/

wxString toSDMM(int NEflag, double a)
{
	short neg = 0;
	int d;
	long m;

	if (a < 0.0)
	{
		a = -a;
		neg = 1;
	}
	d = (int)a;
	m = (long)((a - (double)d) * 60000.0);

	if (neg)
		d = -d;

	wxString s;

	if (!NEflag)
		s.Printf(_T("%d %02ld.%03ld'"), d, m / 1000, m % 1000);
	else
	{
		if (NEflag == 1)
		{
			char c = 'N';

			if (neg)
			{
				d = -d;
				c = 'S';
			}

			s.Printf(_T("%03d %02ld.%03ld %c"), d, m / 1000, (m % 1000), c);
		}
		else if (NEflag == 2)
		{
			char c = 'E';

			if (neg)
			{
				d = -d;
				c = 'W';
			}
			s.Printf(_T("%03d %02ld.%03ld %c"), d, m / 1000, (m % 1000), c);
		}
	}
	return s;
}

Dlg::Dlg(wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style)
	: aisRXBase(parent, id, title, pos, size, style)
{
	this->Fit();
	dbg = false; // for debug output set to true

	m_bUsingWind = false;
	m_bUsingFollow = false;
	m_bInvalidPolarsFile = false;
	m_bInvalidGribFile = false;
	m_baisRXHasStarted = false;
	m_bDisplayStarted = false;

	bool m_bShowaisRX = true;
	m_bHaveMessageList = false;
	m_bHaveDisplay = false;
	m_bUpdateTarget = false; 

	wxFileConfig* pConf = GetOCPNConfigObject();

	if (pConf) {
		pConf->SetPath(_T("/Settings/aisRX_pi"));

		pConf->Read(_T("aisRXUseAis"), &m_bUseAis, 0);
		pConf->Read(_T("aisRXUseFile"), &m_bUseFile, 0);
		pConf->Read(_T("aisRXHECT"), &m_tMMSI, "12345");
	}

	AISTextList = new AIS_Text_Hash;
    pTextData = new AIS_Text_Data;

	m_pASMmessages1 = NULL;
	myAISdisplay = NULL;

}

inline const char * const BoolToString(bool b)
{
	return b ? "true" : "false";
}


void Dlg::OnMessageList(wxCommandEvent& event) {

	if (NULL == m_pASMmessages1) {		
	
		m_pASMmessages1 = new asmMessages(this, wxID_ANY, _T("BBM Messages"), wxPoint(100, 100), wxSize(300, 500), wxDEFAULT_DIALOG_STYLE |wxCLOSE_BOX| wxRESIZE_BORDER);
		CreateControlsMessageList();
		m_pASMmessages1->Show();
		m_bHaveMessageList = true;

		myTextDataCollection.clear();
		m_timer1.Start();
	}

	if (m_bHaveMessageList) {
		m_pASMmessages1->Show();
	}	
}

void Dlg::OnCloseList(wxCloseEvent& event) {

	wxMessageBox("closing");
}

void Dlg::OnLogging(wxCommandEvent& event) {
	
	if ( NULL == myAISdisplay) {		
		myAISdisplay = new AISdisplay(this, wxID_ANY, _T("AIS Logging"), wxPoint(20, 20), wxSize(550, 400), wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER);
		myAISdisplay->Show();
		m_bHaveDisplay = true;
	}

	if (m_bHaveDisplay) {
		myAISdisplay->Show();
	}
}

void Dlg::SetAISMessage(wxString &msg)
{
	m_message = msg;

	if (m_bHaveDisplay) {
		if (myAISdisplay->m_tbAISPause->GetValue()) {

			int mm = 0;
			int ms = 0;

			myAISdisplay->m_tcAIS->AppendText(msg);
		}				
	}

	Decode(msg);
}

void Dlg::SetNMEAMessage(wxString &msg) {

  wxString token[40];
  wxString s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
  token[0] = "";

  wxStringTokenizer tokenizer(msg, ",");
  token[0] = tokenizer.GetNextToken().Trim();  // !AIVDM or !xxBMM


  if (m_bHaveDisplay && token[0] == "!xxBBM") {
    if (myAISdisplay->m_tbAISPause->GetValue()) {
      int mm = 0;
      int ms = 0;

      myAISdisplay->m_tcAIS->AppendText(msg);
    }
  }
}
/*
vector<AIS_Target_Data>  Dlg::FindSignalData(int hect) {

	char **result;
	int n_rows;
	int n_columns;
	//myTestDataCollection.clear();

	wxString shect = wxString::Format("%i", hect);

	wxString sql = "SELECT lat,lon,hectomt, risindex FROM RIS where hectomt = " + shect;

	plugin->dbGetTable(sql, &result, n_rows, n_columns);
	wxArrayString objects;



	for (int i = 1; i <= n_rows; i++)
	{
		char *lat = result[(i * n_columns) + 0];
		char *lon = result[(i * n_columns) + 1];
		string risindex = result[(i * n_columns) + 3];

		wxString object_lat(lat, wxConvUTF8);

		wxString object_lon(lon, wxConvUTF8);

		//wxMessageBox(object_lat);
	   // wxMessageBox(object_lon);

		double value;
		object_lat.ToDouble(&value);
		myTestData.Lat = value;
		object_lon.ToDouble(&value);
		myTestData.Lon = value;
		myTestData.RISindex = risindex;
		myTestDataCollection.push_back(myTestData);
	}
	plugin->dbFreeResults(result);

	return myTestDataCollection;
}


vector<AIS_Target_Data>  Dlg::FindSignalRISindex(int hect) {

	char **result;
	int n_rows;
	int n_columns;
	mySignalCollection.clear();

	wxString shect = wxString::Format("%i", hect);

	wxString sql = "SELECT lat,lon,hectomt, risindex FROM RIS where hectomt = " + shect;

	plugin->dbGetTable(sql, &result, n_rows, n_columns);
	wxArrayString objects;



	for (int i = 1; i <= n_rows; i++)
	{
		char *lat = result[(i * n_columns) + 0];
		char *lon = result[(i * n_columns) + 1];
		string risindex = result[(i * n_columns) + 3];

		wxString object_lat(lat, wxConvUTF8);

		wxString object_lon(lon, wxConvUTF8);

		//wxMessageBox(object_lat);
	   // wxMessageBox(object_lon);

		double value;
		object_lat.ToDouble(&value);
		myTestData.Lat = value;
		object_lon.ToDouble(&value);
		myTestData.Lon = value;
		myTestData.RISindex = risindex;
		mySignalCollection.push_back(myTestData);
	}
	plugin->dbFreeResults(result);

	return mySignalCollection;
}
*/


/*
void Dlg::OnData(wxCommandEvent& event) {

	char **result;
	int n_rows;
	int n_columns;

	plugin->dbGetTable("SELECT lat,lon,hectomt FROM RIS where hectomt = 19214", &result, n_rows, n_columns);
	wxArrayString objects;



	for (int i = 1; i <= n_rows; i++)
	{
		char *lat = result[(i * n_columns) + 0];
		char *lon = result[(i * n_columns) + 1];

		wxString object_lat(lat, wxConvUTF8);

		wxString object_lon(lon, wxConvUTF8);

		double value;
		object_lat.ToDouble(&value);
		myTestData.Lat = value;
		object_lon.ToDouble(&value);
		myTestData.Lon = value;

		myTestDataCollection.push_back(myTestData);
	}
	plugin->dbFreeResults(result);


	wxString myObjectLat = wxString::Format("%f", myTestDataCollection.at(0).Lat);
	wxString myObjectLon = wxString::Format("%f", myTestDataCollection.at(0).Lon);

	JumpTo(myObjectLat, myObjectLon, 16000);

	Refresh();

}
*/
void Dlg::JumpTo(wxString lat, wxString lon, int scale)
{
	double mla, mlo;

	lat.ToDouble(&mla);
	lon.ToDouble(&mlo);
	JumpToPosition(mla, mlo, scale);

}

void Dlg::OnClose(wxCloseEvent& event)
{	
	plugin->OnaisRXDialogClose();
}

wxString Dlg::DateTimeToTimeString(wxDateTime myDT)
{
	wxString sHours, sMinutes, sSecs;
	sHours = myDT.Format(_T("%H"));
	sMinutes = myDT.Format(_T("%M"));
	sSecs = myDT.Format(_T("%S"));
	wxString dtss = sHours + sMinutes + sSecs;
	return dtss;
}

wxString Dlg::DateTimeToDateString(wxDateTime myDT)
{

	wxString sDay, sMonth, sYear;
	sDay = myDT.Format(_T("%d"));
	sMonth = myDT.Format(_T("%m"));
	sYear = myDT.Format(_T("%y"));

	return sDay + sMonth + sYear;
}


void Dlg::Decode(wxString sentence)
{

	wxString mySentence = sentence;

	if (mySentence.IsEmpty() || mySentence.IsNull()) {
		//wxMessageBox("No sentence has been entered");
		return;
	}

	if (mySentence.Mid(0, 6) != "!AIVDM") {
          // wxMessageBox("Invalid sentence");
          return;
        }

	string myMsg = parseNMEASentence(mySentence).ToStdString();

	const char* payload1 = myMsg.c_str();
	mylibais::Ais8 myDacFi(payload1, 0);

	int dac0 = myDacFi.dac;
	wxString outdac0 = wxString::Format("%i", dac0);
	//wxMessageBox(outdac0);

	int fi0 = myDacFi.fi;
	wxString outfi0 = wxString::Format("%i", fi0);
	//wxMessageBox(outfi0);

	switch (fi0) {
	case 26: {
		getAis8_200_26(myMsg);
		break;
	}
	case 44: {
		getAis8_200_44(myMsg);
		break;
	}
	}
}

void Dlg::OnTest(wxCommandEvent& event)
{
	wxString mySentence = plugin->m_pDialog->m_textCtrlTest->GetValue();

	if (mySentence.IsEmpty() || mySentence.IsNull()) {
		wxMessageBox("No sentence has been entered");
		return;
	}

	if (mySentence.Mid(0, 6) != "!AIVDM") {
		wxMessageBox("Invalid sentence");
		return;
	}
	string myMsg = parseNMEASentence(mySentence).ToStdString();

	const char* payload1 = myMsg.c_str();
	mylibais::Ais8 myDacFi(payload1, 0);

	int dac0 = myDacFi.dac;
	wxString outdac0 = wxString::Format("%i", dac0);
	wxMessageBox(outdac0);

	int fi0 = myDacFi.fi;
	wxString outfi0 = wxString::Format("%i", fi0);
	wxMessageBox(outfi0);

	switch (fi0) {
	case 26: {
		getAis8_200_26(myMsg);
		break;
	}
	case 44: {
		getAis8_200_44(myMsg);
		break;
	}
	}

}

wxString Dlg::parseNMEASentence(wxString& sentence)
{

	wxString token[40];
	wxString s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
	token[0] = _T("");

	wxStringTokenizer tokenizer(sentence, wxT(","));
	int i = 0;

	while (tokenizer.HasMoreTokens()) {
		token[i] = tokenizer.GetNextToken();
		i++;
	}
	if (token[0].Right(3) == _T("VDM")) {

		s5 = token[5];

		return s5;

	}
	return "999";
}

void Dlg::UpdateAISTargetList(void)
{
	if (m_bHaveMessageList) {
		
			int index = 0; 
			AIS_Text_Hash::iterator it;
			AIS_Text_Data *pAISTarget;
			AIS_Text_Hash *current_targets = new AIS_Text_Hash;

			current_targets = AISTextList;
			size_t z = current_targets->size();

			if (z == 0) {
				return;
			}

			m_pASMmessages1->m_pListCtrlAISTargets->DeleteAllItems();

			string h = "";
            int id = 0;

			for (it = (current_targets)->begin(); it != (current_targets)->end(); ++it, ++index) {

				pAISTarget = it->second;

				wxListItem item;
				item.SetId(id);
				m_pASMmessages1->m_pListCtrlAISTargets->InsertItem(item);
				for (int j = 0; j < 2; j++) {
					item.SetColumn(j);
					if (j == 0) {
						h = pAISTarget->Hect;						
						item.SetText(h);
						m_pASMmessages1->m_pListCtrlAISTargets->SetItem(item);
					}

					if (j == 1) {						
						string r = pAISTarget->TextIndex;
						item.SetText(r);
						m_pASMmessages1->m_pListCtrlAISTargets->SetItem(item);
					}
				}

				id++;
			}

#ifdef __WXMSW__

			m_pASMmessages1->m_pListCtrlAISTargets->Refresh(false);
			
#endif 

	}		
}

//  ***** Text Message *******************
void Dlg::getAis8_200_44(string rawPayload) {
    bool bnewtarget = false;
    bool bdecode_result = false;

	const char* payload = rawPayload.c_str();

	mylibais::Ais8_200_44 myRIS(payload, 0);

	int mm = myRIS.mmsi;
	wxString outmm = wxString::Format("%i", mm);
	//wxMessageBox(outmm);

	string myCountry = myRIS.country;
	//wxMessageBox(myCountry);

	int sect = myRIS.section;
	wxString xoutsect = wxString::Format("%i", sect);
        const char* moutsect = xoutsect.c_str();
        string outsect = moutsect;

	//wxMessageBox(outsect);

	string myObj = myRIS.object;
	//wxMessageBox(myObj);

	int myHect = myRIS.hectometre;
	wxString xouthect = wxString::Format("%i", myHect);
    const char* mouthect = xouthect.c_str();
        string outhect = mouthect;

	//wxMessageBox(outhect);

	string myText = myRIS.text;
	//wxMessageBox(myText);


	    pNewTextData = new AIS_Text_Data ;
        pNewTextData->Sector = outsect;
        pNewTextData->ObjCode = myObj;
        pNewTextData->Hect = outhect;

        pNewTextData->TextIndex = outsect + "_" + myObj + "_" + outhect;
        vector<AIS_Text_Data> textData;
        textData.push_back(*pNewTextData);

		//

        // Search the current AISTextList for an MMSI match
        AIS_Text_Hash::iterator it
            = AISTextList->find(textData.at(0).TextIndex);

        if (it == AISTextList->end()) // not found
        {
            pTextData->Sector = outsect;
            pTextData->ObjCode = myObj;
            pTextData->Hect = outhect;

            pTextData->TextIndex = outsect + "_" + myObj + "_" + outhect;

            (*AISTextList)[pTextData->TextIndex]
                = pTextData; // update the hash table entry

            bdecode_result = true;

        } else {

            // Not needed at present
            // pTargetData = it->second;          // find current entry
            // save a pointer to stale data
        }

        //  If the message was decoded correctly
        //  Update the AIS Text information
        if (bdecode_result) {
            m_bUpdateTarget = true;

            (*AISTextList)[pTextData->TextIndex]
                = pTextData; // update the hash table entry
            myTextDataCollection.push_back(*pTextData);

			m_notebookMessage->SetSelection(0);

            m_textMMSI1->SetValue(outmm);
            m_textCountry1->SetValue(myCountry);
            m_textFairwaySection1->SetValue(outsect);
            m_textObjectCode1->SetValue(myObj);
            m_textHectometre1->SetValue(outhect);
            m_textText1->SetValue(myText);

            GetParent()->Refresh();
        }
}

//  ***** Water Level ************
void Dlg::getAis8_200_26(string rawPayload) {

	const char* payload = rawPayload.c_str();

	mylibais::Ais8_200_26 myRIS(payload, 0);

	int mm = myRIS.mmsi;
	wxString outmm = wxString::Format("%i", mm);
	//wxMessageBox(outmm);

	wxString outcountry = myRIS.country;
	//wxMessageBox(outcountry);

	int id = myRIS.gaugeID_1;
	wxString outid = wxString::Format("%i", id);
	//wxMessageBox(outid);

	int level = myRIS.waterLevelRef_1;
	wxString outlevel = wxString::Format("%i", level);
	//wxMessageBox(outlevel);

	int value = myRIS.waterLevelValue_1;
	wxString outvalue = wxString::Format("%i", value);
	//wxMessageBox(outvalue);

	int id2 = myRIS.gaugeID_2;
	wxString outid2 = wxString::Format("%i", id2);
	//wxMessageBox(outid2);

	int level2 = myRIS.waterLevelRef_2;
	wxString outlevel2 = wxString::Format("%i", level2);
	//wxMessageBox(outlevel2);

	int value2 = myRIS.waterLevelValue_2;
	wxString outvalue2 = wxString::Format("%i", value2);
	//wxMessageBox(outvalue2);

	int id3 = myRIS.gaugeID_3;
	wxString outid3 = wxString::Format("%i", id3);
	//wxMessageBox(outid3);

	int level3 = myRIS.waterLevelRef_3;
	wxString outlevel3 = wxString::Format("%i", level3);
	//wxMessageBox(outlevel3);

	int value3 = myRIS.waterLevelValue_3;
	wxString outvalue3 = wxString::Format("%i", value3);
	//wxMessageBox(outvalue3);

	m_notebookMessage->SetSelection(3);

	m_textMMSI3->SetValue(outmm);
	m_textCountry3->SetValue(outcountry);
	m_textGauge1->SetValue(outid);
	m_textWaterRef1->SetValue(outlevel);
	m_textValue1->SetValue(outvalue);
	m_textGauge2->SetValue(outid2);
	m_textWaterRef2->SetValue(outlevel2);
	m_textValue2->SetValue(outvalue2);
	m_textGauge3->SetValue(outid3);
	m_textWaterRef3->SetValue(outlevel3);
	m_textValue3->SetValue(outvalue3);

	Refresh();
}

void Dlg::SetViewPort(PlugIn_ViewPort *vp)
{
	if (m_vp == vp)  return;

	m_vp = new PlugIn_ViewPort(*vp);
}

void Dlg::CreateControlsMessageList()
{
	int width;
	long lwidth;

	int dx = 20;

	width = dx * 6;
	if (m_pASMmessages1) {
		m_pASMmessages1->m_pListCtrlAISTargets->InsertColumn(tlTRK, _("Hectomtr"), wxLIST_FORMAT_LEFT, width);
		m_pASMmessages1->m_pListCtrlAISTargets->InsertColumn(tlNAME, _("TextIndex"), wxLIST_FORMAT_LEFT, width);
	}
}

void Dlg::OnTimer(wxTimerEvent& event)
{
	if (m_bHaveMessageList && m_pASMmessages1->IsShown()) {

			// Refresh AIS target list every 5 seconds to avoid blinking
		if (m_pASMmessages1->m_pListCtrlAISTargets && (0 == (g_tick % (5)))) {
			if (m_bUpdateTarget) {
				UpdateAISTargetList();
				m_bUpdateTarget = false;
				GetParent()->Refresh();
			}
		}
			g_tick++;
	}	
}

