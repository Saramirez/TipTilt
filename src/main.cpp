#include "../include/main.hpp"
#include "../include/gui.hpp"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    GUI *gui = new GUI(wxT("TipTilt Control"));
    gui->Show(true);

    return true;
}

