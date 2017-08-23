#include "../include/wxStreamPlayer.hpp"
#include "../include/wxStreamThread.hpp"

#include <iostream>

using namespace std;

BEGIN_EVENT_TABLE(wxStreamPlayer, wxWindow)
	EVT_PAINT(wxStreamPlayer::OnPaint)
	EVT_COMMAND(wxID_ANY, FRAME_READY, wxStreamPlayer::OnFrameReady)
END_EVENT_TABLE()

wxStreamPlayer::wxStreamPlayer(wxWindow* _parent, const wxPoint& _position, const wxSize& _size, wxBitmap * _wxbitmap_p, wxMutex * _mtxProtectingBitmap_p)
	: wxWindow(_parent, -1, _position, _size, wxSIMPLE_BORDER){

 	parent = _parent;
	wxbitmap_p = _wxbitmap_p;
	mtxProtectingBitmap_p = _mtxProtectingBitmap_p;
}

void wxStreamPlayer::OnFrameReady(wxCommandEvent& evt){
	Refresh(FALSE);
	Update();
	cout << "GRRR" << endl;
}

void wxStreamPlayer::OnPaint(wxPaintEvent& event){
	wxPaintDC dc(this);

	if(!dc.IsOk())
		return;

	int x, y, w, h;

	dc.GetClippingBox(&x, &y, &w, &h);
	mtxProtectingBitmap_p->Lock();
	dc.DrawBitmap(wxbitmap, x, y);
	mtxProtectingBitmap_p->Unlock();

	return;
}
