#include "../include/main.hpp"
#include "../include/gui.hpp"

IMPLEMENT_APP(TipTiltApp);

bool TipTiltApp::OnInit()
{
    GUI *gui = new GUI(wxT("TipTilt Control"));
    gui->Show(true);
    gui->createWxCSH();

    return true;
}

