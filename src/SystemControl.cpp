#include "../include/SystemControl.hpp"
 
SystemControl::SystemControl() :
				CSH(&eX, &eY, &mtxProtectingErrors),
				TT(&eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
	capturing = false;
	correcting = false;
	showThresh = false;
}

void SystemControl::SetCamDevice(int id) {
	if (id < 0 || id > 3) {
		cout << "Can't set that device for TT" << endl;
		return;
	}
	switch (id)	{
	case 0:
		CSH.SetDevice("v4l2src device=/dev/video0 ! video/x-raw,format=GRAY8 ! appsink");
		break;
	case 1:
		CSH.SetDevice("v4l2src device=/dev/video1 ! video/x-raw,format=GRAY8 ! appsink");
		break;
	case 2:
		CSH.SetDevice("v4l2src device=/dev/video2 ! video/x-raw,format=GRAY8 ! appsink");
		break;
	case 3:
		CSH.SetDevice("v4l2src device=/dev/video3 ! video/x-raw,format=GRAY8 ! appsink");
		break;
	}
}

void SystemControl::SetTTDevice(int id) {
	if (id < 0 || id > 3) {
		cout << "Can't set that device for TT" << endl;
		return;
	}
	switch (id) {
	case 0:
		TT.setDevice("/dev/ttyUSB0");
		break;
	case 1:
		TT.setDevice("/dev/ttyUSB1");
		break;
	case 2:
		TT.setDevice("/dev/ttyUSB2");
		break;
	case 3:
		TT.setDevice("/dev/ttyUSB3");
		break;
	}
}

void SystemControl::ToggleShowThresh() {
	mtxProtectingValues.lock();
	showThresh = !showThresh;
	mtxProtectingValues.unlock();
}

void SystemControl::SetThreshold(int _thresh) {
	if (_thresh > 255 || _thresh < 0) {
		cout << "Threshold value must be 0 - 255" << endl;
		return;
	}
	mtxProtectingValues.lock();
	CSH.thresh = _thresh;
	mtxProtectingValues.unlock();
}

double SystemControl::GetStarSize() {
	if (capturing) {
		StopCapture();
	}
	if (correcting) {
		StopCorrection();
	}
	if (!CSH.IsCameraOpen()) {
		if (CSH.OpenCamera() != 0) {
			cout << "Could not open camera" << endl;
			return -1;
		}
	}
	mtxProtectingValues.lock();
	frame = CSH.GetStarParams();
	double starRadius = CSH.starRadius;
	mtxProtectingValues.unlock();
	mtxProtectingDisplayControl.lock();
	dControl_p->DisplayFrame(frame);
	mtxProtectingDisplayControl.unlock();
	return starRadius;
}

void SystemControl::SetStarSize(double _starRadius) {
	if (_starRadius > 50 || _starRadius < 0) {
		cout << "Star radius value must be 0 - 50" << endl;
		return;
	}
	mtxProtectingValues.lock();
	CSH.starRadius = _starRadius;
	mtxProtectingValues.unlock();
}

int SystemControl::StartCapture() {
	if (!CSH.IsCameraOpen()) {
		if (CSH.OpenCamera() != 0) {
			cout << "Could not open camera" << endl;
			return -1;
		}
	}
	capturingInternal = true;
	capturingThread = thread(&SystemControl::RunCapture, this);
	capturing = true;
	return 0;
}

void SystemControl::RunCapture() {
	while (capturingInternal) {
		mtxProtectingValues.lock();
		frame = CSH.CaptureAndProcess(showThresh);
		mtxProtectingValues.unlock();
		mtxProtectingDisplayControl.lock();
		dControl_p->DisplayFrame(frame);
		mtxProtectingDisplayControl.unlock();
		this_thread::sleep_for(chrono::milliseconds(5));
	}
}

int SystemControl::StopCapture() {
	capturingInternal = false;
	capturingThread.join();
	capturing = false;
	return 0;
}

int SystemControl::StartCorrection(){
	if (!TT.isOpened()) {
		if (TT.openComm() != 0) {
			cout << "Could not open TT device" << endl;
			return -1;
		}
	}
	correctingInternal = true;
	correctingThread = thread(&SystemControl::RunCorrection, this);
	correcting = true;
	return 0;
}

void SystemControl::RunCorrection() {
	while (correctingInternal) {	
		TT.updatePosition();
		TTposX = TT.sSteps;
		TTposY = TT.eSteps;
		mtxProtectingDisplayControl.lock();
		dControl_p->UpdateTTPos(TTposX, TTposY);
		mtxProtectingDisplayControl.unlock();
		this_thread::sleep_for(chrono::microseconds(100));
	}
}

int SystemControl::StopCorrection() {
	correctingInternal = false;
	correctingThread.join();
	correcting = false;
	TT.closeComm();
	return 0;
}

bool SystemControl::IsCapturing() {
	return capturing;
}

bool SystemControl::IsCorrecting() {
	return correcting;
}

void SystemControl::CenterTT() {
	if (!TT.isOpened()) {
		if (TT.openComm() != 0) {
			cout << "Could not open TT device" << endl;
			return;
		}
	}
	TT.goTo('K');
	TT.sSteps = 0;
	TT.eSteps = 0;
}

