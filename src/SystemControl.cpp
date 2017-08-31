#include "../include/SystemControl.hpp"
 
SystemControl::SystemControl(const char* TTDevice, const char* camDevice) :
				CSH(camDevice, &eX, &eY, &mtxProtectingErrors),
				TT(TTDevice, &eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
}

int SystemControl::StartCapture() {
	capturing = true;
	if (CSH.OpenCamera() != 0) {
		cout << "Could not open camera" << endl;
		return -1;
	}
	capturingThread = thread(&SystemControl::RunCapture, this);
	return 0;
}

void SystemControl::RunCapture() {
	while (capturing) {
		frame = CSH.CaptureAndProcess();
		player_p->DisplayFrame(frame);
		this_thread::sleep_for(chrono::milliseconds(5));
	}
}

int SystemControl::StopCapture() {
	capturing = false;
	capturingThread.join();
	return 0;
}

int SystemControl::StartCorrection(){
	if(TT.start() !=0 ){
		cout << "Could not start TT" << endl;
		return -1;
	}
	return 0;
}

