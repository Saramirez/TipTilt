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
	correcting = true;
	if (!TT.isOpened()) {
		cout << "TT device is not open" << endl;
		return -1;
	}
	correctingThread = thread(&SystemControl::RunCorrection, this);
	return 0;
}

void SystemControl::RunCorrection() {
	while (correcting) {
		TT.updatePosition();
		this_thread::sleep_for(chrono::microseconds(100));
	}
}

int SystemControl::StopCorrection() {
	correcting = false;
	correctingThread.join();
	return 0;
}

