#ifndef TT_H
#define TT_H

#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <iostream>
#include <atomic>
#include <thread>

using namespace std;

class TipTilt {
		int sSteps, eSteps, sError, eError;
		char out;
		atomic<bool> running;
		int fd;
		bool opened = false;
		void configSerial();
		char * writeBuf;
		const char* device;
		struct termios SerialConfig;
		thread runningThread;
	public:
		bool isOpened();
		int openComm();
		void closeComm();
		int getSteps(int);
		void updatePosition();
		void setErrors(int, int);
		int goTo(char);
		void start();
		void stop();
		void run();
		TipTilt(const char *); 	
};

#endif
