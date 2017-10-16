#ifndef DC_H
#define DC_H

#include "opencv2/opencv.hpp"
#include <mutex>

using namespace cv;
using namespace std;

class DisplayControl{
    private:
		const string pinholeWindow = "Pinhole Image";
		const string calibrationWindow = "TipTilt Calibration";
		const string tiptiltPositionWindow = "TipTilt Position";
		const string plotWindow = "FWHM plot";
		const int oX = 400;
		const int oY = 50;
		const int windowSeparationSize = 400;
		const int TTWindowSize = 100;
		double cosCorrAngle = 1;
		double sinCorrAngle = 0;
		Mat ttpos;
		int frameRate;
		string stringFrameRate;
    public:
		DisplayControl();
		const string guidingWindow = "Full Mirror Image";
		void CreateMainWindows();
		void CreateWindow(char);
		void DestroyWindow(char);
		void DisplayFrame(Mat&, char);
		void DisplayFWHMPlot(Mat&, Point);
		void UpdateTTPos(int, int);
		void SetCorrAngles(double, double);
		void SetFrameRate(int);
		int TTPosX;
		int TTPosY;
};


#endif