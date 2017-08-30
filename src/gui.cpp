#include "../include/gui.hpp"

GUI::GUI(const wxString& title)
		: player(this, wxPoint(-1, -1), wxSize(100, 100)),
		wxFrame(NULL, wxID_ANY, title) {
	
    player.Show(true);

    Centre();
}
