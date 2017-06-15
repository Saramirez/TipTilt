#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../include/frameProcess.hpp"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
//	VideoCapture cap(0);
	VideoCapture cap("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

	if (!cap.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); 
	
	Mat frame;

	while (1){
		cap >> frame;

		/*bool bSuccess = cap.read(frame); 

		if (!bSuccess){ 
			 cout << "Cannot read a frame from video stream" << endl;
			 break;
		}*/
	
		
		Point centroid = GetCentroid(frame);	
	
		circle(frame, centroid, 5, Scalar(128,0,0));

		imshow("MyVideo", frame);
		if (waitKey(10) == 27){ 
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}
	return(0);
}
