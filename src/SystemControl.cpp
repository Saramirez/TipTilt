#include "../include/SystemControl.hpp"
 
SystemControl::SystemControl(const char* TTDevice, const char* camDevice) :
				CSH(camDevice, &eX, &eY, &mtxProtectingErrors),
				TT(TTDevice, &eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
}


int SystemControl::Setup() {
	if (CSH.OpenCamera() != 0) {
		cout << "Could not open camera" << endl;
		return -1;
	}
	/*
	Mat * frame;

	frame = CSH.GrabOneFrame();
	cout << "SC frame w, h: " << frame->cols << ", " << frame->rows << endl;
	wxImage img = wxImage(frame->cols,
		frame->rows,
		frame->data,
		TRUE);
	wxBitmap bmp(img);
	cout << "SC bmp: " << &bmp << endl;
	cout << "SC bmp w, h: " << bmp.GetWidth() << ", " << bmp.GetHeight() << endl;

	cout << "Camera stream setup ready" << endl;
	player_p->bmp = bmp;
	wxCommandEvent evt(FRAME_READY, sControlId);
	player_p->GetEventHandler()->AddPendingEvent(evt);

	cout << "FRAME_READY event posted" << endl;*/
}

int SystemControl::Start() {
	cout << "Called start" << endl;
	
}

int SystemControl::Run(){

}
