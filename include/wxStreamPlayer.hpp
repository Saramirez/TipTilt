#ifndef wxSP_H
#define wxSP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "opencv2/opencv.hpp"

class wxStreamPlayer : public wxWindow {
    private:
        wxWindow * parent;
        //wxBitmap * wxbitmap_p;
		//wxMutex * mtxProtectingBitmap_p;
		void DisplayFrame(Mat);
        void OnPaint(wxPaintEvent&);
        void OnFrameReady(wxCommandEvent&);
		wxImage img;
		wxBitmap bmp;

    public:
        wxStreamPlayer(wxWindow *, const wxPoint&, const wxSize&);

    protected:
		DECLARE_EVENT_TABLE();
};

#endif