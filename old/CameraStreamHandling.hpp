#ifndef CIH_HH
#define CIH_HH

#include "opencv2/opencv.hpp"
#include <iostream>
#include "../include/TipTilt.hpp"
#include <math.h>

using namespace cv;
using namespace std;

int OpenCamera(VideoCapture&, const string);
void SetTarget(int, int);
int GetKeyFromKeyboard();
//void GetTargetFromMouse(int, int, int, int, void*);
Point GetCentroid(Mat&);
void CalculateErrors(Point, int&, int&);
int CaptureAndProcess(VideoCapture&, TipTilt&);
//int Calibrate(VideoCapture&, TipTilt&);

#endif