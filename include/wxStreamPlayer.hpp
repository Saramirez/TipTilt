#ifndef wxSP_H
#define wxSP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(FRAME_READY, -1);
END_DECLARE_EVENT_TYPES()

class wxStreamPlayer : public wxWindow {
    private:
        wxWindow * parent;
        //wxBitmap * wxbitmap_p;
		//wxMutex * mtxProtectingBitmap_p;
        void OnPaint(wxPaintEvent&);
        void OnFrameReady(wxCommandEvent&);

    public:
        wxStreamPlayer(wxWindow *, const wxPoint&, const wxSize&);
        wxBitmap bmp;

    protected:
		DECLARE_EVENT_TABLE();
};

#endif