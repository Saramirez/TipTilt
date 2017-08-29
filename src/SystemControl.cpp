#include "../include/SystemControl.hpp"

DEFINE_EVENT_TYPE(FRAME_READY);

SystemControl::SystemControl(const char* TTDevice, const char* camDevice) :
				CSH(camDevice, &eX, &eY, &mtxProtectingErrors),
				TT(TTDevice, &eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
}

void SystemControl::SetPlayer(wxStreamPlayer * _player_p){
	player_p = _player_p;
}


int SystemControl::Setup() {
	if (CSH.OpenCamera() != 0) {
		cout << "Could not open camera" << endl;
		return -1;
	}
	/*
	Mat frame;

	frame = CSH.GrabOneFrame();
	cout << "SC frame w, h: " << frame->cols << ", " << frame->rows << endl;
	wxImage img = wxImage(frame->cols,
		frame->rows,
		frame->data,
		TRUE);
	wxBitmap bmp(img);
	player_p->bmp = bmp;
	wxCommandEvent evt(FRAME_READY, sControlId);
	player_p->GetEventHandler()->AddPendingEvent(evt);
	
	cout << "SC bmp: " << &bmp << endl;
	cout << "SC bmp w, h: " << bmp.GetWidth() << ", " << bmp.GetHeight() << endl;

	cout << "Camera stream setup ready" << endl;
	*/
}
/*
void SystemControl::GetFrames(){
	Mat frame;
	wxImage img(frame.cols,
		frame.rows,
		frame.data,
		TRUE);
	wxBitmap bmp(img);
	
	while(1){
		frame = CSH.CaptureAndProcess();

	}
}*/

void SystemControl::Start() {
	cout << "Called start" << endl;	
	capturing = true;
	captureThread = thread(&SystemControl::Run, this);
	captureThread.detach();
}

void SystemControl::Run(){
	cout << "Started thread" << endl;
	Mat frame;
	frame = CSH.GrabOneFrame();
	//cout << "Captured frame" << endl;
	wxImage img(frame.cols,
		frame.rows,
		frame.data,
		TRUE);
	//cout << "Copied to image" << endl;
	wxBitmap bmp(img);
	//cout << "Copied to bmp" << endl;
	player_p->bmp = bmp;
	wxCommandEvent evt(FRAME_READY, sControlId);
	player_p->GetEventHandler()->AddPendingEvent(evt);

	
	while(capturing){
		frame = CSH.GrabOneFrame();
		//cout << "1" << endl;
		bmp = wxBitmap(img);
		//cout << "2" << endl;
		player_p->bmp = bmp;
		wxCommandEvent evt(FRAME_READY, sControlId);
		player_p->GetEventHandler()->AddPendingEvent(evt);
		//cout << "Grr" << endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void SystemControl::Stop(){
	capturing = false;
	//captureThread.join();
}
