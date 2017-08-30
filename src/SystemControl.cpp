#include "../include/SystemControl.hpp"
#include "../include/wxStreamThread.hpp"
 
SystemControl::SystemControl(const char* TTDevice, const char* camDevice) :
				CSH(camDevice, &eX, &eY, &mtxProtectingErrors),
				TT(TTDevice, &eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
}

int SystemControl::Start() {
	capturing = true;
	if (!CSH.OpenCamera()) {
		cout << "Could not open camera" << endl;
		return -1;
	}
	capturingThread = thread(&SystemControl::RunCapture, this);
	return 0;
}

void SystemControl::RunCapture() {
	Mat frame;
	while (capturing) {
		frame = CSH.CaptureAndProcess();
		player_p->DisplayFrame(frame);
		this_thread::sleep_for(chrono::milliseconds(5));
	}
}

int SystemControl::Stop() {
	capturing = false;

	capturingThread.join();
	return 0;
}
