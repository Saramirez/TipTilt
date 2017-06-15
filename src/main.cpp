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
double corrAngle = -0.225404;
double cosCorrAngle = 0.9747;
double sinCorrAngle = -0.2235;
int targetX = 320;
int targetY = 220;

mutex TTm;


int CaptureAndProcess(){
	namedWindow("Star",CV_WINDOW_AUTOSIZE); 

	Mat frame;

    cam.open("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

	if (!cam.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}
	int counter = 0;

    while (1){
		cam >> frame;
		Point centroid = GetCentroid(frame);

        //cout << "Centroid: " << centroid.x << "," << centroid.y << endl;	

        int dx = targetX - centroid.x;
        int dy = targetY - centroid.y;

        int _dx = dx * cosCorrAngle + dy * sinCorrAngle;
        int _dy = -dx * sinCorrAngle + dy * cosCorrAngle;

        cout << "Errors: dx, dy = " << dx << "," << dy << endl;
        cout << "Errors: dx', dy' = " << _dx << "," << _dy << endl;

        //TTm.lock();
        //TT.setErrors(_dx, _dy);
        TT.setErrors(dx, dy);
        //TTm.unlock();

		circle(frame, centroid, 5, Scalar(128,0,0));
		circle(frame, Point(targetX,targetY), 3, Scalar(128,128,0));

		imshow("Star", frame);
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

void Align(){
	namedWindow("Alignment",CV_WINDOW_AUTOSIZE);

	Mat K,N,S,E,W;
	Point cK, cN, cS, cE, cW;

    cam.open("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");
	
	TT.goTo('K');
	cam >> K;

	TT.goTo('N');
	cam >> N;
    TT.goTo('S');
	cam >> S;

    TT.goTo('K');

    TT.goTo('E');
	cam >> E;
    TT.goTo('W');
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

    //Align();
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
