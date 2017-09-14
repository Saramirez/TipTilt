#include "../include/DisplayControl.hpp"

#include <iostream>


DisplayControl::DisplayControl(wxPanel * _camPanel_p,	wxPanel * _TTPositionPanel_p,
							 mutex * _mtxbmp, mutex * _mtxpos){
	
	camPanel_p = _camPanel_p;
	TTPositionPanel_p = _TTPositionPanel_p;
	TTPosX = 0;
	TTPosY = 0;
	mtxProtectingBmpAndCamPanel = _mtxbmp;
	mtxProtectingTTPositionsAndPanel = _mtxpos;
}

void DisplayControl::DisplayFrame(Mat frame) {
	img = wxImage(frame.cols,
		frame.rows,
		frame.data,
		TRUE);

	mtxProtectingBmpAndCamPanel->lock();
	bmp = wxBitmap(img);

	//panel_p->Refresh(FALSE);
	camPanel_p->Refresh();
	mtxProtectingBmpAndCamPanel->unlock();

	camPanel_p->Update();
	
}

void DisplayControl::UpdateTTPos(int _TTPosX, int _TTPosY) {
	mtxProtectingTTPositionsAndPanel->lock();
	TTPosX = _TTPosX;
	TTPosY = _TTPosY;
	TTPositionPanel_p->Refresh();
	mtxProtectingTTPositionsAndPanel->unlock();

	TTPositionPanel_p->Update();
}