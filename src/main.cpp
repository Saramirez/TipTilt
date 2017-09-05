#include "../include/main.hpp"
#include "../include/TTGui.hpp"
#include "../include/SystemControl.hpp"


IMPLEMENT_APP(TipTiltApp);

SystemControl sControl("/dev/ttyUSB0", "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

bool TipTiltApp::OnInit()
{
	TTGui * gui = new TTGui(NULL);

	sControl.player_p = gui->player;
	gui->sControl_p = &sControl;
    gui->Show(true);

	//sControl.StartCapture();

    return true;
}

