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
		cout << "Intro pressed" << endl;
		ToggleCorrection();
		break;
	case 43: // +
		cout << "+ pressed" << endl;
		ChangeThresh(1);
		break;
	case 45: // -
		cout << "- pressed" << endl;
		ChangeThresh(0);
		break;
	case 67: // C
		cout << "C pressed" << endl;
		CenterTT();
		break;
	case 83: // S
		cout << "S pressed" << endl;
		ToggleSimulate();
		break;
	case 116: // t
		cout << "t pressed" << endl;
		ToggleShowThresh();
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
		CSH.SetDevice("v4l2src device=/dev/video1 ! video/x-raw,format=GRAY8, width=640, height=480 ! appsink");
		break;
	case 2:
		CSH.SetDevice("v4l2src device=/dev/video2 ! video/x-raw,format=GRAY8 ! appsink");
		break;
	case 3:
		CSH.SetDevice("v4l2src device=/dev/video3 ! video/x-raw,format=GRAY8 ! appsink");
		break;
	}
	//video/x-raw,format=GRAY8, width=640, height=480 ! appsink
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

void SystemControl::ChangeThresh(int increase) {
	mtxProtectingValues.lock();
	if (!showThresh) {
		mtxProtectingValues.unlock();
		return;
	}
	int thrs = CSH.thresh;
	mtxProtectingValues.unlock();

	if (increase)
		SetThreshold(thrs + 5);
	else
		SetThreshold(thrs - 5);
}

void SystemControl::SetStarSize(double _starRadius) {
	if (_starRadius > 50 || _starRadius < 0) {
		cout << "Star radius value must be 0 - 50" << endl;
		return;
	}
	CSH.starRadius = _starRadius;
}

int SystemControl::StartCapture() {
	cout << "Starting capture" << endl;

	CheckAndOpenCam();

	dControl.CreateMainWindows();
	dControl.UpdateTTPos(0, 0);

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
	cout << "Starting correction ..." << endl;

	CheckAndOpenTT();

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
	if (correcting)
		StopCorrection();

	CheckAndOpenTT();

	TT.goTo('K');
	TT.sSteps = 0;
	TT.eSteps = 0;
	mtxProtectingDisplayControl.lock();
	dControl.UpdateTTPos(0, 0);
	mtxProtectingDisplayControl.unlock();	
}

