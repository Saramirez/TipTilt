#ifndef CSH_H
#define CSH_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>
#include <mutex>

using namespace cv;
using namespace std;

const Point fullFramePinholePosition(657,565);
const int errorCountsToAvg = 5;
const int FWHMCountsToAvg  = 20;
const int roiSize = 80;
const int guideRoiSize = 500;
const int TTzoom = 4;
class CameraStreamHandler{
    private:
        const char* device;
        int * eX;
        int * eY;
        int xErr = 0;
        int yErr = 0;
		int _xErr;
		int _yErr;
		vector<int>xErrors;
		vector<int>yErrors;
		vector<int>FWHMs;
		vector<int>HMs;
		int iXErr, iYErr;
        Point centroid;
        double dist;
        double dir[2];
        double width;
        mutex * mtx;
        VideoCapture cam;
        Mat frame;
		Point target;
        Rect roi;
        Rect oRoi;

		double cosCorrAngle = 1;
		double sinCorrAngle = 0;

        const double pinholeRadius = 4.76;

        const double w = 2 * M_PI * 0.05;
	    const double R = 3;

        void GetShapeInfo(Point&, double&, double*, double&, int mode);
        void GetSimpleShapeInfo(Point&, double&);
        void CalculateErrors(int&, int&, double&, double*, double&, int mode);

    public:
        CameraStreamHandler(int *, int *, mutex * );

		int thresh = 100; //Should be FWHM
		double starRadius = 5;
		double xPixToSteps = 0.877; //2.4 / 2.735 (factor en laboratorio / magnificacion de camara);
		double yPixToSteps = 0.852; //2.33 / 2.735;
		
		void SetPixToStepsFactors(double, double);
		void SetAngles(double, double);
		void SetRoi(Rect);
		void SetDevice(const char *);
		Point GetTarget();
		int OpenCamera();
		int CloseCamera();
		bool IsCameraOpen();
		Point GetCentroid(Mat&);
        Mat GetStarParams();
		Mat GrabOneFrame(bool full = false);
		Mat GrabGuideFrame(int, bool);
        Mat GrabGuideFrame(int, bool, Mat&);
        Mat CaptureAndProcess(bool showThresh = false, bool simulate = false, int filterErrors = 0, int errorMode = 1);
		Mat CaptureAndProcess(int&, int&, mutex&, bool showThresh = false, bool simulate = false, int filterErrors = 0, int errorMode = 1);
		void MeasureFWMH(Mat&, Mat&);

};

#endif