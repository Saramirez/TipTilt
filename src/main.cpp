#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <iostream>
#include "../include/TipTilt.hpp"
#include "../include/frameProcess.hpp"

using namespace cv;
using namespace std;

TipTilt TT;
int targetX = 320;
int targetY = 220;

int CaptureAndProcess(){
	Mat frame;

    VideoCapture cap("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

	if (!cap.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

    while (1){
		cap >> frame;
		Point centroid = GetCentroid(frame);
        cout.precision(10);

        //cout << "Centroid: " << fixed << centroid.x << "," << centroid.y << endl;	

        int dx = targetX - centroid.x;
        int dy = targetY - centroid.y;

        //cout << "Errors: " << fixed << dx << "," << dy << endl;
        
        TT.setErrors(dx, dy);

		circle(frame, centroid, 5, Scalar(128,0,0));
		circle(frame, Point(targetX,targetY), 3, Scalar(128,128,0));

		imshow("MyVideo", frame);
		if (waitKey(30) == 27){ 
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}

    return 0;
}

void UpdateTipTilt(){
    while(1){
        TT.updatePosition();
    }
}

int main( int argc, char** argv )
{	

	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); 
    thread capture(CaptureAndProcess);

    TT.openComm("/dev/ttyUSB0");   
    thread utt(UpdateTipTilt);
    
    capture.join();
    TT.closeComm();
	return(0);
}
