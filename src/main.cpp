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
	
		circle(frame, centroid, 5, Scalar(128,0,0));
		circle(frame, Point(320,220), 3, Scalar(128,128,0));

		imshow("MyVideo", frame);
		if (waitKey(30) == 27){ 
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}

    return 0;
}

int main( int argc, char** argv )
{
    TT.openComm("/dev/ttyUSB0");    
	

	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); 

    thread capture(CaptureAndProcess);

    capture.join();
	
    TT.closeComm();
	return(0);
}
