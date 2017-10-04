#include "../include/TTGui.hpp"

TTGui::TTGui( wxWindow* parent )
:
MainFrame( parent ),
dControl_p(new DisplayControl(StreamPlayerPanel, TTPositionPanel,
		&mtxProtectingBmpAndCamPanel, &mtxProtectingTTPositionsAndPanel))
{
}


void TTGui::OnSelectCalibrate(wxCommandEvent& event)
{
	if (sControl_p->IsCapturing())
		sControl_p->StopCapture();
	if (sControl_p->IsCorrecting())
		sControl_p->StopCorrection();
	Enable(false);
	sControl_p->CalibrateTT();
	Enable(true);
}

void TTGui::OnCaptureDeviceChoice(wxCommandEvent& event)
{
	if (sControl_p->IsCapturing())
		sControl_p->StopCapture();
	int choice = CamChoice->GetSelection();
	sControl_p->SetCamDevice(choice);
}

void TTGui::OnTTDeviceChoice(wxCommandEvent& event)
{
	if (sControl_p->IsCorrecting())
		sControl_p->StopCorrection();
	int choice = TTChoice->GetSelection();
	sControl_p->SetTTDevice(choice);
}

void TTGui::OnSelectCameraSettings(wxCommandEvent& event)
{
	std::system("guvcview -z");
	//std::system("v4l2ucp");
}

void TTGui::OnClickCapture( wxCommandEvent& event )
{
	if(!sControl_p->IsCapturing())
		sControl_p->StartCapture();
	else {
		sControl_p->StopCapture();
		wxClientDC dc(StreamPlayerPanel);

		if (!dc.IsOk())
			return;
		dc.Clear();	
	}
}

void TTGui::OnClickCorrection(wxCommandEvent& event)
{
	if (!sControl_p->IsCorrecting()){
		if(sControl_p->IsCapturing())
			sControl_p->StartCorrection();
	}
	else
		sControl_p->StopCorrection();
}

void TTGui::OnFramePaint(wxPaintEvent& event)
{
	mtxProtectingBmpAndCamPanel.lock();
	wxPaintDC dc(StreamPlayerPanel);

	if (!dc.IsOk()) {
		mtxProtectingBmpAndCamPanel.unlock();
		return;
	}


	wxBitmap bmp = dControl_p->bmp;

	if (!bmp.IsOk()) {
		mtxProtectingBmpAndCamPanel.unlock();
		return;
	}
	/*
	int x, y, w, h;
	dc.GetClippingBox(&x, &y, &w, &h);
	dc.DrawBitmap(bmp, x, y);
	*/
	dc.DrawBitmap(bmp, 0, 0);
	mtxProtectingBmpAndCamPanel.unlock();

	return;
}

void TTGui::OnTTPosPaint(wxPaintEvent& event)
{
	mtxProtectingTTPositionsAndPanel.lock();
	wxPaintDC dc(TTPositionPanel);

	if (!dc.IsOk()) {
		mtxProtectingTTPositionsAndPanel.unlock();
		return;
	}

	int w, h, x, y;
	x = dControl_p->TTPosX;
	y = dControl_p->TTPosY;
	dc.GetSize(&w, &h);
	dc.SetPen(wxPen(*wxRED_PEN));
	dc.DrawRectangle(w / 2 - 35, h / 2 - 35, 70, 70);
	dc.SetPen(wxPen(*wxBLACK_PEN));
	dc.CrossHair(w / 2, h / 2);
	dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawCircle(wxPoint(w / 2 + x, h / 2 + y), 5);

	mtxProtectingTTPositionsAndPanel.unlock();

	return;
}

void TTGui::OnThrshTextSet(wxCommandEvent& event)
{
	long newThresh;
	(event.GetString()).ToLong(&newThresh);
	sControl_p->SetThreshold((int)newThresh);
}

void TTGui::OnShowThresholdChecked(wxCommandEvent& event)
{
	sControl_p->ToggleShowThresh();
}

void TTGui::OnSimulateChecked(wxCommandEvent& event)
{
	sControl_p->ToggleSimulate();
}

void TTGui::OnGetStarSizeClicked(wxCommandEvent& event)
{
	double newStarRadius = sControl_p->GetStarSize();

	stringstream stream;
	stream << fixed << setprecision(1) << newStarRadius;

	wxString newStarRadiusString(stream.str());
	StrSzTxCtrl->ChangeValue(newStarRadiusString);
}

void TTGui::OnStrSzTextSet(wxCommandEvent& event)
{
	double newStarRadius;
	(event.GetString()).ToDouble(&newStarRadius);
	sControl_p->SetStarSize(newStarRadius);
}

void TTGui::OnDefaultClicked(wxCommandEvent& event)
{
	CamChoice->SetSelection(0);
	TTChoice->SetSelection(0);

	StrSzTxCtrl->ChangeValue(defaultStarRadius);
	double newStarRadius;
	defaultStarRadius.ToDouble(&newStarRadius);
	sControl_p->SetStarSize(newStarRadius);

	ThrsTxCtrl->ChangeValue(defaultThreshold);
	long newThresh;
	defaultThreshold.ToLong(&newThresh);
	sControl_p->SetThreshold((int)newThresh);
}

void TTGui::OnClickCenterTT(wxCommandEvent& event)
{
	if (sControl_p->IsCorrecting())
		sControl_p->StopCorrection();
	sControl_p->CenterTT();
}

void TTGui::OnClickExit( wxCommandEvent& event )
{
	if (sControl_p->IsCapturing())
		sControl_p->StopCapture();
	if (sControl_p->IsCorrecting())
		sControl_p->StopCorrection();
	
	Close(true);
// TODO: Implement OnClickExit
}
