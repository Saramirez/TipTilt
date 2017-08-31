#include "../include/wxStreamPlayer.hpp"

#include <iostream>

using namespace std;

BEGIN_EVENT_TABLE(wxStreamPlayer, wxWindow)
	EVT_PAINT(wxStreamPlayer::OnPaint)
END_EVENT_TABLE()

wxStreamPlayer::wxStreamPlayer(wxWindow* _parent, const wxPoint& _position, const wxSize& _size)
	: wxWindow(_parent, -1, _position, _size, wxSIMPLE_BORDER){

 	parent = _parent;
}

void wxStreamPlayer::DisplayFrame(Mat frame) {
	img = wxImage(frame.cols,
		frame.rows,
		frame.data,
		TRUE);
	bmp = wxBitmap(img);

	Refresh(FALSE);
	Update();
}

void wxStreamPlayer::OnPaint(wxPaintEvent& event){
	//cout << "Recieved ON_PAINT event" << endl;
	wxPaintDC dc(this);

	if(!dc.IsOk())
		return;

	int x, y, w, h;

	//cout << "player bmp w, h: " << bmp.GetWidth() << ", " << bmp.GetHeight() << endl;
	

	dc.GetClippingBox(&x, &y, &w, &h);
	//cout << "x, y, w, h: " << x << ", " << y << ", " << w << ", " << h << endl;
	dc.DrawBitmap(bmp, x, y);

	//cout << "Bitmap Drawn" << endl;

	return;
}
