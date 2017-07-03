#include "../include/gui.hpp"


GUI::GUI(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480))
{
    //SetIcon(wxIcon(wxT("web.xpm")));

    menubar = new wxMenuBar;
    file = new wxMenu;
    file->Append(wxID_EXIT, wxT("&Quit"));
    menubar->Append(file, wxT("&File"));
    SetMenuBar(menubar);
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI::OnQuit));

    wxPanel *panel = new wxPanel(this, wxID_ANY);

    BuildButtons(panel);
   
    Centre();
}

void GUI::BuildButtons(wxPanel* panel){
    wxButton *button = new wxButton(panel, wxID_EXIT, wxT("Quit"), wxPoint(20, 20));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnQuit));
    button->SetFocus();
    
    wxButton *openCameraButton = new wxButton(panel, ID_OpenCam, wxT("Open Camera"), wxPoint(20, 100));
}

void GUI::OnQuit(wxCommandEvent & WXUNUSED(event))
{
    Close(true);
}