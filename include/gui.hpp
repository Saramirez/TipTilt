#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/menu.h>

class GUI : public wxFrame
{
	void BuildButtons(wxPanel*);
public: 
    GUI(const wxString& title);
    void OnQuit(wxCommandEvent& event);
    wxMenuBar *menubar;
    wxMenu *file;
};


enum
{
    ID_OpenCam = 1
};