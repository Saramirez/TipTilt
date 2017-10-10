#include "../include/DisplayControl.hpp"

#include <iostream>


DisplayControl::DisplayControl(){
	TTPosX = 0;
	TTPosY = 0;
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