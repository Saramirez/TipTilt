#ifndef wxSP_H
#define wxSP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class wxStreamPlayer : public wxWindow {
    private:
        wxWindow * parent;
        wxBitmap * wxbitmap_p;
		wxMutex * mtxProtectingBitmap_p;
        void OnPaint(wxPaintEvent&);
        void OnFrameReady(wxCommandEvent&);

    public:
        wxStreamPlayer(wxWindow *, const wxPoint&, const wxSize&, wxMutex *, wxBitmap *);

    protected:
		DECLARE_EVENT_TABLE();
};

#endif