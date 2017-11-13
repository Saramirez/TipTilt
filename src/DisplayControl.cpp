#include "../include/DisplayControl.hpp"
#include <iostream>

DisplayControl::DisplayControl() :
	ttpos(TTWindowSize, TTWindowSize, CV_8UC3, Scalar(240, 240, 240)) {
	TTPosX = 0;
	TTPosY = 0;

	rectangle(ttpos, Point(TTWindowSize / 2 - 35, TTWindowSize / 2 - 35),
		Point(TTWindowSize / 2 + 35, TTWindowSize / 2 + 35),
		Scalar(0, 0, 255));
	line(ttpos, Point(TTWindowSize / 2, 0), Point(TTWindowSize / 2, TTWindowSize), Scalar(0, 0, 0));
	line(ttpos, Point(0, TTWindowSize / 2), Point(TTWindowSize, TTWindowSize / 2), Scalar(0, 0, 0));
}

void DisplayControl::CreateMainWindows() {
	cout << "Creating windows" << endl;
	namedWindow(pinholeWindow, CV_WINDOW_AUTOSIZE);
	namedWindow(tiptiltPositionWindow, CV_WINDOW_AUTOSIZE);

	moveWindow(pinholeWindow, oX, oY);
	moveWindow(tiptiltPositionWindow, oX + windowSeparationSize, oY);
}

void DisplayControl::CreateWindow(char type) {
	switch (type) {
	case 'g':
		namedWindow(guidingWindow, CV_WINDOW_AUTOSIZE);
		moveWindow(guidingWindow, oX, oY);
		break;
	case 'c':
		namedWindow(calibrationWindow, CV_WINDOW_AUTOSIZE);
		moveWindow(calibrationWindow, oX, oY);
		break;
	case 'f':
		namedWindow(plotWindow, CV_WINDOW_AUTOSIZE);
		moveWindow(plotWindow, oX, oY);
		break;
	}
}

void DisplayControl::DestroyWindow(char type) {
	switch (type) {
	case 'g':
		destroyWindow(guidingWindow);
		break;
	case 'c':
		destroyWindow(calibrationWindow);
		break;
	case 'f':
		destroyWindow(plotWindow);
		break;
	}
}

void DisplayControl::DisplayFrame(Mat& frame, char type) {
	if (frame.empty())
		return;
	switch (type) {
	case 'p':
		/*stringFrameRate = to_string(frameRate);
		putText(frame, stringFrameRate, Point(10, frame.rows - 10), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(128, 128, 0));*/
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
	case 'f':
		imshow(plotWindow, frame);
		break;
	}
}

void DisplayControl::UpdateTTPos(int TTPosX, int TTPosY) {
	Mat _ttpos = ttpos.clone();

	//double x = TTPosX * cosCorrAngle - TTPosY * sinCorrAngle;
	//double y = -1 * TTPosX * sinCorrAngle + TTPosY * cosCorrAngle;

	circle(_ttpos, Point(TTWindowSize / 2 - TTPosY, TTWindowSize / 2 + TTPosX), 5, Scalar(0, 128, 0), -1, CV_AA); // orientación x-y invertida para que coincida con los controles del mount control

	resize(_ttpos, _ttpos, Size(), 3, 3);
	imshow(tiptiltPositionWindow, _ttpos);
}

void DisplayControl::SetFrameRate(int f) {
	frameRate = f;
}