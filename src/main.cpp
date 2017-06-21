#include <thread>
#include <mutex>
#include "../include/TipTilt.hpp"
#include "../include/CameraStreamHandling.hpp"

using namespace cv;
using namespace std;

VideoCapture cam;
TipTilt TT("/dev/ttyUSB0");

int main( int argc, char** argv )
{	
	OpenCamera(cam, "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

    //Calibrate(cam, TT);

    //Cuando CaptureAndProcess termina, llama a TT.stop()
    thread capture(CaptureAndProcess, ref(cam), ref(TT)); 

    TT.start();
    
    capture.join();

    TT.closeComm();

	return(0);
}
