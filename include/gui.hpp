#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "../include/TipTilt.hpp"
#include "../include/CameraStreamHandler.hpp"

class GUI : public wxFrame {
	private:
		CameraStreamHandler * CSH;
		TipTilt * TT;
	public: 
	    GUI(const wxString&, CameraStreamHandler *, TipTilt *);
	    void createWxSP();
};