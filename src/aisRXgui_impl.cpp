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

#include <memory>

class GribRecordSet;

using mylibais::AisMsg;
using std::unique_ptr;
using namespace mylibais;


void assign(char* dest, char* arrTest2) { strcpy(dest, arrTest2); }

#define BUFSIZE 0x10000

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

    wxFileConfig* pConf = GetOCPNConfigObject();

    if (pConf) {
        pConf->SetPath(_T("/Settings/aisRX_pi"));

        pConf->Read(_T("aisRXUseAis"), &m_bUseAis, 0);
        pConf->Read(_T("aisRXUseFile"), &m_bUseFile, 0);
        pConf->Read(_T("aisRXMMSI"), &m_tMMSI, "12345");
    }

	AISTargetList = new AIS_Target_Hash;
	AISTargetNamesC = new AIS_Target_Name_Hash;
    AISTargetNamesNC = new AIS_Target_Name_Hash;
	pTargetData = new AIS_Target_Data;
	
}

namespace mylibais {
	template <typename T, typename... Args>
	std::unique_ptr<T> MakeUnique(Args &&... args) {
		//wxMessageBox("here");
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}


	unique_ptr<AisMsg>CreateAisMsg8(const string &body, const int fill_bits) {
		mylibais::Ais8 msg(body.c_str(), fill_bits);
		int dac = msg.fi;
		wxString dacs = wxString::Format("%i", dac);
		//wxMessageBox(dacs);

		

		return MakeUnique<mylibais::Ais8_200_44>(body.c_str(), fill_bits);

	}



	unique_ptr<AisMsg> CreateAisMsg(const string &body, const int fill_bits) {


		string mybody = body;
		wxMessageBox(mybody);

		int fill = fill_bits;
		wxString fills = wxString::Format("%i", fill);
		wxMessageBox(fills);

		Ais8 msg(body.c_str(), fill_bits);

		

		int dac = msg.dac;
		wxString dacs = wxString::Format("%i", dac);
		wxMessageBox(dacs);

		int fi = msg.fi;
		wxString fis = wxString::Format("%i", fi);
		wxMessageBox(fis);

		return CreateAisMsg8(body, fill_bits);
	}




} // mylibais


AIS_Target_Data* Dlg::Get_Target_Data_From_MMSI( int mmsi )
{
	int sz = AISTargetList->count(pTargetData->MMSI);

	wxString testCount = wxString::Format("%i", sz);
	wxMessageBox(testCount);

	
	if( AISTargetList->find( mmsi ) == AISTargetList->end() )     // if entry does not exist....
    return NULL;
    else
        return ( *AISTargetList )[mmsi];          // find current entry
}

void Dlg::SetAISMessage(wxString &msg) {
	
	if (NULL != m_pAISdialog) {
		if (!m_pAISdialog->m_tbAISPause->GetValue()) {

			int mm = 0;
			int ms = 0;

			m_pAISdialog->m_tcAIS->AppendText(msg);
			

			wxString token[40];
			wxString s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
			token[0] = _T("");

			wxStringTokenizer tokenizer(msg, wxT(","));
			int i = 0;

			while (tokenizer.HasMoreTokens()) {
				token[i] = tokenizer.GetNextToken();
				i++;
			}
			if (token[0].Right(3) == _T("VDM")) {
				s5 = token[5];
			}
			m_sPayload = s5.ToStdString();

			//wxMessageBox(m_sPayload, "test");
/*
			unique_ptr<AisMsg> myMsg;

			myMsg = CreateAisMsg(myMessage,0);
			mm = myMsg->mmsi;
			ms = myMsg->message_id;			

			wxString aisRXmmsi = SetaisRXMessage(myMessage);

			aisRXmmsi += "; ";

			AisBitset bs;
			const char* load = s5;

			bs.ParseNmeaPayload(load, 0);
			AisPoint myPt;
			myPt = bs.ToAisPoint(164, 55);

			double lat = myPt.lat_deg;
			double lon = myPt.lng_deg;
            
			if (ms != NULL)	pTargetData->MMSI = mm;
			else pTargetData->MMSI = 0;

			pTargetData->MID = ms;
			//pTargetData->Lat = lat;
			//pTargetData->Lon = lon;

			 ( *AISTargetList )[pTargetData->MMSI] = pTargetData;			 

			wxString out(wxString::Format(("%f"), lat));
			wxString outlon(wxString::Format(("%f"), lon));
			wxString result = aisRXmmsi + out + "; " + outlon;

			m_pAISdialog->m_tcAIS->AppendText(result + "\r\n");*/
		}
	}
	
}

