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
		const string guidingWindow = "Full Mirror Image";
		const int oX = 400;
		const int oY = 50;
		const int windowSeparationSize = 100;
		const int TTWindowSize = 100;
		double cosCorrAngle = 1;
		double sinCorrAngle = 0;
    public:
		DisplayControl();
		void CreateMainWindows();
		void CreateCalibrationWindow();
		void DestroyCalibrationWindow();
		void CreateGuidingWindow();
		void DestroyGuidingWindow();
		void DisplayFrame(Mat&, char);
		void UpdateTTPos(int, int);
		void SetCorrAngles(double, double);
		int TTPosX;
		int TTPosY;
};


#endif