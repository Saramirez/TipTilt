#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "../include/wxStreamPlayer.hpp"
#include "../include/SystemControl.hpp"

class GUI : public wxFrame {
	public: 
		wxStreamPlayer * player;
		SystemControl * sControl_p;
	    GUI(const wxString&);
};