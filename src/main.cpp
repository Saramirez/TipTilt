#include "../include/main.hpp"
#include "../include/gui.hpp"
#include "../include/SystemControl.hpp"


IMPLEMENT_APP(TipTiltApp);

bool TipTiltApp::OnInit()
{
	SystemControl sControl("/dev/ttyUSB0", "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

    GUI *gui = new GUI(wxT("TipTilt Control"), &sControl);
    gui->Show(true);

    return true;
}

