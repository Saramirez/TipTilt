#include "../include/CameraStreamHandling.hpp"
#include <chrono>

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

const double Kp = 1;
const string winName = "Star";
bool targetSet = false;
const int thresh = 100;
Rect roi(300, 180, 80, 80);

Point target(40, 40);
double xPixToSteps = 2.38;
double yPixToSteps = 2.33;
double corrAngle = 0;
double cosCorrAngle = 1;
double sinCorrAngle = 0;

int frameCount = 0;
double avgRateOfChange = 0.0;
double avgRateOfChangeBefore = 0.0;

double avgIllum = 0.0;
double avgIllumBefore = 0.0;
int exposure; //ms
const int testTime = 60;

const double pinholeRadius = 12.5; //12.5*4.8*2 um = 120 um 
const double pinholeArea = M_PI*pinholeRadius*pinholeRadius;

/*
const double ksq = 0.03;
const double k = 0.72;
const double n = 8.54;

const double ksq2 = -0.02;
const double k2 = -0.49;
const double n2 = 0.03;
*/
const double kl1 = 0.36;

const double kl2 = 0.5;
const double n2 = 0.35;

const double kl3 = 1.1;
const double n3 = - 16;

const double kl4 = 1.47;
const double n4 = -27.73;



int OpenCamera(VideoCapture& cam, const string gstreamPipeline){
	cam.open(gstreamPipeline);
	
	if (!cam.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}
	return 0;
}

void SetTarget(int tx, int ty){
    target.x = tx;
    target.y = ty;
}

int GetKeyFromKeyboard(){
	int key = waitKey(50);
	//cout << "Key: " << key << endl;
	switch(key){
		case 255:
			return 0;
		case 27: // esc
			return -1;
		break;
		case 119: // w
			target.y-=1;
			if(target.y < 0)
				target.y = 0;
		break;
		case 115: // s
			target.y+=1;
			if(target.y > 480)
				target.y = 480;
		break;
		case 100: // d
			target.x+=1;
			if(target.x > 640)
				target.x = 640;
		break;
		case 97: // a
			target.x-=1;
			if(target.x < 0)
				target.x = 0;
		break;
		case 10: // Intro
			if(!targetSet){
				targetSet = true;
				cout << "\n\n\nTarget set. Control loop started.\n\n\n" << endl;
				frameCount = 0;
				avgIllumBefore = avgIllum;
				avgRateOfChangeBefore = avgRateOfChange;
			}
		break;
	}
	//cout << "Target: " << target.x << "," << target.y << endl;
	return 0;
}

void GetTargetFromMouse(int event, int x, int y, int, void*){
	if (event != EVENT_LBUTTONDOWN)
		return;
	target.x = x;
	target.y = y;
	targetSet = true;
	cout << "Target: " << target.x << "," << target.y << endl;

	setMouseCallback(winName, NULL, NULL);
}

Point GetCentroid(Mat& src){
	Moments m = moments((src>=thresh), true);
	Point res(m.m10/m.m00, m.m01/m.m00);
	return res;
}

void GetShapeInfo(Mat& src, Point& centroid, double& area){
	Moments m = moments((src>=thresh), true);
	Point res(m.m10/m.m00, m.m01/m.m00);
	centroid = res;
	area = m.m00;
}

void CalculateErrors(Point centroid, int& xErr, int& yErr, double& area){
	int dx = xPixToSteps * (target.x - centroid.x);
    int dy = yPixToSteps * (target.y - centroid.y);
	
	//cout << "Errors: dx, dy = " << dx << "," << dy << endl;
	
    /*xErr = Kp * (dx * cosCorrAngle + dy * sinCorrAngle);
    yErr = Kp * (-dx * sinCorrAngle + dy * cosCorrAngle);*/

	
    xErr = dx;// * min(area / pinholeArea, 1.0);
    yErr = dy;// * min(area / pinholeArea, 1.0);
	
	
	double dxSgn = (dx >= 0) ? 1.0: -1.0;
	double dySgn = (dy >= 0) ? 1.0: -1.0;

	if(abs(dx) <= 10)
		xErr = kl1 * dx;
	else if(abs(dx) <= 20)
		xErr = kl2 * dx + dxSgn * n2;
	else if(abs(dx) <= 30)
		xErr = kl3 * dx + dxSgn * n3;
	else if(abs(dx) <= 40)
		xErr = kl4 * dx + dxSgn * n4;

	if(abs(dy) <= 10)
		yErr = kl1 * dy;
	else if(abs(dy) <= 20)
		yErr = kl2 * dy + dySgn * n2;
	else if(abs(dy) <= 30)
		yErr = kl3 * dy + dySgn * n3;
	else if(abs(dy) <= 40)
		yErr = kl4 * dy + dySgn * n4;

	/*if(abs(dx) < 50){
		if(abs(dx) <= 20){
			xErr = kl * dx;
			//xErr = dxSgn * ksq2 * pow(dx, 2) - k2 * dx + dxSgn * n2;
		}
		else{
			xErr = dxSgn * ksq * pow(dx, 2) - k * dx + dxSgn * n;
		}
	} 
	if(abs(dy) < 50){
		if(abs(dy) <= 20){
			yErr = kl * dy;
			//yErr = dySgn * ksq2 * pow(dy, 2) - k2 * dy + dySgn * n2;
		}
		else{
			yErr = dySgn * ksq * pow(dy, 2) - k * dy + dySgn * n;
		}
	}*/
	/*
	cout << "Area: area = " << area << "; area/pinArea = " << min(area / pinholeArea, 1.0) << endl;
    cout << "Errors: dx   = " << dx <<"; dy   = " << dy << endl;	 
    cout << "Errors: xErr = " << xErr << "; yErr = " << yErr << endl;
	*/
}

