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

void SystemControl::CheckBumps(int& NSBump, int& WEBump) {
	switch (TT.getBump(0)) {
	case 0:
		if (NSBump != 0) {
			NSBump = 0;
			cout << "NSBump not needed" << endl;
		}
		break;
	case -1:
		if (NSBump != -1) {
			NSBump = -1;
			cout << "NSBump up" << endl;
		}
		break;
	case 1:
		if (NSBump != 1) {
			NSBump = 1;
			cout << "NSBump down" << endl;
		}
		break;
	}

	switch (TT.getBump(1)) {
	case 0:
		if (WEBump != 0) {
			WEBump = 0;
			cout << "WEBump not needed" << endl;
		}
		break;
	case -1:
		if (WEBump != -1) {
			WEBump = -1;
			cout << "WEBump to the left" << endl;
		}
		break;
	case 1:
		if (WEBump != 1) {
			WEBump = 1;
			cout << "WEBump to the right" << endl;
		}
		break;
	}
}

void SystemControl::RunCorrection() {
	int NSBump = 0;
	int WEBump = 0;
	while (correcting) {		
		CheckBumps(NSBump, WEBump);
		TT.updatePosition();
		this_thread::sleep_for(chrono::microseconds(100));
	}
}

int SystemControl::StopCorrection() {
	correcting = false;
	correctingThread.join();
	return 0;
}

bool SystemControl::IsCapturing() {
	return capturing;
}

bool SystemControl::IsCorrecting() {
	return correcting;
}

