#include "../include/TTGui.hpp"

TTGui::TTGui( wxWindow* parent )
:
MainFrame( parent )
{
	player_p = new StreamPlayer(StreamPlayerPanel);
}

void TTGui::OnSelectCameraSettings(wxCommandEvent& event)
{
	//std::system("guvcview -z");
	std::system("v4l2ucp");
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
	wxPaintDC dc(StreamPlayerPanel);

	if (!dc.IsOk())
		return;

	int x, y, w, h;

	//cout << "player bmp w, h: " << bmp.GetWidth() << ", " << bmp.GetHeight() << endl;

	wxBitmap bmp = player_p->bmp;

	if (!bmp.IsOk())
		return;

	dc.GetClippingBox(&x, &y, &w, &h);
	//cout << "x, y, w, h: " << x << ", " << y << ", " << w << ", " << h << endl;
	dc.DrawBitmap(bmp, x, y);

	//cout << "Bitmap Drawn" << endl;

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
