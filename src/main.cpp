#include "../include/main.hpp"
#include "../include/TTGui.hpp"
#include "../include/SystemControl.hpp"


IMPLEMENT_APP(TipTiltApp);

SystemControl sControl;
//"/dev/ttyUSB0", "v4l2src device=/dev/video0 ! video/x-raw,format=GRAY8 ! appsink");
//"/dev/ttyUSB0", "v4l2src device=/dev/video0 ! video/x-raw,format=GRAY8 ! appsink"

bool TipTiltApp::OnInit()
{
	TTGui * gui = new TTGui(NULL);

	sControl.dControl_p = gui->dControl_p;
	sControl.SetCamDevice(0);
	sControl.SetTTDevice(0);
	gui->sControl_p = &sControl;
    gui->Show(true);

	//sControl.StartCapture();

    return true;
}

