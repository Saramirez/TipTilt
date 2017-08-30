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
        Rect roi;
        double xPixToSteps = 2.4;
        double yPixToSteps = 2.33;
        const double pinholeRadius = 13;
        double starRadius = 13.5;

        const int thresh = 100;
        bool targetSet;

        void GetShapeInfo(Point&, double&, double*, double&);
        void GetShapeInfo(Point&, double&);
        void CalculateErrors(int&, int&, double&, double*, double&);

    public:
        CameraStreamHandler(const char *, int *, int *, mutex * );
        int OpenCamera();
		bool IsCameraOpen();
        int GetStarParams();
        Mat GrabOneFrame();
        Mat CaptureAndProcess();
};

#endif