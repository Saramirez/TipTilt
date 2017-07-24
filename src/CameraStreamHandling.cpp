#include "../include/CameraStreamHandling.hpp"
#include <chrono>

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

Point target(64, 64);
double xPixToSteps = 0.42;
double yPixToSteps = 0.43;
const string winName = "Star";
bool targetSet = false;

double corrAngle = 0.023;
double cosCorrAngle = 1;
double sinCorrAngle = 0.023;

int frameCount = 0;
double avgRateOfChange = 0.0;
double avgIllum = 0.0;
const int exposure = 1000; //ms

Rect roi(266, 192, 128, 128);

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
			target.y-=5;
			if(target.y < 0)
				target.y = 0;
		break;
		case 115: // s
			target.y+=5;
			if(target.y > 480)
				target.y = 480;
		break;
		case 100: // d
			target.x+=5;
			if(target.x > 640)
				target.x = 640;
		break;
		case 97: // a
			target.x-=5;
			if(target.x < 0)
				target.x = 0;
		break;
		case 10: // Intro
			if(!targetSet){
				targetSet = true;
				cout << "\n\n\nTarget set. Control loop started.\n\n\n" << endl;
				frameCount = 0;
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
	cout << "Targets: " << target.x << "," << target.y << endl;

	setMouseCallback(winName, NULL, NULL);
}

Point GetCentroid(Mat& src){
	Moments m = moments((src>=100), true);
	Point res(m.m10/m.m00, m.m01/m.m00);
	return res;
}

void CalculateErrors(Point centroid, int& xErr, int& yErr){
	int dx = xPixToSteps * (target.x - centroid.x);
    int dy = yPixToSteps * (target.y - centroid.y);
	
	//cout << "Errors: dx, dy = " << dx << "," << dy << endl;
	
    xErr = dx * cosCorrAngle + dy * sinCorrAngle;
    yErr = -dx * sinCorrAngle + dy * cosCorrAngle;

    //cout << "Errors: xErr, yErr = " << *xErr << "," << *yErr << endl;
}

int CaptureAndProcess(VideoCapture& cam, int * ex, int * ey, mutex * mtx){

	namedWindow(winName,CV_WINDOW_AUTOSIZE); 
	namedWindow("Pinhole",CV_WINDOW_AUTOSIZE);
	moveWindow("Pinhole", 200 , 50);

	Mat frame;

	if (!cam.isOpened()){
		cout << "Cam is not opened" << endl;
		return -1;
	}
	cout << "Starting capture process" << endl;
	frameCount = 0;

	int xErr = 0;
	int yErr = 0;
	int _xErr = 0;
	int _yErr = 0;
	double dr = 0.0;

	auto _t = get_time::now();
	auto t = get_time::now();
	auto dt = t - _t;
	//setMouseCallback(winName, GetTargetFromMouse, NULL);

	while (1){
		cam >> frame;
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

		//Separate frame in two, after pinhole and before pinhole.
		Mat mask(Mat::zeros(frame.rows, frame.cols, CV_8UC1));
		circle(mask, target, 12.5, Scalar(256,256,256), -1);
		//pinhole is the image seen after the pinhole
		Mat pinhole(Mat::zeros(frame.rows, frame.cols, CV_8UC1));
		bitwise_and(frame, mask, pinhole);

		//get the mean illumination into the pinhole
		auto illum(mean(frame, mask));
		//get the average illumination across the elapsed time.
		avgIllum = ((avgIllum * (double)(frameCount - 1)) + ((double)illum[0] / 256)) / (double)frameCount;
		//cout << "Illumination: " << ((double)illum[0] / 256) << ". Avg: " << avgIllum << endl;	

		//draw the pinhole into the frame
		circle(frame, target, 12.5, Scalar(0,0,0), -1);

		Point centroid = GetCentroid(frame);

		//cout << "Centroid: " << centroid.x << "," << centroid.y << endl;	

		CalculateErrors(centroid, xErr, yErr);
/*
		dr = sqrt(pow((xErr - _xErr),2) + pow((yErr - _yErr),2));

		_xErr = xErr;
		_yErr = yErr;	

		double drdt = 1000 * dr / ((double)chrono::duration_cast<ms>(dt).count());
		if(centroid.x == 0 && centroid.y == 0)
			drdt = avgRateOfChange;

		//cout << "dr: " << dr << ". dt: " << chrono::duration_cast<ms>(dt).count() << ". drdt: " <<  drdt << endl;
		avgRateOfChange = ((avgRateOfChange * (double)(frameCount - 1)) + drdt) / (double)frameCount;
		if(frameCount == 1){
			avgRateOfChange = 0.0;
		}*/

		//cout << "Avg Rate is " << avgRateOfChange << " [px/s]" << endl;	

		//simulate exposure by only updating the errors to the TipTilt device with period = exposure
		t = get_time::now(); 
		dt = t - _t;
		if(targetSet && 
		  (centroid.x != 0 && centroid.y != 0) &&
		  (chrono::duration_cast<ms>(dt).count() >= exposure)){
			mtx->lock();
			*ex = xErr;
			*ey = yErr;
			cout << "Updated errors - ex = " << *ex << ", ey = " << *ey << endl;
			mtx->unlock();
			cout << "Time between updates = " << chrono::duration_cast<ms>(dt).count() << endl;
			_t = t;
		}

		circle(frame, centroid, 5, Scalar(128,0,0));
		cvtColor(frame, frame, CV_GRAY2BGR);
		circle(frame, Point(target.x,target.y), 3, Scalar(128,128,0));

		imshow(winName, frame);
		imshow("Pinhole", pinhole);

		if (GetKeyFromKeyboard() == -1){ 
			cout << "esc key is pressed by user" << endl;
			break; 
		}
	}

	cout << "CaptureAndProcess returned" << endl;
    cout << "Updated Errors " << frameCount << " times." << endl;
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

	xPixToSteps = NSDist / ((double)NSSteps);
	yPixToSteps = EWDist / ((double)EWSteps);

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
