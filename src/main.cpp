#include "../include/main.hpp"
#include "../include/gui.hpp"
#include "../include/CameraStreamHandler.hpp"
#include "../include/TipTilt.hpp"

IMPLEMENT_APP(TipTiltApp);

int eX = 0;
int eY = 0;
mutex mtx;
TipTilt TT("/dev/ttyUSB0", &eX, &eY, &mtx);
CameraStreamHandler CSH("v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink",
                        &eX, &eY, &mtx);

bool TipTiltApp::OnInit()
{
    GUI *gui = new GUI(wxT("TipTilt Control"), &CSH, &TT);
    gui->Show(true);

    return true;
}