wxString Dlg::SetaisRXMessage(string &msg) {
	unique_ptr<AisMsg> myMsg;

	//AIS_Bitstring* myBits;

	string payload;
	//   !AIVDM,1,1,,A,E>j4e>@LtqHIpHHLh@@@@@@@@@@0Vei<=iWL000000N2P0,4*05
	//payload = "E>j4e>@LtqHIpHHLh@@@@@@@@@@0Vei<=iWL000000N2P0"; //aisRX
	payload = msg;
	//string output;

	// myMsg = CreateAisMsg(payload,0);
	 int mm = myMsg->mmsi;
	 int ms = myMsg->message_id;

	 wxString outstring(wxString::Format(("%i"), mm));
	 return outstring;
	// wxMessageBox(outString);

	//wxString paystring = payload;

	//  Create the bit accessible string
	///AIS_Bitstring strbit(paystring.mb_str());


	///char testOut;

	///strbit.GetStr(10, 20, &testOut, 7);
	///wxMessageBox(testOut);
	/*
	AisBitset bs;
	const char* load = "E>j4e>@LtqHIpHHLh@@@@@@@@@@0Vei<=iWL000000N2P0";
	bs.ParseNmeaPayload(load, 0);
	AisPoint myPt;
	myPt = bs.ToAisPoint(164, 55);

	double lat = myPt.lat_deg;

	wxString out(wxString::Format(("%f"), lat));
	wxMessageBox(out);*/
}

void Dlg::OnAuto(wxCommandEvent& event)
{
	
    ///m_iMMSI = 992030009;
	///wxString timeStamp = wxString::Format(_T("%i"), wxGetUTCTime());

	//wxString myNMEAais = myAIS->nmeaEncode(_T("18"), 1234, _T("5"), 5,
    //    49.0, 17.0, 270, 270, _T("B"), timeStamp);

	
	///wxString myNMEAaisRX = myAIS->nmeaEncodeaisRX("21", m_iMMSI, "", 48.148, 16.9149, "A", timeStamp);
	///wxMessageBox(myNMEAaisRX);
	int x = plugin->m_hr_dialog_x + 200;
	int y = plugin->m_hr_dialog_y;
	
	m_pAISdialog = new AISdisplay(this->GetParent());
	m_pAISdialog->Show();
	m_pAISdialog->m_tbAISPause->SetValue(false);

	m_bDisplayStarted = true;
    m_bAuto = true;

    m_buttonStandby->SetBackgroundColour(wxColour(255, 0, 0));
    m_buttonAuto->SetBackgroundColour(wxColour(0, 255, 0));
    Refresh();
}

void Dlg::OnStandby(wxCommandEvent& event) { GoToStandby(); }

void Dlg::GoToStandby()
{

    m_bAuto = false;

    m_buttonStandby->SetBackgroundColour(wxColour(0, 255, 0));
    m_buttonAuto->SetBackgroundColour(wxColour(255, 255, 255));
    Refresh();
}

void Dlg::OnClose(wxCloseEvent& event)
{

    plugin->OnaisRXDialogClose();
}


wxString Dlg::makeCheckSum(wxString mySentence)
{
    size_t i;
    unsigned char XOR;

    wxString s(mySentence);
    wxCharBuffer buffer = s.ToUTF8();
    char* Buff = buffer.data(); // data() returns const char *
    size_t iLen = strlen(Buff);
    for (XOR = 0, i = 0; i < iLen; i++)
        XOR ^= (unsigned char)Buff[i];
    stringstream tmpss;
    tmpss << hex << (int)XOR << endl;
    wxString mystr = tmpss.str();
    return mystr;
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


void Dlg::OnTest(wxCommandEvent& event)
{
	
	//string myMessage = "8000000j:@2`004dBhpb0WVGsP00";   // m_sPayload;  //Ais8_200_41
	string myMessage = "8000h>@j;02aR`Lt8S60CfI@E=@TpN1@PF15DT<f098uLr0HuR2222222220"; ////Ais8_200_44 ****myTX

	//string myMessage = "8000000j;02`004<8tS4`eP85D588DU@Dr04r1=A8tlhDUADpLDp";  // From manufacturer report

	wxString myS(myMessage);

	wxMessageBox(myS);

	mylibais::AisBitset bs;
	//const char* load = myMessage.c_str();
	int num_bits;
	//bs.ParseNmeaPayload(load, 0);
	//int i = bs.ToInt(71, 17);
	
	const char* payload =  myMessage.c_str();
	//num_bits = sizeof payload;
	wxString outnum = wxString::Format("%i", num_bits);
   // wxMessageBox(outnum);


	mylibais::Ais8_200_44 myRIS(payload,0);

	int dac = myRIS.dac;
	wxString outdac = wxString::Format("%i", dac);
	wxMessageBox(outdac);

	int fi = myRIS.fi;
	wxString outfi = wxString::Format("%i", fi);
	wxMessageBox(outfi);

	int mm = myRIS.mmsi;
	wxString outmm = wxString::Format("%i", mm);
	//wxMessageBox(outmm);

	int myHect = myRIS.hectometre;
	wxString outhect = wxString::Format("%i", myHect);
    //wxMessageBox(outhect);

	string myCountry = myRIS.country;
	//wxMessageBox(myCountry);

	string myObj = myRIS.object;
    wxMessageBox(myObj);

	string myText = myRIS.text;
	wxMessageBox(myText);

	//int mid = myMsg->message_id;
	//wxString outID = wxString::Format("%i", myID);
	//AIS_Target_Data* myData;
	//myData = Get_Target_Data_From_MMSI(992030009);
	//int myID = myRis->version; // myData->MID;

	//wxMessageBox(outID);
	//wxMessageBox(myCountry);
}


