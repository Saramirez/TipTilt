#include "../include/gui.hpp"
#include "../include/wxStreamPlayer.hpp"

GUI::GUI(const wxString& title, SystemControl * _sControl_p)
    : player(this, wxPoint(-1,-1), wxSize(640, 480)),
      wxFrame(NULL, wxID_ANY, title) {

    sControl_p = _sControl_p;
    player.Show(true);
    
    Centre();

}
void GUI::Go(){
	sControl_p->SetPlayer(&player);
	sControl_p->Setup();
	sControl_p->Start();
}
