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
		const int avgCount = 10;
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
		int getAvgStep(int);
		void run();
		// To tell the user it needs to move the telescope mount
		int NSCenter;
		int WECenter;
	public:
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
