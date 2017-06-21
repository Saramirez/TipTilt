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
Point target(375,240);
/*int target.x = 375;
int target.y = 240;*/
bool targetSet = false;
/*double xPixToSteps = 0.42;
double yPixToSteps = 0.41;
double corrAngle = 0.023;
double cosCorrAngle = 1;
double sinCorrAngle = 0.023;*/
const string winName = "Star";

mutex TTm;

int GetKeyFromKeyboard(){
	int key = waitKey(50);
	//cout << "Key: " << key << endl;
	switch(key){
		case 255:
			return 0;
		case 27: // esc
			return -1;
		break;
		case 119: // w
			target.y-=5;
			if(target.y < 0)
				target.y = 0;
		break;
		case 115: // s
			target.y+=5;
			if(target.y > 480)
				target.y = 480;
		break;
		case 100: // d
			target.x+=5;
			if(target.x > 640)
				target.x = 640;
		break;
		case 97: // a
			target.x-=5;
			if(target.x < 0)
				target.x = 0;
		break;
		case 10: // Intro
			if(!targetSet){
				targetSet = true;
				cout << "Target set" << endl;
			}
		break;
	}
	//cout << "Target: " << target.x << "," << target.y << endl;
	return 0;
}

void GetTargetFromMouse(int event, int x, int y, int, void*){
	if (event != EVENT_LBUTTONDOWN)
		return;
	target.x = x;
	target.y = y;
	targetSet = true;
	cout << "Targets: " << target.x << "," << target.y << endl;

	setMouseCallback(winName, NULL, NULL);
}
/*
void CalculateErrors(Point centroid, int * xErr, int * yErr){
	int dx = xPixToSteps * (target.x - centroid.x);
    int dy = yPixToSteps * (target.y - centroid.y);
	
	//cout << "Errors: dx, dy = " << dx << "," << dy << endl;
	
    *xErr = dx * cosCorrAngle + dy * sinCorrAngle;
    *yErr = -dx * sinCorrAngle + dy * cosCorrAngle;

    //cout << "Errors: xErr, yErr = " << *xErr << "," << *yErr << endl;
}*/

int CaptureAndProcess(VideoCapture& cam){
	namedWindow(winName,CV_WINDOW_AUTOSIZE); 

	Mat frame;

	int counter = 0;

	int xErr = 0;
	int yErr = 0;

	//setMouseCallback(winName, GetTargetFromMouse, NULL);

    while (1){
		cam >> frame;
		if(targetSet){
			Point centroid = GetCentroid(frame);

	        //cout << "Centroid: " << centroid.x << "," << centroid.y << endl;	

	        //TTm.lock();
	        //CalculateErrors(centroid, &xErr, &yErr);
	        TT.setErrors(target, centroid);
	        //TTm.unlock();

			circle(frame, centroid, 5, Scalar(128,0,0));
		}

		cvtColor(frame, frame, CV_GRAY2BGR);
		circle(frame, Point(target.x,target.y), 3, Scalar(128,128,0));

		imshow(winName, frame);
		counter++;

		if (GetKeyFromKeyboard() == -1){ 
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}

	cout << "CaptureAndProcess returned" << endl;
    cout << "Updated Errors " << counter << " times." << endl;
    return 0;
}

/*
void Calibrate(){
	namedWindow("Calibration",CV_WINDOW_AUTOSIZE);

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
	
	imshow("Calibration", complete);

	waitKey(0);

	destroyWindow("Alignment");
}*/

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

	cam.open("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

	if (!cam.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

    //Calibrate();
    //cout << "Is camera opened? " << cam.isOpened() << endl;

	TT.calibrate(cam);

    thread capture(CaptureAndProcess, ref(cam)); 

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
