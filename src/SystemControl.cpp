#include "../include/SystemControl.hpp"
#include "../include/wxStreamThread.hpp"
 
SystemControl::SystemControl(const char* TTDevice, const char* camDevice) :
				CSH(camDevice, &eX, &eY, &mtx),
				TT(TTDevice, &eX, &eY, &mtx){
	eX = 0;
	eY = 0;
}

void SystemControl::SetPlayer(wxStreamPlayer * _player_p) {
	player_p = _player_p;
}

wxImage * SystemControl::GetWxBitmap() {
	return &bmp;
}

wxMutex * SystemControl::GetWxMutexProtectingBitmap() {
	return &mtxProtectingBitmap;
}

int SystemControl::Setup() {
	if (CSH -> OpenCamera() != 0) {
		cout << "Could not open camera" << endl;
		return -1;
	}
	Mat * frame;

	frame = CSH->GrabOneFrame();
	img = wxImage(frame->cols,
		frame->rows,
		frame->data,
		TRUE);
	mtxProtectingBitmap.Lock();
	bmp = wxBitmap(img);
	mtxProtectingBitmap.Unlock();

	cout << "Camera stream setup ready" << endl;

	wxCommandEvent evt(FRAME_READY, GetId());
	player_p->GetEventHandler()->AddPendingEvent(evt);
}

int SystemControl::Start() {
	wxStreamThread * sThread = new wxStreamThread(player_p, &CSH, &img, &bmp, &mtxProtectingBitmap);

	sThread->Create();
	sThread->Run();
}
