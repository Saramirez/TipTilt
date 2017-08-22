#ifndef wxSTH_H
#define wxSTH_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "../include/CameraStreamHandler.hpp"
#include "../include/wxStreamPlayer.hpp"
#include "opencv2/opencv.hpp"

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(FRAME_READY, -1);
END_DECLARE_EVENT_TYPES()

class wxStreamThread : public wxThread{
    private:
        wxStreamPlayer * parent;
        CameraStreamHandler * csh;
        wxImage wximage;
        wxBitmap * wxbitmap;
    public:
        wxStreamThread(wxStreamPlayer *, CameraStreamHandler *);
        int Open();
        virtual void * Entry();
};



#endif