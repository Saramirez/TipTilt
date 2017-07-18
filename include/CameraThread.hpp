#ifndef CAMTHREAD_H
#define 

#include "opencv2/opencv.hpp"
#include <iostream>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

using namespace cv;
using namespace std;
BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(wxEVT_COMMAND_CAMERA_THREAD_COMPLETED, -1)
    DECLARE_EVENT_TYPE(wxEVT_COMMAND_CAMERA_THREAD_UPDATE, -1)
END_DECLARE_EVENT_TYPES()

class CameraThread : public wxThread{

	public:
	    CameraThread(wxEvtHandler*, VideoCapture*);
	    ~CameraThread();

	protected:
	    virtual ExitCode Entry();
	    wxEvtHandler* handler;
	    VideoCapture* cam;
	    void captureAndProcess();
};

#endif 