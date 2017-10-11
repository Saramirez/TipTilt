#ifndef CSH_H
#define CSH_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>
#include <mutex>

using namespace cv;
using namespace std;

class CameraStreamHandler{
    private:
        const char* device;
        int * eX;
        int * eY;
        int xErr = 0;
        int yErr = 0;

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
        double xPixToSteps = 2.4;
        double yPixToSteps = 2.33;
        const double pinholeRadius = 8.0;
        const double w = 2 * M_PI * 0.05;
	    const double R = 3;

        void GetShapeInfo(Point&, double&, double*, double&);
        void GetSimpleShapeInfo(Point&, double&);
        void CalculateErrors(int&, int&, double&, double*, double&);

    public:
        CameraStreamHandler(int *, int *, mutex * );

		int thresh = 150;
		double starRadius = 10.3;
		
		void SetPixToStepsFactors(double, double);
		void SetRoi(Rect);
		void SetDevice(const char *);
		Point GetTarget();
		int OpenCamera();
		int CloseCamera();
		bool IsCameraOpen();
		Point GetCentroid(Mat&);
        Mat GetStarParams();
        Mat GrabOneFrame(bool full = false, bool pinholePos = false);
        Mat CaptureAndProcess(bool showThresh = false, bool simulate = false);
};

#endif