#ifndef TT_H
#define TT_H

//#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <iostream>
//#include <stdlib.h> 
#include <atomic>

using namespace std;

class TipTilt {
		int sSteps, eSteps, sError, eError;
		char out;
		atomic<bool> running;
		int fd;
		void configSerial();
		char * writeBuf;
		const char* device;
		struct termios SerialConfig;
	public:
		int openComm();
		void closeComm();
		int getSteps(int);
		void updatePosition();
		void setErrors(int, int);
		int goTo(char);
		void start();
		void stop();
		TipTilt(const char *); 	
};

#endif