int CaptureAndProcess(VideoCapture& cam, int * eX, int * eY, mutex * mtx, const int _exposure){
	exposure = _exposure;


	namedWindow(winName,CV_WINDOW_AUTOSIZE); 
	namedWindow("Pinhole",CV_WINDOW_AUTOSIZE);
	moveWindow(winName, 400 , 50);
	moveWindow("Pinhole", 500 , 50);

	Mat frame;

	if (!cam.isOpened()){
		cout << "Cam is not opened" << endl;
		return -1;
	}
	//cout << "Starting capture process" << endl;
	frameCount = 0;
	int processedFrameCount = 0;

	int xErr = 0;
	int yErr = 0;

	Point centroid;
	double area;
	
	Point cent;
	Point _cent;
	double dr = 0.0;

	auto _t = get_time::now();
	auto t = get_time::now();
	auto dt = t - _t;

	auto _tt = get_time::now();
	auto tt = get_time::now();
	auto dtt = tt - _tt;

	auto startTime = get_time::now();
	auto currentTime = startTime;
	auto elapsedTime = currentTime - startTime;
	
	cout << "\nStarting test.\n\n   simulated exposure = " << exposure << "\n   r0 = 40cm" << "\n   driver speed = 100" << "\n   test time = " << testTime << "s\n" <<  endl;
	
	while (1){
		_tt = tt;
		cam >> frame;

		tt = get_time::now();
		dtt = tt - _tt;

		//Simulate framerate of camera, waiting until the exposure time has passed.
	/*
		t = get_time::now();
		while(chrono::duration_cast<ms>(dt).count() < exposure){
			t = get_time::now();
			dt = t - _t;
		}
	*/
		//Apply region of interest
		frame = frame(roi);
		frameCount++;

		_cent = cent;
		cent = GetCentroid(frame);
		if(frameCount > 1){
			dr = xPixToSteps * sqrt(pow((cent.x - _cent.x),2) + pow((cent.y - _cent.y),2));			
			double drdt = 1000 * dr / ((double)chrono::duration_cast<ms>(dtt).count());
			//cout << "dr = " << dr << "; dtt = " << ((double)chrono::duration_cast<ms>(dtt).count()) << "; drdt = " << drdt <<  endl;
			if(cent.x == 0 && cent.y == 0)
				drdt = avgRateOfChange;

			avgRateOfChange = ((avgRateOfChange * (double)(frameCount - 2)) + drdt) / ((double)(frameCount - 1));
			//cout << "Avg Rate of change is " << avgRateOfChange << " [steps/s]" << endl;	
		}
		
		//Separate frame in two, after pinhole and before pinhole.
		Mat mask(Mat::zeros(frame.rows, frame.cols, CV_8UC1));
		circle(mask, target, pinholeRadius, Scalar(256,256,256), -1);
		//pinhole is the image seen after the pinhole
		Mat pinhole(Mat::zeros(frame.rows, frame.cols, CV_8UC1));
		bitwise_and(frame, mask, pinhole);

		//get the mean illumination into the pinhole
		auto illum(mean(frame, mask));
		//get the average illumination across the elapsed time.
		avgIllum = ((avgIllum * (double)(frameCount - 1)) + ((double)illum[0] / 256)) / (double)frameCount;
		//cout << "Illumination: " << ((double)illum[0] / 256) << ". Avg: " << avgIllum << endl;	

		//draw the pinhole into the frame
		circle(frame, target, pinholeRadius, Scalar(0,0,0), -1);


		GetShapeInfo(frame, centroid, area);

		CalculateErrors(centroid, xErr, yErr, area);

		//simulate exposure by only updating the errors to the TipTilt device with period = exposure
		t = get_time::now(); 
		dt = t - _t;
		if(targetSet && 
		  (centroid.x != 0 && centroid.y != 0) &&
		  (chrono::duration_cast<ms>(dt).count() >= exposure)){
			//cout << "Target: " << target.x << "," << target.y << endl;
			//cout << "Centroid: " << centroid.x << "," << centroid.y << endl;
			mtx->lock();
			//cout << "Outdated errors - eX = " << *eX << ", eY = " << *eY << endl;
			*eX = xErr;
			*eY = yErr;
			//cout << "Updated errors - eX = " << *eX << ", eY = " << *eY << endl;
			mtx->unlock();
			//cout << "Time between updates = " << chrono::duration_cast<ms>(dt).count() << endl;
			processedFrameCount++;
			_t = t;
		}

		circle(frame, centroid, 5, Scalar(128,0,0));
		cvtColor(frame, frame, CV_GRAY2BGR);
		circle(frame, Point(target.x,target.y), 3, Scalar(128,128,0));

		imshow(winName, frame);
		imshow("Pinhole", pinhole);

		if (GetKeyFromKeyboard() == -1){ 
			//cout << "esc key is pressed by user" << endl;
			break; 
		}
		this_thread::sleep_for(chrono::microseconds(10));

		currentTime = get_time::now();
		elapsedTime = currentTime - startTime;
		if(chrono::duration_cast<chrono::seconds>(elapsedTime).count() >= testTime)
			break;
		else if((chrono::duration_cast<chrono::seconds>(elapsedTime).count() >= testTime/2) && !targetSet){
			targetSet = true;
			cout << "\nTarget set. Control loop started.\n" << endl;
			frameCount = 0;
			avgIllumBefore = avgIllum;
			avgRateOfChangeBefore = avgRateOfChange;
		}

	}

	cout << "\nTest finished\n\n   Average rate of change (no control): " << avgRateOfChangeBefore << " [steps/s]" << endl; 
	cout << "   Average Illumination with no control: " << (100.0 * avgIllumBefore) << "\%" << endl;
	cout << "   Average Illumination with active control: " << (100.0 * avgIllum) << "\%\n" << endl;
	//cout << "CaptureAndProcess returned" << endl;
    //cout << "Updated Errors " << processedFrameCount << " times." << endl;
	//TT.stop();
    return 0;
}

