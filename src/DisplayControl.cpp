#include "../include/DisplayControl.hpp"
#include <iostream>

DisplayControl::DisplayControl(){
	TTPosX = 0;
	TTPosY = 0;
}

void DisplayControl::CreateMainWindows() {
	cout << "Creating windows" << endl;
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
		case 'g':
			imshow(guidingWindow, frame);
		break;
		case 'c':
			imshow(calibrationWindow, frame);
		break;
		case 't':
			imshow(tiptiltPositionWindow, frame);
		break;
	}
}

void DisplayControl::SetCorrAngles(double cos, double sin) {
	cosCorrAngle = cos;
	sinCorrAngle = sin;
}


void DisplayControl::UpdateTTPos(int TTPosX, int TTPosY) {
	Mat ttpos(TTWindowSize, TTWindowSize, CV_8UC3, Scalar(240, 240, 240));

	double x = TTPosX * cosCorrAngle - TTPosY * sinCorrAngle;
	double y = -1 * TTPosX * sinCorrAngle + TTPosY * cosCorrAngle;

	circle(ttpos, Point(TTWindowSize / 2 + x, TTWindowSize / 2 + y), 5, Scalar(0, 128, 0), -1);
	rectangle(ttpos, Point(TTWindowSize / 2 - 35, TTWindowSize / 2 - 35),
		Point(TTWindowSize / 2 + 35, TTWindowSize / 2 + 35),
		Scalar(0, 0, 255));
	line(ttpos, Point(TTWindowSize / 2, 0), Point(TTWindowSize / 2, TTWindowSize), Scalar(0, 0, 0));
	line(ttpos, Point(0, TTWindowSize / 2), Point(TTWindowSize, TTWindowSize / 2), Scalar(0, 0, 0));
	imshow(tiptiltPositionWindow, ttpos);
}

void DisplayControl::DestroyGuidingWindow() {
	destroyWindow(guidingWindow);
}

void DisplayControl::DestroyCalibrationWindow() {
	destroyWindow(calibrationWindow);
}