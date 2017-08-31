#include "../include/SystemControl.hpp"
 
SystemControl::SystemControl(const char* TTDevice, const char* camDevice) :
				CSH(camDevice, &eX, &eY, &mtxProtectingErrors),
				TT(TTDevice, &eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
}

int SystemControl::Start() {
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
		mtxProtectingFrame.lock();
		frame = CSH.CaptureAndProcess();
		mtxProtectingFrame.unlock();
		SendFrame();
		this_thread::sleep_for(chrono::milliseconds(5));
	}
}

void SystemControl::SendFrame(){
	mtxProtectingFrame.lock();
	player_p->DisplayFrame(frame);
	mtxProtectingFrame.unlock();
}

int SystemControl::Stop() {
	capturing = false;

	capturingThread.join();
	return 0;
}
