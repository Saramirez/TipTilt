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

const int avgCount = 10;

class TipTilt {
	private:
		int sSteps, eSteps;
		int sLastSteps[avgCount];
		int eLastSteps[avgCount];
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
		void addStep(int);
		void run();
		void checkBumps(int&, int&);
	public:
		int getBump(int);
		bool isOpened();
		int openComm();
		void closeComm();
		void updatePosition();
		int goTo(char);
		void moveWithWASD();
		int start();
		int stop();
		void move(char);
		TipTilt(const char *, int *, int *, mutex *); 	
};

#endif
