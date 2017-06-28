#include "../include/gui.hpp"

GUI::GUI(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))
{
    SetIcon(wxIcon(wxT("web.xpm")));

    menubar = new wxMenuBar;
    file = new wxMenu;
    file->Append(wxID_EXIT, wxT("&Quit"));
    menubar->Append(file, wxT("&File"));
    SetMenuBar(menubar);
/*
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxButton *button = new wxButton(panel, wxID_EXIT, wxT("Quit"), wxPoint(20, 20));

    button->SetFocus();

    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnQuit));*/
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI::OnQuit));
    
    Centre();
}
void GUI::OnQuit(wxCommandEvent & WXUNUSED(event))
{
    Close(true);
}