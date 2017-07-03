#include "../include/main.hpp"
#include "../include/gui.hpp"
#include "../include/TipTilt.hpp"
#include "../include/CameraStreamHandling.hpp"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    GUI *gui = new GUI(wxT("TipTilt Control"));
    gui->Show(true);

    return true;
}

