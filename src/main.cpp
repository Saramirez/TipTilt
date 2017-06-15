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
int targetX = 320;
int targetY = 220;


int CaptureAndProcess(){
	namedWindow("Star",CV_WINDOW_AUTOSIZE); 

	Mat frame;

    cam.open("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

	if (!cam.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

    while (1){
		cam >> frame;
		Point centroid = GetCentroid(frame);

        //cout << "Centroid: " << centroid.x << "," << centroid.y << endl;	

        int dx = targetX - centroid.x;
        int dy = targetY - centroid.y;

        //cout << "Errors: " << dx << "," << dy << endl;
        
        TT.setErrors(dx, dy);

		circle(frame, centroid, 5, Scalar(128,0,0));
		circle(frame, Point(targetX,targetY), 3, Scalar(128,128,0));

		imshow("Star", frame);
		if (waitKey(30) == 27){ 
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}

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

	cout << "Angles: " << alpha << "," << beta << endl;

	double xAlFactor = 1.0/cos(alpha);
	double yAlFactor = 1.0/cos(beta);

	cout << "Factors: " << xAlFactor << "," << yAlFactor << endl;

	TT.setAlignmentFactors(xAlFactor, yAlFactor);

	Mat complete = (K > 150) + (N > 150) + (S > 150) + (E > 150) + (W > 150);
	circle(complete, cK, 5, Scalar(128,0,0));
	circle(complete, cN, 5, Scalar(128,0,0));
	circle(complete, cS, 5, Scalar(128,0,0));
	circle(complete, cE, 5, Scalar(128,0,0));
	circle(complete, cW, 5, Scalar(128,0,0));
	imshow("Alignment", complete);

	cam.release();

	waitKey(0);
}

void UpdateTipTilt(atomic<bool>& running){
    while(running){
        TT.updatePosition();
    }
}

int main( int argc, char** argv )
{	
    TT.openComm("/dev/ttyUSB0"); 

    //Align();

    thread capture(CaptureAndProcess); 

	atomic<bool> running { true };
    thread utt(UpdateTipTilt, ref(running));

    capture.join();
    running = false;
    utt.join();
    TT.closeComm();
	return(0);
}
