#include "../include/main.hpp"
#include "../include/gui.hpp"
#include "../include/TipTiltControl.hpp"


IMPLEMENT_APP(TipTiltApp);

bool TipTiltApp::OnInit()
{
	TipTiltControl TTC("/dev/ttyUSB0", "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");

    GUI *gui = new GUI(wxT("TipTilt Control"), &TTC);
    gui->Show(true);

    return true;
}

