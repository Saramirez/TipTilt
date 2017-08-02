#ifndef CIH_HH
#define CIH_HH

#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include "../include/TipTilt.hpp"
#include <math.h>
#include <mutex>

using namespace cv;
using namespace std;

int OpenCamera(VideoCapture&, const string);
void SetTarget(int, int);
int GetKeyFromKeyboard();
void GetTargetFromMouse(int, int, int, int, void*);
Point GetCentroid(Mat&);
void CalculateErrors(Point, int&, int&);
int CaptureAndProcess(VideoCapture&, int *, int *, mutex *, const int);
int Calibrate(VideoCapture&, TipTilt&);
int CalibrateErrorCalculation(VideoCapture&, TipTilt&);
void GetStarParams(VideoCapture&);
void GetShapeInfo(Mat&, Point&, double&, int&, double&);

#endif