int Calibrate(VideoCapture& cam, TipTilt& TT){
	if (!cam.isOpened()){
        cout << "Cam is not opened. Can't calibrate." << endl;
        return -1;
    }
	if(!TT.isOpened()){
		cout << "TT is not opened. Can't calibrate." << endl;
		return -2;
	}
	namedWindow("Calibration",CV_WINDOW_AUTOSIZE);

	Mat K,N,S,E,W;
	Point cK, cN, cS, cE, cW;

    TT.goTo('K');
	cam >> K;

	TT.goTo('N');
	cam >> N;
	int NSSteps = TT.goTo('S');
	cam >> S;

    TT.goTo('K');

    TT.goTo('E');
	cam >> E;
    int EWSteps = TT.goTo('W');
	cam >> W;

	TT.goTo('K');

	cK = GetCentroid(K);
	cN = GetCentroid(N);
	cS = GetCentroid(S);
	cE = GetCentroid(E);
	cW = GetCentroid(W);

	cout << "Centroids: " << cK.x << "," << cK.y << ";" << cN.x << "," << cN.y << ";" 
							<< cS.x << "," << cS.y << ";" << cE.x << "," << cE.y << ";" 
							<< cW.x << "," << cW.y << endl;

	cout << "Steps: " << NSSteps << "," << EWSteps << endl;

	double NSDist = sqrt(pow(cN.x - cS.x, 2) + pow(cN.y - cS.y, 2));
	double EWDist = sqrt(pow(cE.x - cW.x, 2) + pow(cE.y - cW.y, 2));

	cout << "Dists: " << NSDist << "," << EWDist << endl;

	xPixToSteps = ((double)NSSteps) / NSDist;
	yPixToSteps = ((double)EWSteps) / EWDist;

	cout << "Factors: " << xPixToSteps << "," << yPixToSteps << endl;

	double tan1 = ((double)(cW.y - cE.y))/((double)(cE.x - cW.x));
	double tan2 = ((double)(cN.x - cS.x))/((double)(cN.y - cS.y));

	cout << "Tans: " << tan1 << "," << tan2 << endl;

	double alpha = atan(tan1);
	double beta = atan(tan2);

	corrAngle = (alpha + beta) / 2.0;
	cosCorrAngle = cos(corrAngle);
	sinCorrAngle = sin(corrAngle);

	cout << "Angles: " << alpha << "," << beta << ";" << corrAngle << endl;

	Mat complete = (K > 150) + (N > 150) + (S > 150) + (E > 150) + (W > 150);

	roi = boundingRect(complete);
	cout << "ROI: " << roi << endl;

	target.x = cK.x - roi.x;
	target.y = cK.y - roi.y;

	cvtColor(complete, complete, CV_GRAY2BGR);

	rectangle(complete, roi, Scalar(0,128,0));
	circle(complete, cK, 5, Scalar(0,0,0));
	circle(complete, cN, 5, Scalar(0,128,0));
	circle(complete, cS, 5, Scalar(0,0,128));
	circle(complete, cE, 5, Scalar(128,0,0));
	circle(complete, cW, 5, Scalar(128,128,128));
	imshow("Calibration", complete);


	waitKey(0);

	destroyWindow("Calibration");

    return 0;
}
