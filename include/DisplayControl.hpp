#ifndef DC_H
#define DC_H

#include "opencv2/opencv.hpp"
#include <mutex>

using namespace cv;
using namespace std;

class DisplayControl{
    private:
		const string pinholeWindow = "Pinhole Image";
		const string guidingWindow = "Full Mirror Image";
		const string calibrationWindow = "TipTilt Calibration";
		const string tiptiltPositionWindow = "TipTilt Position";
		const string plotWindow = "FWHM plot";
		const int oX = 400;
		const int oY = 50;
		const int windowSeparationSize = 400;
		const int TTWindowSize = 100;
		Mat ttpos;
		int frameRate;
		string stringFrameRate;
    public:
		DisplayControl();
		void CreateMainWindows();
		void CreateWindow(char);
		void DestroyWindow(char);
		void DisplayFrame(Mat&, char);
		void UpdateTTPos(int, int);
		void SetFrameRate(int);
		int TTPosX;
		int TTPosY;
};


#endif