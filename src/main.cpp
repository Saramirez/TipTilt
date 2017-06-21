#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <thread>
#include <mutex>
#include <atomic>
#include "../include/TipTilt.hpp"
#include "../include/CameraAndImageHandling.hpp"

using namespace cv;
using namespace std;

VideoCapture cam;
TipTilt TT;

mutex TTm;

void UpdateTipTilt(atomic<bool>& running){
	int counter = 0;
    while(running){
    	//TTm.lock();
        TT.updatePosition();
        counter ++;
        //TTm.unlock();
    }
    cout << "UpdateTipTilt returned" << endl;
    cout << "Updated TipTilt " << counter << " times." << endl;
}

int main( int argc, char** argv )
{	
    TT.openComm("/dev/ttyUSB0"); 

	cam.open("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

	if (!cam.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

    Calibrate(cam, TT);

    //cout << "Is camera opened? " << cam.isOpened() << endl;
    thread capture(CaptureAndProcess, ref(cam), ref(TT)); 

	atomic<bool> running { true };
    thread utt(UpdateTipTilt, ref(running));

    capture.join();
    running = false;
    utt.join();
    TT.closeComm();
    cout << "Closed Comm" << endl;
	return(0);
}
