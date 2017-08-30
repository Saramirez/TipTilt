#include "../include/main.hpp"
#include "../include/gui.hpp"
#include "../include/SystemControl.hpp"


IMPLEMENT_APP(TipTiltApp);

SystemControl sControl("/dev/ttyUSB0", "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");
GUI gui(wxT("TipTilt Control"), &sControl);

bool TipTiltApp::OnInit()
{
	sControl.player_p = &(gui.player);
	gui.sControl_p = &sControl;
    gui.Show(true);

	sControl.Start();
	/*
	SystemControl * sControl = new SystemControl("/dev/ttyUSB0", "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");
	GUI * gui = new GUI(wxT("TipTilt Control"), sControl);
	*/

    return true;
}

