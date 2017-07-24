#ifndef CIH_HH
#define CIH_HH

#include "opencv2/opencv.hpp"
#include <iostream>
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
int CaptureAndProcess(VideoCapture&, int *, int *, mutex *);
int Calibrate(VideoCapture&, TipTilt&);

#endif