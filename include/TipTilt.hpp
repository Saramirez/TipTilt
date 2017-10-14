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
		void run();
	public:
		int sSteps, eSteps;
		bool isOpened();
		int openComm();
		void setDevice(const char *);
		void closeComm();
		void updatePosition();
		int goTo(char);
		void moveWithWASD();
		int start();
		int stop();
		void move(char);
		TipTilt(int *, int *, mutex *); 	
};

#endif
