#include "../include/gui.hpp"
#include "../include/wxStreamPlayer.hpp"
#include "../include/wxStreamThread.hpp"

GUI::GUI(const wxString& title, CameraStreamHandler * _CSH, TipTilt * _TT)
    : wxFrame(NULL, wxID_ANY, title) {

    CSH = _CSH;
    TT = _TT;


    wxStreamPlayer* player = new wxStreamPlayer(
        this, 
        wxPoint(-1,-1),
        wxSize(640, 480));
    player->Show(true);

    wxStreamThread * sThread = new wxStreamThread(player, CSH);

    sThread -> Open();
    sThread -> Create();
    sThread -> Run();

    Centre();
}
