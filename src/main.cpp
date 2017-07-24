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
int ex = 0;
int ey = 0;
mutex mtx;
TipTilt TT("/dev/ttyUSB0", &ex, &ey);

int main( int argc, char** argv )
{	
	OpenCamera(cam, "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

    //Calibrate(cam, TT);

    thread capture(CaptureAndProcess, ref(cam), &ex, &ey, &mtx); 

    TT.start();
    
    capture.join();

    TT.stop();

    TT.closeComm();

	return(0);
}
