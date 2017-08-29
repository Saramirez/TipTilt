#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "../include/SystemControl.hpp"

class GUI : public wxFrame {
	private:
		SystemControl * sControl_p;
		wxStreamPlayer player;
	public: 
	    GUI(const wxString&, SystemControl *);
		void Go();
};