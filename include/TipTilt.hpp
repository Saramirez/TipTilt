#ifndef TT_H
#define TT_H

#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <iostream>
#include <stdlib.h> 

using namespace std;

class TipTilt {
		int sSteps, eSteps, sError, eError;
		int fd;
		void configSerial();
		char * writeBuf;
		struct termios SerialConfig;
	public:
		int openComm(const char*);
		void closeComm();
		int getSteps(int);
		void center();
		void updatePosition();
		void setErrors(int, int);
		TipTilt(); 	
};

#endif
