#ifndef CSH_H
#define CSH_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>
#include <mutex>

using namespace cv;
using namespace std;

const int FWHMCountsToAvg  = 100;
const int roiSize = 50;
const int guideRoiSize = 500;
const int TTzoom = 8;
class CameraStreamHandler{
    private:
        const char* device;
        int * eX_p;
        int * eY_p;
        double xErr = 0.0;
		double yErr = 0.0;
		vector<int>FWHMs;
		vector<int>HMs;
		int iXErr = 0;
		int iYErr = 0;
        Point centroid;
        double dist;
        double dir[2];
        double width;
        mutex * mtx;
        VideoCapture cam;
        Mat frame;
		Point target;
		Point fullFramePinholePosition;
        Rect roi;
        Rect oRoi;

		double cosCorrAngle = 1;
		double sinCorrAngle = 0;

        const double pinholeRadius = 4.76;//4.76;

        const double w = 2 * M_PI * 1.2;
	    const double R = 2;

        void GetShapeInfo(Point&, double&, double*, double&);
        void GetSimpleShapeInfo(Point&, double&);
        void CalculateErrors(double&, double&, double&, double*, double&);

    public:
        CameraStreamHandler(int *, int *, mutex * );

		int thresh = 30; 
		double starRadius = 5;
		double xPixToSteps = 7.7; //2.4 * 2.735 (factor en laboratorio * magnificacion de camara) - valor medido en telescopio con calibracion
		double yPixToSteps = 8.5; //2.33 * 2.735;

		void SetPixToStepsFactors(double, double);
		void SetAngles(double, double);
		void SetRoi(Rect);
		void SetDevice(const char *);
		void SetPinholePosition(Point);
		int OpenCamera();
		int CloseCamera();
		bool IsCameraOpen();
		Point GetCentroid(Mat&);
		Mat GrabOneFrame(bool full = false);
		Mat GrabGuideFrame(int, bool);
        Mat GrabGuideFrame(int, bool, Mat&);
        Mat CaptureAndProcess(bool showThresh = false, bool simulate = false, int filterErrors = 0, bool updateErrors = true, int timeBetweenUpdates = -1);
		void MeasureFWMH(Mat&, Mat&);

};

#endif
