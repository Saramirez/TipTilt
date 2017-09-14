#include "../include/TTGui.hpp"

TTGui::TTGui( wxWindow* parent )
:
MainFrame( parent )
{
	dControl_p = new DisplayControl(StreamPlayerPanel, TTPositionPanel,
		&mtxProtectingBmpAndCamPanel, &mtxProtectingTTPositionsAndPanel);
}

void TTGui::OnSelectCameraSettings(wxCommandEvent& event)
{
	std::system("guvcview -z");
	//std::system("v4l2ucp");
}

void TTGui::OnToggleCapture( wxCommandEvent& event )
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

void TTGui::OnToggleCorrection(wxCommandEvent& event)
{
	if (!sControl_p->IsCorrecting()){
		if(sControl_p->IsCapturing())
			sControl_p->StartCorrection();
		//TODO show can't correct because no capture
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
	//std::cout << event.GetString() << endl;
}

void TTGui::OnShowThresholdChecked(wxCommandEvent& event)
{
	//std::cout << "Toggle show threshold" << endl;
	sControl_p->ToggleShowThresh();
	// TODO: Implement OnShowThresholdChecked
}

void TTGui::OnGetStarSizeClicked(wxCommandEvent& event)
{
	double newStarRadius = sControl_p->GetStarSize();

	stringstream stream;
	stream << fixed << setprecision(1) << newStarRadius;

	wxString newStarRadiusString(stream.str());
	//newStarRadiusString << newStarRadius;
	StrSzTxCtrl->ChangeValue(newStarRadiusString);
	// TODO: Implement OnGetStarSizeClicked
}

void TTGui::OnStrSzTextSet(wxCommandEvent& event)
{
	double newStarRadius;
	(event.GetString()).ToDouble(&newStarRadius);
	sControl_p->SetStarSize(newStarRadius);
	//std::cout << event.GetString() << endl;
}

void TTGui::OnDefaultClicked(wxCommandEvent& event)
{
	// TODO: Implement OnDefaultClicked
}

void TTGui::OnClickExit( wxCommandEvent& event )
{
	Close(true);
// TODO: Implement OnClickExit
}
