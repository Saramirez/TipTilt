#include "../include/TTGui.hpp"

TTGui::TTGui( wxWindow* parent )
:
MainFrame( parent )
{
	player_p = new StreamPlayer(StreamPlayerPanel);
}

void TTGui::OnClickStart( wxCommandEvent& event )
{
	//sControl_p->StartCorrection();
	sControl_p->StartCapture();
// TODO: Implement OnClickStart
}

void TipTiltGUIMainFrame::OnFramePaint(wxPaintEvent& event)
{
	wxPaintDC dc(StreamPlayerPanel);

	if (!dc.IsOk())
		return;

	int x, y, w, h;

	//cout << "player bmp w, h: " << bmp.GetWidth() << ", " << bmp.GetHeight() << endl;


	dc.GetClippingBox(&x, &y, &w, &h);
	//cout << "x, y, w, h: " << x << ", " << y << ", " << w << ", " << h << endl;
	dc.DrawBitmap(player_p->bmp, x, y);

	//cout << "Bitmap Drawn" << endl;

	return;
}

void TTGui::OnClickExit( wxCommandEvent& event )
{
	Close(true);
// TODO: Implement OnClickExit
}
