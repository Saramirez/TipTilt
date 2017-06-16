#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include "../include/TipTilt.hpp"
#include "../include/frameProcess.hpp"
#include <math.h>

using namespace cv;
using namespace std;

VideoCapture cam;
TipTilt TT;
double corrAngle = 0.023;
double cosCorrAngle = 1;
double sinCorrAngle = 0.023;
int targetX = 320;
int targetY = 220;
bool targetSet = false;
double xPixToSteps = 0.42;
double yPixToSteps = 0.41;
const string winName = "Star";

mutex TTm;

void GetTargetFromMouse(int event, int x, int y, int, void*){
	if (event != EVENT_LBUTTONDOWN)
		return;
	targetX = x;
	targetY = y;
	targetSet = true;
	cout << "Targets: " << targetX << "," << targetY << endl;

	setMouseCallback(winName, NULL, NULL);
}

void CalculateErrors(Point centroid, int * xErr, int * yErr){
	int dx = xPixToSteps * (targetX - centroid.x);
    int dy = yPixToSteps * (targetY - centroid.y);

    *xErr = dx * cosCorrAngle + dy * sinCorrAngle;
    *yErr = -dx * sinCorrAngle + dy * cosCorrAngle;

    //cout << "Errors: dx, dy = " << dx << "," << dy << endl;
    //cout << "Errors: dx', dy' = " << _dx << "," << _dy << endl;
}

int CaptureAndProcess(){
	namedWindow(winName,CV_WINDOW_AUTOSIZE); 

	Mat frame;

    cam.open("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

	if (!cam.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}
	int counter = 0;

	int xErr = 0;
	int yErr = 0;

	setMouseCallback(winName, GetTargetFromMouse, NULL);
    while (1){
		cam >> frame;
		if(targetSet){
			Point centroid = GetCentroid(frame);

	        //cout << "Centroid: " << centroid.x << "," << centroid.y << endl;	

	        //TTm.lock();
	        CalculateErrors(centroid, &xErr, &xErr);
	        TT.setErrors(&xErr, &xErr);
	        //TTm.unlock();

			circle(frame, centroid, 5, Scalar(128,0,0));
			circle(frame, Point(targetX,targetY), 3, Scalar(128,128,0));
		}

		imshow(winName, frame);
		counter++;
		if (waitKey(30) == 27){ 
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}
	cout << "CaptureAndProcess returned" << endl;
    cout << "Updated Errors " << counter << " times." << endl;
    return 0;
}

void Calibrate(){
	namedWindow("Alignment",CV_WINDOW_AUTOSIZE);

	Mat K,N,S,E,W;
	Point cK, cN, cS, cE, cW;

    cam.open("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");
	
	TT.goTo('K');
	cam >> K;

	TT.goTo('N');
	cam >> N;
	int NSSteps = TT.goTo('S');
	cam >> S;

    TT.goTo('K');

    TT.goTo('E');
	cam >> E;
    int EWSteps = TT.goTo('W');
	cam >> W;

	cam.release();

	cK = GetCentroid(K);
	cN = GetCentroid(N);
	cS = GetCentroid(S);
	cE = GetCentroid(E);
	cW = GetCentroid(W);

	cout << "Centroids: " << cK.x << "," << cK.y << ";" << cN.x << "," << cN.y << ";" 
							<< cS.x << "," << cS.y << ";" << cE.x << "," << cE.y << ";" 
							<< cW.x << "," << cW.y << endl;

	cout << "Steps: " << NSSteps << "," << EWSteps << endl;

	double NSDist = sqrt(pow(cN.x - cS.x, 2) + pow(cN.y - cS.y, 2));
	double EWDist = sqrt(pow(cE.x - cW.x, 2) + pow(cE.y - cW.y, 2));

	cout << "Dists: " << NSDist << "," << EWDist << endl;

	xPixToSteps = NSDist / ((double)NSSteps);
	yPixToSteps = EWDist / ((double)EWSteps);

	cout << "Factors: " << xPixToSteps << "," << yPixToSteps << endl;

	double tan1 = ((double)(cW.y - cE.y))/((double)(cE.x - cW.x));
	double tan2 = ((double)(cN.x - cS.x))/((double)(cN.y - cS.y));

	cout << "Tans: " << tan1 << "," << tan2 << endl;

	double alpha = atan(tan1);
	double beta = atan(tan2);

	corrAngle = (alpha + beta) / 2.0;
	cosCorrAngle = cos(corrAngle);
	sinCorrAngle = sin(corrAngle);

	cout << "Angles: " << alpha << "," << beta << ";" << corrAngle << endl;

	Mat complete = (K > 150) + (N > 150) + (S > 150) + (E > 150) + (W > 150);
	cvtColor(complete, complete, CV_GRAY2BGR);

	circle(complete, cK, 5, Scalar(0,0,0));
	circle(complete, cN, 5, Scalar(0,128,0));
	circle(complete, cS, 5, Scalar(0,0,128));
	circle(complete, cE, 5, Scalar(128,0,0));
	circle(complete, cW, 5, Scalar(128,128,128));
	imshow("Alignment", complete);


	waitKey(0);

	destroyWindow("Alignment");
}

void UpdateTipTilt(atomic<bool>& running){
	int counter = 0;
    while(running){
    	//TTm.lock();
        TT.updatePosition();
        counter ++;
        //TTm.unlock();
    }
    cout << "Updated TipTilt " << counter << " times." << endl;
}

int main( int argc, char** argv )
{	
    TT.openComm("/dev/ttyUSB0"); 

    //Calibrate();
    //cout << "Is camera opened? " << cam.isOpened() << endl;
    thread capture(CaptureAndProcess); 

	atomic<bool> running { true };
    thread utt(UpdateTipTilt, ref(running));

    capture.join();
    running = false;
    utt.join();
    cout << "UpdateTipTilt returned" << endl;
    TT.closeComm();
    cout << "Closed Comm" << endl;
	return(0);
}
