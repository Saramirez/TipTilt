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
        wxStreamPlayer * player_p;
        CameraStreamHandler * CSH_p;
		wxImage img;
        wxBitmap bmp;
    public:
        wxStreamThread(wxStreamPlayer *, CameraStreamHandler *);
        virtual void * Entry();
};



#endif