#include "../include/gui.hpp"

GUI::GUI(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title) {
	
    player = new wxStreamPlayer(this, wxPoint(-1, -1), wxSize(100, 100));
    player->Show(true);

    Centre();
}
