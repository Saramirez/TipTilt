#include "../include/SystemControl.hpp"
 
SystemControl::SystemControl(const char* TTDevice, const char* camDevice) :
				CSH(camDevice, &eX, &eY, &mtxProtectingErrors),
				TT(TTDevice, &eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
	capturing = false;
	correcting = false;
	showThresh = false;
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
	if (!CSH.IsCameraOpen())
		if(CSH.OpenCamera() != 0) {
			cout << "Could not open camera" << endl;
			return -1;
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
		cout << "TT device is not open" << endl;
		return -1;
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
	return 0;
}

bool SystemControl::IsCapturing() {
	return capturing;
}

bool SystemControl::IsCorrecting() {
	return correcting;
}

