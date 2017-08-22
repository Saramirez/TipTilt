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
		int sSteps, eSteps;
		int * eY;
		int * eX;
		mutex * mtx;
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
		void moveWithWASD();
		void start();
		void stop();
		void run();
		void move(char);
		TipTilt(const char *, int *, int *, mutex *); 	
};

#endif
