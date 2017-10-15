#include "../include/DisplayControl.hpp"
#include <iostream>

DisplayControl::DisplayControl():
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
	Mat _ttpos = ttpos.clone();

	double x = TTPosX * cosCorrAngle - TTPosY * sinCorrAngle;
	double y = -1 * TTPosX * sinCorrAngle + TTPosY * cosCorrAngle;

	circle(_ttpos, Point(TTWindowSize / 2 + x, TTWindowSize / 2 + y), 5, Scalar(0, 128, 0), -1);

	imshow(tiptiltPositionWindow, _ttpos);
}

void DisplayControl::DisplayFWHMPlot(Mat& frame, Point FWHMcenter) {
	Mat plot(300, 100, CV_8UC3, Scalar(0, 0, 0));
	vector<Point> curvePoints;
	int maxIntensity = 0;
	for (int i = 0; i < 100; i++) {
		Point pixel((FWHMcenter.x - plot.cols / 2 + i), FWHMcenter.y);
		Scalar intensity = frame.at<uchar>(pixel);
		if (intensity.val[0] > maxIntensity)
			maxIntensity = intensity.val[0];
		Point curvePoint(i, plot.rows - intensity.val[0]);
		curvePoints.push_back(curvePoint);
	}
	for (int i = 0; i < curvePoints.size() - 1; i++) {
		line(plot, curvePoints[i], curvePoints[i + 1], Scalar(0, 128, 0), 1, CV_AA);
	}
	int HM = maxIntensity / 2;

	Mat bw = plot.clone();
	cvtColor(bw, bw, CV_BGR2GRAY);

	line(plot, Point(0, plot.rows - HM), Point(plot.cols - 1, plot.rows - HM), Scalar(255, 255, 255));
		
	int FWHM = 0;
	while (1){
		FWHM += 1;
		Point pixel(plot.cols/2 + FWHM, plot.rows - HM);
		Scalar intensity = bw.at<uchar>(pixel);
		if (intensity.val[0] != 0)
			break;
	}
	FWHM += 1;
	FWHM *= 2;
	cout << "FWHM = " << FWHM << endl;

	imshow(plotWindow, plot);
}