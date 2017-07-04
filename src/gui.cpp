#include "../include/gui.hpp"

GUI::GUI(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title) {

    Centre();
}

void GUI::createWxCSH(){
    wxCameraStreamHandler* csh = new wxCameraStreamHandler(
        this, 
        wxPoint(-1,-1),
        wxSize(640, 480));

    csh->openCamera( "v4l2src ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");
    csh->Show(true);
    csh->startCapture();
}
