#include "../include/TTGui.hpp"

TTGui::TTGui( wxWindow* parent )
:
MainFrame( parent )
{
	player = new wxStreamPlayer(this, wxPoint(-1, -1), wxSize(100, 100));
	player->Show(true);
}

void TTGui::OnClickStart( wxCommandEvent& event )
{
	sControl_p->StartCorrection();
	sControl_p->StartCapture();
// TODO: Implement OnClickStart
}

void TTGui::OnClickExit( wxCommandEvent& event )
{
	Close(true);
// TODO: Implement OnClickExit
}
