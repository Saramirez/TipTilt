#include "../include/wxStreamThread.hpp"
#include <iostream>

using namespace std;

DEFINE_EVENT_TYPE(FRAME_READY);

wxStreamThread::wxStreamThread(wxStreamPlayer * _parent,
                               CameraStreamHandler * _csh){
    parent = _parent;
    csh = _csh;
    wxbitmap = parent->GetBitmap();
}
void * wxStreamThread::Entry(){
    Mat * frame;

    while(1){
        frame = csh -> CaptureAndProcess();
        *wxbitmap = wxBitmap(wximage);
        
        wxCommandEvent evt(FRAME_READY, GetId());
        parent->GetEventHandler()->AddPendingEvent(evt);
    }
}
int wxStreamThread::Open(){
    if(csh -> OpenCamera() != 0){
            cout << "Could not open camera" << endl;
            return -1;
        }
    Mat * frame;

    frame = csh -> GrabOneFrame();
    wximage = wxImage(frame -> cols,
                    frame -> rows,
                    frame -> data,
                    TRUE);
    *wxbitmap = wxBitmap(wximage);
    wxCommandEvent evt(FRAME_READY, GetId());
    cout << "Opened" << endl;
    return 0;
}