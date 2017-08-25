#include "../include/wxStreamThread.hpp"
#include <iostream>

using namespace std;

DEFINE_EVENT_TYPE(FRAME_READY);

wxStreamThread::wxStreamThread(wxStreamPlayer * _player_p,
                               CameraStreamHandler * _CSH_p){
    player_p = _player_p;
    CSH_p = _CSH_p;
}
void * wxStreamThread::Entry(){
	cout << "Called Entry" << endl;
	if (!(CSH_p->IsCameraOpen())) {
		cout << "Camera is not open" << endl;
		return 0;
	}
    Mat frame;
	frame = CSH_p->GrabOneFrame();
	cout << "SC frame w, h: " << frame.cols << ", " << frame.rows << endl;
	img = wxImage(frame.cols,
		frame.rows,
		frame.data,
		TRUE);
	wxCommandEvent evt(FRAME_READY, GetId());
	player_p->GetEventHandler()->AddPendingEvent(evt);
	cout << "FRAME_READY event posted" << endl;
/*
    while(1){
        frame = CSH_p -> CaptureAndProcess();
		//cout << "thread frame w, h: " << frame->cols << ", " << frame->rows << endl;
		bmp = wxBitmap(img);
		//player_p->bmp = bmp;
        //cout << "thread_bmp w, h: " << bmp.GetWidth() << ", " << bmp.->GetHeight() << endl;
        wxCommandEvent evt(FRAME_READY, GetId());
        player_p->GetEventHandler()->AddPendingEvent(evt);
		cout << "FRAME_READY event posted" << endl;
    }*/
	return 0;
}