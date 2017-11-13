#include "../include/SystemControl.hpp"

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

SystemControl::SystemControl() :
				CSH(&eX, &eY, &mtxProtectingErrors),
				TT(&eX, &eY, &mtxProtectingErrors){
	eX = 0;
	eY = 0;
	capturing = false;
	correcting = false;
	showThresh = false;
	simulate = false;
	withFilter = false;
	measuringFWHMaux = false;
	GetPinholePosFromFile("../src/Values.txt");
}

int SystemControl::GetKeyFromKeyboard() {
	int key = waitKey(10);
	//cout << "Key: " << key << endl;
	switch (key) {
	case 27: // esc
		cout << "Esc pressed, exiting" << endl;
		return -1;
		break;
	case 10: // Intro
		cout << "Intro pressed" << endl;
		ToggleCorrection();
		break;
	case '1': // 1
		cout << "1 pressed" << endl;
		ChangeThresh(0);
		break;
	case '2': // 2
		cout << "2 pressed" << endl;
		ChangeThresh(1);
		break;
	case 'C': // C
		cout << "C pressed" << endl;
		CenterTT();
		break;
	case 'S': // S
		cout << "S pressed" << endl;
		//ToggleSimulate();
		break;
	case 't': // t
		cout << "t pressed" << endl;
		ToggleShowThresh();
		break;
	case 'm': // m
		cout << "m pressed" << endl;
		ToggleConstantRate();
		break;
	case '3': // m
		cout << "3 pressed" << endl;
		ChangeTimeBetweenUpdates(0);
		break;
	case '4': // m
		cout << "4 pressed" << endl;
		ChangeTimeBetweenUpdates(1);
		break;
	case 'f': // f
		cout << "f pressed" << endl;
		ChangeErrorFilter();
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
		cout << "Can't set that device for cam" << endl;
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

void SystemControl::ToggleConstantRate() {
	mtxProtectingValues.lock();
	constatRate = !constatRate;
	mtxProtectingValues.unlock();

	if (constatRate)
		cout << "Constant rate mode enabled." << endl;
	else
		cout << "Constant rate mode disabled." << endl;
}

void SystemControl::ToggleSimulate() {
	mtxProtectingValues.lock();
	simulate = !simulate;
	mtxProtectingValues.unlock();
}

void SystemControl::ChangeErrorFilter() {
	mtxProtectingValues.lock();
	withFilter += 1;
	if (withFilter == 3)
		withFilter = 0;
	cout << "With filter: " << withFilter << endl;
	mtxProtectingValues.unlock();
}

void SystemControl::SetThreshold(int _thresh) {
	if (_thresh > 255 || _thresh < 0) {
		cout << "Threshold value must be 0 - 255" << endl;
		return;
	}
	mtxProtectingValues.lock();
	CSH.thresh = _thresh;
	cout << "New threshold: " << CSH.thresh << endl;
	mtxProtectingValues.unlock();
}

void SystemControl::ChangeThresh(int increase) {
	mtxProtectingValues.lock();
	if (!showThresh) {
		mtxProtectingValues.unlock();
		return;
	}
	int thrs = CSH.thresh;
	if (increase) {
		thrs = min(thrs + 5, 255);
	}
	else {
		thrs = max(thrs - 5, 0);
	}
	CSH.thresh = thrs;
	cout << "New threshold: " << CSH.thresh << endl;
	mtxProtectingValues.unlock();
}

void SystemControl::ChangeTimeBetweenUpdates(int increase) {
	mtxProtectingValues.lock();
	if (!constatRate) {
		mtxProtectingValues.unlock();
		return;
	}
	if (increase)
		timeBetweenUpdates += 10;
	else
		timeBetweenUpdates -= 10;

	cout << "New time between updates: " << timeBetweenUpdates << endl;
	mtxProtectingValues.unlock();
}

int SystemControl::StartCapture() {
	cout << "Starting capture" << endl;
	cout << "\nPress t to view thresholded image, 1-2 to change threshold, C to center TT," <<
			"f to change error filtering, m to change into constant update rate mode, 3-4 to change the time between updates and Intro to start correction. Esc to end.\n" << endl;
	CheckAndOpenCam(); 
	CheckAndOpenTT();
	TT.goTo('K');
	TT.closeComm();

	dControl.CreateMainWindows();
	dControl.UpdateTTPos(0, 0);

	capturingInternal = true;
	capturingThread = thread(&SystemControl::RunCapture, this);
	capturing = true;

	while (GetKeyFromKeyboard() != -1) {
	}
	StopCapture();

	if (IsCorrecting())
		StopCorrection();
	return 0;
}

void SystemControl::RunCapture() {
	auto time1 = get_time::now();
	auto time2 = get_time::now();
	auto elapsedTime = time2 - time1;
	auto eTimeMS = chrono::duration_cast<ms>(elapsedTime).count();// / 1000.0; //seconds
	/*
	auto frameRate = 1000.0 / eTimeMS;
	int avgFrameRate = frameRate;
	vector<double> frameRates;
	for (int i = 0; i < 20; i++)
		frameRates.push_back(0.0);
	*/

	bool updateErrors = true;

	while (capturingInternal) {		
		if (constatRate) { //Si quiero actualizar los errores a una frecuencia constante
			if (updateErrors)
				updateErrors = false;
			time2 = get_time::now();
			elapsedTime = time2 - time1;
			eTimeMS = chrono::duration_cast<ms>(elapsedTime).count();
			if (eTimeMS >= timeBetweenUpdates) {
				time1 = time2;
				updateErrors = true;
			}
		}
		else
			if (!updateErrors)
				updateErrors = true;
		/*
		frameRate = 1000.0 / eTimeMS;
		frameRates.push_back(frameRate);
		frameRates.erase(frameRates.begin());
		avgFrameRate = accumulate(frameRates.begin(), frameRates.end(), 0.0) / frameRates.size();
		*/

		mtxProtectingValues.lock();
		frame = CSH.CaptureAndProcess(showThresh, simulate, withFilter, updateErrors);
		mtxProtectingValues.unlock();
		mtxProtectingDisplayControl.lock();
		dControl.DisplayFrame(frame, 'p');
		//dControl.SetFrameRate(avgFrameRate);
		mtxProtectingDisplayControl.unlock();
		this_thread::sleep_for(chrono::microseconds(100));
	}
}

int SystemControl::StopCapture() {
	capturingInternal = false;
	capturingThread.join();
	capturing = false;
	return 0;
}

int SystemControl::StartCorrection(){
	cout << "Starting correction" << endl;

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
	dControl.CreateWindow('c');

	CheckAndOpenCam();
	CheckAndOpenTT();
/*
	cout << "Starting calibration of TT.\n" <<
			"Make sure a star is correctly visible.\n" <<
			"Press enter to continue." << endl;

	while (waitKey(10) != 10) {
		frame = CSH.GrabOneFrame(true);
		dControl.DisplayFrame(frame, 'c');
	}
*/
	// Grab one frame at the extremes of TT movement range
	Mat K, N, S, E, W;
	Point cK, cN, cS, cE, cW;
	TT.goTo('K');

	K = CSH.GrabOneFrame(false);
	dControl.DisplayFrame(K, 'c');
	waitKey(100);

//	cK = CSH.GetCentroid(K);

	TT.goTo('N');
	N = CSH.GrabOneFrame(false);
	dControl.DisplayFrame(N, 'c');
	waitKey(100);


//	cN = CSH.GetCentroid(N);

	int NSSteps = TT.goTo('S');
	S = CSH.GrabOneFrame(false);
	dControl.DisplayFrame(S, 'c');
	waitKey(100);

//	cS = CSH.GetCentroid(S);

	TT.goTo('K');

	TT.goTo('E');
	E = CSH.GrabOneFrame(false);
	dControl.DisplayFrame(E, 'c');
	waitKey(100);

//	cE = CSH.GetCentroid(E);

	int EWSteps = TT.goTo('W');
	W = CSH.GrabOneFrame(false);
	dControl.DisplayFrame(W, 'c');
	waitKey(100);

//	cW = CSH.GetCentroid(W);

	TT.goTo('K');

	//Get the centroids of each frame and measure the distance (in steps and pixels) between them
	cK = CSH.GetCentroid(K);
	cN = CSH.GetCentroid(N);
	cS = CSH.GetCentroid(S);
	cE = CSH.GetCentroid(E);
	cW = CSH.GetCentroid(W);


	cout << "Centroids: " << cK.x << "," << cK.y << ";" << cN.x << "," << cN.y << ";"
		<< cS.x << "," << cS.y << ";" << cE.x << "," << cE.y << ";"
		<< cW.x << "," << cW.y << endl;

	double NSDist = sqrt(pow(cN.x - cS.x, 2) + pow(cN.y - cS.y, 2));
	double EWDist = sqrt(pow(cE.x - cW.x, 2) + pow(cE.y - cW.y, 2));

	double xPixToSteps = ((double)EWSteps) / EWDist;
	double yPixToSteps = ((double)NSSteps) / NSDist;


	cout << "Steps: " << EWSteps << "," << NSSteps << endl;
	cout << "Dists: " << EWDist << "," << NSDist << endl;
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

	CSH.SetPixToStepsFactors(xPixToSteps, yPixToSteps);

	Mat complete = (K > threshold) + (N > threshold) + (S > threshold) + (E > threshold) + (W > threshold);

	cvtColor(complete, complete, CV_GRAY2RGB);
	circle(complete, cK, 5, Scalar(0, 0, 0));
	circle(complete, cN, 5, Scalar(0, 128, 0));
	circle(complete, cS, 5, Scalar(0, 0, 128));
	circle(complete, cE, 5, Scalar(128, 0, 0));
	circle(complete, cW, 5, Scalar(128, 128, 128));

	resize(complete, complete, Size(), 4, 4);
	dControl.DisplayFrame(complete, 'c');
	cout << "\n Calibration done. Press any key to continue." << endl;

	waitKey(0);

	dControl.DestroyWindow('c');

	return 0;
}

int SystemControl::Guide() {
	dControl.CreateWindow('g');

	CheckAndOpenCam();

	cout << "Starting guiding.\n" <<
		"Move telescope until star is on top of the pinhole.\n" <<
		"Press f to measure the FWHM\n or enter to continue to tip tilt correction. z - x to zoom image in - out." << endl;
	int zoom = 0;
	int key = 0;
	while (key != 10) {
		key = waitKey(1);
		switch (key) {
			case 27: //esc
				cout << "Esc pressed, exiting" << endl;
				dControl.DestroyWindow('g');
				return -1;
			break;
			case 102: //f
				cout << "f pressed. Started measuring the FWHM" << endl;
				measuringFWHM = !measuringFWHM;
			break;
			case 122: //z
				cout << "z pressed. Zooming +" << endl;
				zoom += 1;
				cout << "Zoom = " << zoom << endl;
			break;
			case 120: //x
				cout << "x pressed. Zooming -" << endl;
				zoom = max(0, zoom - 1);
				cout << "Zoom = " << zoom << endl;
			break;
			default:
				if (measuringFWHM) {
					if (!measuringFWHMaux) {
						measuringFWHMaux = true;
						dControl.CreateWindow('f');
					}
					Mat plot(300, 100, CV_8UC3, Scalar(0, 0, 0));
					frame = CSH.GrabGuideFrame(zoom, false, plot);
					dControl.DisplayFrame(plot, 'f');
				}
				else if (!measuringFWHM) 
					if (measuringFWHMaux) {
						measuringFWHMaux = false;
						dControl.DestroyWindow('f');
					}
				else
					frame = CSH.GrabGuideFrame(zoom, false);

				dControl.DisplayFrame(frame, 'g');
			break;
		}
	}
	dControl.DestroyWindow('g');
	return 0;
}

void SystemControl::GetPinholePosFromFile(const char* file) {
	ifstream values(file);

	int px, py;
	char letter;
	string line;

	if (values.is_open()) {
		while (getline(values, line)) {
			if (!line.empty())
				if (line.at(0) == 'p')
					values >> px >> py;
		}
	}
	//cout << "Values: " << px << ", " << py << endl;
	if (px > 1280 || px < 0 || py > 1024 || py < 0) {
		cout << "Imposible pinhole position!" << endl;
		values.close();
		return;
	}
	Point pinPos = Point(px, py);

	CSH.SetPinholePosition(pinPos);

	values.close();
}