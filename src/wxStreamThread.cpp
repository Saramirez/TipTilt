#include "../include/wxStreamThread.hpp"
#include <iostream>

using namespace std;

DEFINE_EVENT_TYPE(FRAME_READY);

wxStreamThread::wxStreamThread(wxStreamPlayer * _player_p,
                               CameraStreamHandler * _CSH_p,
							   wxBitmap * _bmp_p,
							   wxMutex * _mtxProtectingBitmap_p){
    player_p = _player_p;
    CSH_p = _CSH_p;
	bmp_p = _bmp_p;
	mtxProtectingBitmap_p = _mtxProtectingBitmap_p;
}
void * wxStreamThread::Entry(){
	if (!(CSH_p->IsCameraOpen())) {
		cout << "Camera is not open" << endl;
		return 0;
	}
    Mat * frame;
	frame = CSH->GrabOneFrame();
	img = wxImage(frame->cols,
		frame->rows,
		frame->data,
		TRUE);

    while(1){
        frame = CSH_p -> CaptureAndProcess();

		mtxProtectingBitmap.Lock();
        *bmp_p = wxBitmap(img);
		mtxProtectingBitmap.Unlock();
        
        wxCommandEvent evt(FRAME_READY, GetId());
        player_p->GetEventHandler()->AddPendingEvent(evt);
    }
	return 0;
}