#include <thread>
#include <mutex>
#include "../include/TipTilt.hpp"
#include "../include/CameraStreamHandling.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

using namespace cv;
using namespace std;

VideoCapture cam;
int eX = 0;
int eY = 0;
mutex mtx;
TipTilt TT("/dev/ttyUSB0", &eX, &eY, &mtx);

int main( int argc, char** argv )
{	
	OpenCamera(cam, "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

    //Calibrate(cam, TT);

    thread capture(CaptureAndProcess, ref(cam), &eX, &eY, &mtx, 50); 

    TT.start();
    
    capture.join();

    TT.stop();

    TT.closeComm();

	return(0);
}
