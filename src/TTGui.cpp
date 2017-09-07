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
	else
		sControl_p->StopCapture();
}

void TTGui::OnToggleCorrection(wxCommandEvent& event)
{
	if (!sControl_p->IsCorrecting())
		sControl_p->StartCorrection();
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
