#ifndef TT_H
#define TT_H

#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class TipTilt {
	private:
		int * eY;
		int * eX;
		int eXX, eYY;
		mutex * mtx;
		mutex internalMtx;
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
		int sSteps, eSteps;
		bool isOpened();
		int openComm();
		void setDevice(const char *);
		void closeComm();
		void updatePosition();
		void updatePositionV2();
		int goTo(char);
		void moveWithWASD();
		void move(char);
		void setErrors(int, int);
		TipTilt(int *, int *, mutex *); 	
};

#endif
