#include "../include/StreamPlayer.hpp"

#include <iostream>


StreamPlayer::StreamPlayer(wxPanel * _panel_p){
	panel_p = _panel_p;
}

void StreamPlayer::DisplayFrame(Mat frame) {
	img = wxImage(frame.cols,
		frame.rows,
		frame.data,
		TRUE);
	bmp = wxBitmap(img);

	//panel_p->Refresh(FALSE);
	panel_p->Refresh();
	panel_p->Update(); // Se vuelve inestable la gui al resizesiarla
	 

}
