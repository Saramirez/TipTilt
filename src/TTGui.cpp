#include "../include/TTGui.hpp"

TTGui::TTGui( wxWindow* parent )
:
MainFrame( parent )
{
	player_p = new StreamPlayer(StreamPlayerPanel);
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
	if (!sControl_p->IsCorrecting())
		if(!sControlId->IsCapturing())
			sControl_p->StartCorrection();
		//TODO show can't correct because no capture
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

void TTGui::OnClickExit( wxCommandEvent& event )
{
	Close(true);
// TODO: Implement OnClickExit
}
