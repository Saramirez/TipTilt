#ifndef TT_H
#define TT_H

#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <iostream>
#include <stdlib.h> 
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class TipTilt {
		int sSteps, eSteps, sError, eError;
		int fd;
		void configSerial();
		char * writeBuf;
		struct termios SerialConfig;
		double xPixToSteps = 0.42;
		double yPixToSteps = 0.41;		
		double cosCorrAngle = 1;
		double sinCorrAngle = 0.023;
	public:
		int openComm(const char*);
		void closeComm();
		int getSteps(int);
		void updatePosition();
		void setErrors(Point target, Point centroid);
		int goTo(char);
		void calibrate(VideoCapture&);
		TipTilt(); 	
};

#endif