int SystemControl::CalibrateTT() {
	dControl.CreateCalibrationWindow();

	CheckAndOpenCam();	
	CheckAndOpenTT();

	cout << "Starting calibration of TT.\n" <<
			"Make sure a star is correctly visible.\n" <<
			"Press enter to continue." << endl;

	while (waitKey(10) != 10) {
		frame = CSH.GrabOneFrame(true, false);
		dControl.DisplayFrame(frame, 'c');
	}

	// Grab one frame at the extremes of TT movement range
	Mat K, N, S, E, W;
	Point cK, cN, cS, cE, cW;
	TT.goTo('K');

	K = CSH.GrabOneFrame(true, false);
	dControl.DisplayFrame(K, 'c');
	waitKey(100);

	cK = CSH.GetCentroid(K);

	TT.goTo('N');
	N = CSH.GrabOneFrame(true, false);
	dControl.DisplayFrame(N, 'c');
	waitKey(100);


	cN = CSH.GetCentroid(N);

	int NSSteps = TT.goTo('S');
	S = CSH.GrabOneFrame(true, false);
	dControl.DisplayFrame(S, 'c');
	waitKey(100);

	cS = CSH.GetCentroid(S);

	TT.goTo('K');

	TT.goTo('E');
	E = CSH.GrabOneFrame(true, false);
	dControl.DisplayFrame(E, 'c');
	waitKey(100);
	
	cE = CSH.GetCentroid(E);

	int EWSteps = TT.goTo('W');
	W = CSH.GrabOneFrame(true, false);
	dControl.DisplayFrame(W, 'c');
	waitKey(100);

	cW = CSH.GetCentroid(W);

	TT.goTo('K');

	//Get the centroids of each frame and measure the distance (in steps and pixels) between them
	/*cK = CSH.GetCentroid(K);
	cN = CSH.GetCentroid(N);
	cS = CSH.GetCentroid(S);
	cE = CSH.GetCentroid(E);
	cW = CSH.GetCentroid(W);
	*/

	cout << "Centroids: " << cK.x << "," << cK.y << ";" << cN.x << "," << cN.y << ";"
		<< cS.x << "," << cS.y << ";" << cE.x << "," << cE.y << ";"
		<< cW.x << "," << cW.y << endl;

	double NSDist = sqrt(pow(cN.x - cS.x, 2) + pow(cN.y - cS.y, 2));
	double EWDist = sqrt(pow(cE.x - cW.x, 2) + pow(cE.y - cW.y, 2));

	double xPixToSteps = ((double)EWSteps) / EWDist;
	double yPixToSteps = ((double)NSSteps) / NSDist;

	cout << "Factors (x, y): " << xPixToSteps << "," << yPixToSteps << endl;

	double tan1 = ((double)(cW.y - cE.y)) / ((double)(cE.x - cW.x));
	double tan2 = ((double)(cN.x - cS.x)) / ((double)(cN.y - cS.y));

	double alpha = atan(tan1);
	double beta = atan(tan2);

	double corrAngle = (alpha + beta) / 2.0;
	double cosCorrAngle = cos(corrAngle);
	double sinCorrAngle = sin(corrAngle);

	cout << "Angles (alpha, beta): " << alpha << "," << beta << endl;

	int threshold = CSH.thresh;
	cout << "Threshold: " << threshold << endl;
	Point target = CSH.GetTarget();
	cout << "Target: " << target << endl;
	CSH.SetPixToStepsFactors(xPixToSteps, yPixToSteps);

	Mat complete = (K > threshold) + (N > threshold) + (S > threshold) + (E > threshold) + (W > threshold);

	cvtColor(complete, complete, CV_GRAY2RGB);
	circle(complete, cK, 5, Scalar(0, 0, 0));
	circle(complete, cN, 5, Scalar(0, 128, 0));
	circle(complete, cS, 5, Scalar(0, 0, 128));
	circle(complete, cE, 5, Scalar(128, 0, 0));
	circle(complete, cW, 5, Scalar(128, 128, 128));

	dControl.DisplayFrame(complete, 'c');
	cout << "\n Calibration done. Press any key to continue." << endl;

	waitKey(0);

	dControl.DestroyCalibrationWindow();

	return 0;
}

void SystemControl::Guide() {
	dControl.CreateGuidingWindow();
	CheckAndOpenCam();

	cout << "Starting guiding.\n" <<
		"Move telescope until star is on top of the pinhole.\n" <<
		"Press s to measure star size or enter to continue to tip tilt correction." << endl;
	int key = 0;
	while (key != 10) {
		key = waitKey(100);
		if (key == 115) {
			frame = CSH.GetStarParams();
			dControl.DisplayFrame(frame, 'g');
			cout << "Star measured. Press any key to continue." << endl;
			waitKey(0);
		}
		else if(key == 27){ //esc
			cout << "Esc key pressed" << endl;
			dControl.DestroyGuidingWindow();
			return;
		}
		else {
			frame = CSH.GrabOneFrame(true, true);
			dControl.DisplayFrame(frame, 'g');
		}
	}

	dControl.DestroyGuidingWindow();
}

void SystemControl::CheckAndOpenCam() {
	if (!CSH.IsCameraOpen()) {
		if (CSH.OpenCamera() != 0) {
			cout << "Could not open camera" << endl;
			return;
		}
		cout << "Opened camera" << endl;
	}
}

void SystemControl::CheckAndOpenTT() {
	if (!TT.isOpened()) {
		if (TT.openComm() != 0) {
			cout << "Could not open TT device" << endl;
			return;
		}
		cout << "Opened TT device" << endl;
	}
}

void SystemControl::SimpleCalib(){
	CheckAndOpenTT();

	TT.goTo('K');

	this_thread::sleep_for(chrono::milliseconds(100));

	TT.goTo('N');

	this_thread::sleep_for(chrono::milliseconds(2000));
	TT.goTo('S');
	this_thread::sleep_for(chrono::milliseconds(2000));
	
	TT.goTo('K');
	this_thread::sleep_for(chrono::milliseconds(100));
	
	TT.goTo('E');
	this_thread::sleep_for(chrono::milliseconds(2000));
	
	TT.goTo('W');
	this_thread::sleep_for(chrono::milliseconds(2000));
	
}
