#include "../include/gui.hpp"
#include "../include/wxStreamPlayer.hpp"
#include "../include/wxStreamThread.hpp"

GUI::GUI(const wxString& title, SystemControl * _sControl_p)
    : wxFrame(NULL, wxID_ANY, title) {

    sControl_p = _sControl_p;


    wxStreamPlayer* player_p = new wxStreamPlayer(this, wxPoint(-1,-1), wxSize(640, 480),
												  sControl_p->GetWxBitmap(), sControl_p->GetWxMutexProtectingBitmap());
    player_p->Show(true);

	sControl_p->SetPlayer(player_p);
	sControl_p->Setup();
	sControl_p->Start();

    Centre();
}
