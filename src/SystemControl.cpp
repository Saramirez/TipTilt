#include "../include/SystemControl.hpp"
 
SystemControl::SystemControl() :
				CSH(&eX, &eY, &mtxProtectingErrors),
				TT(&eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
	capturing = false;
	correcting = false;
	showThresh = false;
	simulate = false;
}

int SystemControl::GetKeyFromKeyboard() {
	int key = waitKey(10);
	//cout << "Key: " << key << endl;
	switch (key) {
	case 255:
		return 0;
	case 27: // esc
		return -1;
		break;
	case 10: // Intro
		ToggleCorrection();
		return 1; // Start Correction
		break;
	case 116: //t
		ToggleShowThresh();
		break;
	case 119: // w
		break;
	case 115: // s
		break;
	case 100: // d
		break;
	case 97: // a
		break;
	}
	//cout << "Target: " << target.x << "," << target.y << endl;
	return 0;
}

void SystemControl::ToggleCorrection() {
	if (!correcting) {
		StartCorrection();
	}
	else
		StopCorrection();
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

void SystemControl::ToggleSimulate() {
	mtxProtectingValues.lock();
	simulate = !simulate;
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
	dControl.DisplayFrame(frame, 'g');
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
	mtxProtectingDisplayControl.lock();
	dControl.CreateMainWindows();
	mtxProtectingDisplayControl.unlock();

	capturingInternal = true;
	capturingThread = thread(&SystemControl::RunCapture, this);
	capturing = true;
	return 0;
}

void SystemControl::RunCapture() {
	while (capturingInternal) {
		mtxProtectingValues.lock();
		frame = CSH.CaptureAndProcess(showThresh, simulate);
		mtxProtectingValues.unlock();
		mtxProtectingDisplayControl.lock();
		dControl.DisplayFrame(frame, 'p');
		mtxProtectingDisplayControl.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
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
		dControl.UpdateTTPos(TTposX, TTposY);
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

int SystemControl::CalibrateTT() {
	if (capturing) {
		StopCapture();
	}
	if (correcting) {
		StopCorrection();
	}

	mtxProtectingValues.lock();
	if (!CSH.IsCameraOpen()) {
		if (CSH.OpenCamera() != 0) {
			cout << "Could not open camera" << endl;
			return -1;
		}
	}
	mtxProtectingValues.unlock();
	if (!TT.isOpened()) {
		if (TT.openComm() != 0) {
			cout << "Could not open TT device" << endl;
			return -1;
		}
	}

	// Grab one frame at the extremes of TT movement range
	Mat K, N, S, E, W;
	Point cK, cN, cS, cE, cW;
	TT.goTo('K');

	mtxProtectingValues.lock();
	K = CSH.GrabOneFrame(false, false);
	mtxProtectingValues.unlock();

	/*///
	mtxProtectingValues.lock();
	cK = CSH.GetCentroid(K);
	mtxProtectingValues.unlock();

	cvtColor(K, K, CV_GRAY2RGB);
	circle(K, cK, 5, Scalar(0, 0, 0));
	
	mtxProtectingDisplayControl.lock();
	dControl_p->DisplayFrame(K);
	mtxProtectingDisplayControl.unlock();

	cout << "Centroids: " << cK.x << "," << cK.y << endl;

	return 0;

	*////

	TT.goTo('N');
	mtxProtectingValues.lock();
	N = CSH.GrabOneFrame(false, false);
	mtxProtectingValues.unlock();

	int NSSteps = TT.goTo('S');
	mtxProtectingValues.lock();
	S = CSH.GrabOneFrame(false, false);
	mtxProtectingValues.unlock();

	TT.goTo('K');

	TT.goTo('E');
	mtxProtectingValues.lock();
	E = CSH.GrabOneFrame(false, false);
	mtxProtectingValues.unlock();

	int EWSteps = TT.goTo('W');
	mtxProtectingValues.lock();
	W = CSH.GrabOneFrame(false, false);
	mtxProtectingValues.unlock();

	TT.goTo('K');

	//Get the centroids of each frame and measure the distance (in steps and pixels) between them
	mtxProtectingValues.lock();
	cK = CSH.GetCentroid(K);
	cN = CSH.GetCentroid(N);
	cS = CSH.GetCentroid(S);
	cE = CSH.GetCentroid(E);
	cW = CSH.GetCentroid(W);
	mtxProtectingValues.unlock();

	cout << "Centroids: " << cK.x << "," << cK.y << ";" << cN.x << "," << cN.y << ";"
		<< cS.x << "," << cS.y << ";" << cE.x << "," << cE.y << ";"
		<< cW.x << "," << cW.y << endl;

	double NSDist = sqrt(pow(cN.x - cS.x, 2) + pow(cN.y - cS.y, 2));
	double EWDist = sqrt(pow(cE.x - cW.x, 2) + pow(cE.y - cW.y, 2));

	double xPixToSteps = ((double)NSSteps) / NSDist;
	double yPixToSteps = ((double)EWSteps) / EWDist;

	cout << "Factors (x, y): " << xPixToSteps << "," << yPixToSteps << endl;

	double tan1 = ((double)(cW.y - cE.y)) / ((double)(cE.x - cW.x));
	double tan2 = ((double)(cN.x - cS.x)) / ((double)(cN.y - cS.y));

	double alpha = atan(tan1);
	double beta = atan(tan2);

	cout << "Angles (alpha, beta): " << alpha << "," << beta << endl;


	mtxProtectingValues.lock();
	int threshold = CSH.thresh;
	cout << "Threshold: " << threshold << endl;
	Point target = CSH.GetTarget();
	cout << "Target: " << target << endl;
	//Rect roi((cK.x - target.x), (cK.y - target.y), 100, 100);
	CSH.SetPixToStepsFactors(xPixToSteps, yPixToSteps);
	//CSH.SetRoi(roi);
	mtxProtectingValues.unlock();

	//Rect roi(880, 490, 100, 100);
	Mat complete = (K > threshold) + (N > threshold) + (S > threshold) + (E > threshold) + (W > threshold);
	//Mat complete = K + N + S + W + E;

	cvtColor(complete, complete, CV_GRAY2RGB);
	circle(complete, cK, 5, Scalar(0, 0, 0));
	circle(complete, cN, 5, Scalar(0, 128, 0));
	circle(complete, cS, 5, Scalar(0, 0, 128));
	circle(complete, cE, 5, Scalar(128, 0, 0));
	circle(complete, cW, 5, Scalar(128, 128, 128));
	//complete = complete(roi);

	mtxProtectingDisplayControl.lock();
	dControl.DisplayFrame(complete, 'c');
	mtxProtectingDisplayControl.unlock();

	return 0;
}
