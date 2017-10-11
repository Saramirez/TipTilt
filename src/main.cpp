#include "../include/SystemControl.hpp"
#include "../include/DisplayControl.hpp"


SystemControl sControl;
//"/dev/ttyUSB0", "v4l2src device=/dev/video0 ! video/x-raw,format=GRAY8 ! appsink");
//"/dev/ttyUSB0", "v4l2src device=/dev/video0 ! video/x-raw,format=GRAY8 ! appsink"

int main(int argc, char** argv)
{
	sControl.SetCamDevice(0);
	sControl.SetTTDevice(0);

	sControl.StartCapture();

	while (sControl.GetKeyFromKeyboard() != -1) {
	}

	sControl.StopCapture();
	return(0);
}
