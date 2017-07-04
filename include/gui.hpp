#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "../include/wxCameraStreamHandler.hpp"

class GUI : public wxFrame {
	public: 
	    GUI(const wxString& title);
	    void createWxCSH();
};