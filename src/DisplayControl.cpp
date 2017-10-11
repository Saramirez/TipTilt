#include "../include/DisplayControl.hpp"

#include <iostream>


DisplayControl::DisplayControl(){
	TTPosX = 0;
	TTPosY = 0;
}

void DisplayControl::CreateMainWindows() {
	namedWindow(pinholeWindow, CV_WINDOW_AUTOSIZE);
	namedWindow(tiptiltPositionWindow, CV_WINDOW_AUTOSIZE);

	moveWindow(pinholeWindow, oX, oY);
	moveWindow(tiptiltPositionWindow, oX + windowSeparationSize, oY);
}
void DisplayControl::CreateCalibrationWindow() {
	namedWindow(calibrationWindow, CV_WINDOW_AUTOSIZE);
	moveWindow(calibrationWindow, oX, oY);
}
void DisplayControl::CreateGuidingWindow() {
	namedWindow(guidingWindow, CV_WINDOW_AUTOSIZE);
	moveWindow(guidingWindow, oX, oY);
}

void DisplayControl::DisplayFrame(Mat& frame, char type) {
	switch (type){
		case 'p':
			imshow(pinholeWindow, frame);
		break;
		case 'g'
			imshow(guidingWindow, frame);
		break;
		case 'c'
			imshow(calibrationWindow, frame);
		break;
		case 't'
			imshow(tiptiltPositionWindow, frame);
		break;
		case 'h'
			imshow(pinholeThreshedWindow, frame);
		break;
	}
}


void DisplayControl::UpdateTTPos(int _TTPosX, int _TTPosY) {
	TTPosX = _TTPosX;
	TTPosY = _TTPosY;
}