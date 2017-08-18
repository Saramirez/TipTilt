#include "../include/CameraStreamHandling.hpp"
#include <chrono>

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

const string winName = "Star";
bool targetSet = false;
const int thresh = 100;
Rect oRoi(270, 190, 100, 100);
Rect roi(270, 190, 100, 100);

Point oTarget(50, 50);
Point target(50, 50);
double xPixToSteps = 2.4;
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

const double pinholeRadius = 6; //13*4.8*2 um = 124.8 um 
const double pinholeArea = M_PI*pinholeRadius*pinholeRadius;
double starRadius = 6.58;
double starArea = M_PI*starRadius*starRadius;

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
			/*if(!targetSet){
				targetSet = true;
				cout << "\n\n\nTarget set. Control loop started.\n\n\n" << endl;
				frameCount = 0;
				avgIllumBefore = avgIllum;
				avgRateOfChangeBefore = avgRateOfChange;
			}*/
			targetSet = !targetSet;
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
	Mat bw;
	threshold(src, bw, thresh, 255, THRESH_BINARY);
	Moments m = moments(bw, true);
	Point res(m.m10/m.m00, m.m01/m.m00);
	centroid = res;
	area = m.m00;
	/*
	Mat aux;
	threshold(src, aux, thresh, 255, THRESH_TOZERO);
	Moments m2 = moments(aux);
	Point res2(m2.m10/m2.m00, m2.m01/m2.m00);
	cout << "Centroid " << res.x << "," << res.y << endl;
	cout << "Weighted centroid " << res2.x << "," << res2.y << endl;
	circle(src, res2, 3, Scalar(128,128,128));
	*/
}
void GetShapeInfo(Mat& src, Point& centroid, double& dist, double dir[2], double& area, double& width){
	Mat bw;
	threshold(src, bw, thresh, 255, THRESH_BINARY);
	Moments m = moments(bw, true);
	Point res(m.m10/m.m00, m.m01/m.m00);
	//centroid = res;
	area = m.m00;
	
	Mat aux;
	threshold(src, aux, thresh, 255, THRESH_TOZERO);
	Moments m2 = moments(aux);
	Point res2(m2.m10/m2.m00, m2.m01/m2.m00);
	centroid = res2;
	/*cout << "Centroid " << res.x << "," << res.y << endl;
	cout << "Weighted centroid " << res2.x << "," << res2.y << endl;
	circle(src, res2, 3, Scalar(128,128,128));
	*/

	dist = sqrt(pow(target.x - centroid.x, 2) + pow(target.y - centroid.y, 2));
	if(centroid.x == 0 && centroid.y == 0){
		dist = -1;
		return;
	}

	dir[0] = (target.x - centroid.x) / dist;
	dir[1] = (centroid.y - target.y) / dist;

	if(dist > (starRadius + pinholeRadius))
		return;

	//cout << "dir = " << dir << "; target = " << target << "; centroid = " << centroid << endl;
	
	double intensity = 1;
	int flag = 0;	
	width = -0.1;
	while ((intensity != 0 || flag != 1) && width < 2*starRadius){
		width+=0.1;
		Point pixel(target.x - (pinholeRadius + width)*dir[0],
					target.y + (pinholeRadius + width)*dir[1]);
		intensity = bw.at<uchar>(pixel);
		//cout << "dir = " << dir << "; target = " << target << "; centroid = " << centroid << endl;
		//cout << "pixel = " << pixel << "; intensity = " << intensity << "; width = " << width << endl;
		if (intensity == 255)
			flag = 1;
	}
	if(flag == 0)
		width = 0;

	//cout << "Width = " << width << endl;

}

int GetStarParams(VideoCapture& cam) {
	cout << "Getting star params" << endl;
	Mat frame;
	namedWindow("Star",CV_WINDOW_AUTOSIZE); 

	if (!cam.isOpened()) {
		cout << "Cam is not opened" << endl;
		return -1;
	}

	Point centroid;
	cam >> frame;
	GetShapeInfo(frame, centroid, starArea);
	starRadius = sqrt(starArea / M_PI);

	cout << "Star area = " << starArea << "; Star radius = " << starRadius << endl;

	cvtColor(frame, frame, CV_GRAY2BGR);
	circle(frame, centroid, starRadius, Scalar(0, 128, 0));
	imshow(winName, frame);

	waitKey(0);

	destroyWindow("Star");
}

void CalculateErrors(int& xErr, int& yErr, double& dist, double dir[2], double& area, double& width){
	if(dist == -1){
		xErr = 0;
		yErr = 0;
		//cout << "No star" << endl;
		return;
	}
	//cout << "dist = " << dist << "; dir = " << dir[0] << ", " << dir[1] << endl;
	
	double xx = xPixToSteps * dir[0];
	double yy = yPixToSteps * dir[1];

	if(dist <= (pinholeRadius + starRadius)){
		//cout << "pinhole+star radius = " << (pinholeRadius + starRadius) << endl;
		//cout << "With width = " << width << endl;
		xx *= width;
		yy *= width;
		//xx *= (dist * area / starArea);
		//yy *= (dist * area / starArea); 
	}
	else{
		//cout << "With distance * factor" << endl;
		xx *= dist;
		yy *= dist;
	}
	xErr = (int)xx;
	yErr = (int)yy;
	//cout << "width = " << width << " area = " << area << "; area/starArea = " << area / starArea << endl;
    //cout << "xErr = " << xErr << "; yErr = " << yErr << endl;
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
	int _xErr = 0;
	int _yErr = 0;

	Point centroid;
	double dist;
	double dir[2];
	double area;
	double width;
	/*
	Point cent;
	Point _cent;
	double dr = 0.0;*/

	double w = 2 * M_PI * 0.04;
	double R = 4;

	auto _t = get_time::now();
	auto t = get_time::now();
	auto dt = t - _t;

	auto _tt = get_time::now();
	auto tt = get_time::now();
	auto dtt = tt - _tt;

	auto startTime = get_time::now();
	auto currentTime = startTime;
	auto elapsedTime = currentTime - startTime;
	
	cout << "\nStarting test.\n\n   exposure = 0.1s \n   r0 > 20cm" << "\n   test time = " << testTime << "s\n" <<  endl;
	
	while (1){
		//_tt = tt;
		cam >> frame;

		auto cTime = chrono::duration_cast<ms>(elapsedTime).count() / 1000.0;
		double dx = 2.2 * R * sin(2 * w * cTime) *  cos(2 * w * cTime) + R * cos(4 * w * cTime) + 0.5 * R * cos(10 * w * cTime);
		double dy = 2.2 * R * cos(2 * w * cTime) * sin(w/1.5 * cTime) + R * sin(3 * w * cTime) + 0.4 * R * sin(15 * w * cTime);
		roi.x = oRoi.x + dx;
		roi.y = oRoi.y + dy;
	
		/*
			tt = get_time::now();
			dtt = tt - _tt;
		*/

		//Apply region of interest
		frame = frame(roi);
		frameCount++;

		/*
			_cent = cent;
			cent = GetCentroid(frame);
			
			if(frameCount > 1){ //compute rate of change
				dr = xPixToSteps * sqrt(pow((cent.x - _cent.x),2) + pow((cent.y - _cent.y),2));			
				double drdt = 1000 * dr / ((double)chrono::duration_cast<ms>(dtt).count());
				//cout << "dr = " << dr << "; dtt = " << ((double)chrono::duration_cast<ms>(dtt).count()) << "; drdt = " << drdt <<  endl;
				if(cent.x == 0 && cent.y == 0)
					drdt = avgRateOfChange;

				avgRateOfChange = ((avgRateOfChange * (double)(frameCount - 2)) + drdt) / ((double)(frameCount - 1));
				//cout << "Avg Rate of change is " << avgRateOfChange << " [steps/s]" << endl;	
			}
		*/

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

		GetShapeInfo(frame, centroid, dist, dir, area, width);


		//simulate exposure by only updating the errors to the TipTilt device with period = exposure
		t = get_time::now(); 
		dt = t - _t;
		if(targetSet && (chrono::duration_cast<ms>(dt).count() >= exposure)){
			//targetSet = false;
			_xErr = xErr;
			_yErr = yErr;

			CalculateErrors(xErr, yErr, dist, dir, area, width);
			//cout << "Target: " << target.x << "," << target.y << endl;
			//cout << "Centroid: " << centroid.x << "," << centroid.y << endl;
			mtx->lock();
			//cout << "Outdated errors - eX = " << *eX << ", eY = " << *eY << endl;
			*eX = xErr;
			*eY = yErr;
			//*eX = 0.5 * xErr + 0.5 * _xErr;
			//*eY = 0.5 * yErr + 0.5 * _yErr;
			//cout << "Updated errors - eX = " << *eX << ", eY = " << *eY << endl;
			mtx->unlock();
			//cout << "Time between updates = " << chrono::duration_cast<ms>(dt).count() << endl;
			processedFrameCount++;
			_t = t;
		}

		circle(frame, centroid, 2, Scalar(128,0,0));
		cvtColor(frame, frame, CV_GRAY2BGR);
		circle(frame, Point(target.x,target.y), 2, Scalar(128,128,0));

		imshow(winName, frame);
		imshow("Pinhole", pinhole);

		if (GetKeyFromKeyboard() == -1){ 
			//cout << "esc key is pressed by user" << endl;
			break; 
		}
		this_thread::sleep_for(chrono::microseconds(100));
		
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
	
	cout << "\nTest finished\n\n" << endl; //  Average rate of change (no control): " << avgRateOfChangeBefore << " [steps/s]" << endl; 
	cout << "   Average Illumination with no control: " << (100.0 * avgIllumBefore) << "\%" << endl;
	cout << "   Average Illumination with active control: " << (100.0 * avgIllum) << "\%\n" << endl;
	//cout << "CaptureAndProcess returned" << endl;
	//cout << "Updated Errors " << processedFrameCount << " times." << endl;


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

int CalibrateErrorCalculation(VideoCapture& cam, TipTilt& TT){
	if (!cam.isOpened()){
        cout << "Cam is not opened. Can't calibrate." << endl;
        return -1;
    }
	if(!TT.isOpened()){
		cout << "TT is not opened. Can't calibrate." << endl;
		return -2;
	}

	namedWindow("Calibration",CV_WINDOW_AUTOSIZE);

	Mat frame;
	int ex = 10;
	int ey = 10;
	Point centroid;

	double area;


	cam >> frame;
	frame = frame(roi);

	GetShapeInfo(frame, centroid, area);

	double starSize = 2*4.8 * sqrt(area / M_PI);
	double starToPin = area / pinholeArea;
	starToPin = roundf(starToPin * 100) / 100;

    //TT.goTo('K');
	//this_thread::sleep_for(chrono::seconds(4));

	
	int steps = 0;
	int run = 0;
	int _run = 0;

	int res [51][4];

	cout << "Centering" << endl;
	while(_run < 4){
		cam >> frame;
		frame = frame(roi);

		if(run == 0){ //center
			centroid = GetCentroid(frame);
			ex = target.x - centroid.x;
			ey = centroid.y - target.y;
			if(ex > 0)
				TT.move('e');
			else if(ex < 0)
				TT.move('w');
			if(ey > 0)
				TT.move('n');
			else if(ey < 0)
				TT.move('s');
			//cout << "ex " << ex << " ey " << ey << endl;

			if(ex == 0 && ey == 0){
				switch(_run){
					case 0:
						run = 1;
						_run = 0;
						cout << "\nCentered. Going right." << endl;
						steps = 0;
					break;
					case 1:
						run = 2;
						_run = 0;
						cout << "\nCentered. Going up." << endl;
						steps = 0;
					break;
					case 2:
						run = 3;
						_run = 0;
						cout << "\nCentered. Going left." << endl;
						steps = 0;
					break;
					case 3:
						run = 4;
						_run = 0;
						cout << "\nCentered. Going down." << endl;
						steps = 0;
					break;
				}
			}
		}
		else{
			circle(frame, target, pinholeRadius, Scalar(0,0,0), -1);
			centroid = GetCentroid(frame);
			switch(run){
				case 1:
					ex = target.x - centroid.x;
					res[steps][0] = ex;
					TT.move('e');
				break;
				case 2:
					ey = centroid.y - target.y;
					res[steps][1] = ey;
					TT.move('s');
				break;
				case 3:
					ex = target.x - centroid.x;
					res[steps][2] = ex;
					TT.move('w');
				break;
				case 4:
					ey = centroid.y - target.y;
					res[steps][3] = ey;
					TT.move('n');
				break;
			}
			steps++;
			
			if(steps > 50){
				_run = run;
				run = 0;
				cout << "\nFinished." << endl;
			}
		}
		circle(frame, centroid, 5, Scalar(128,0,0));	
		cvtColor(frame, frame, CV_GRAY2BGR);
		circle(frame, Point(target.x,target.y), 3, Scalar(128,128,0));

		imshow("Calibration", frame);
		int key = waitKey(100);
	}
	ofstream file;
	file.open("Calibration_" + to_string(starToPin) + ".txt");//, ios::out | ios::app);
	file << "Pinhole, Star, Star/Pinhole\n";
	file << (2*4.8*pinholeRadius) << "," << starSize << "," << starToPin << "\n";
	file << "Steps, ex (e), ex (w), ey (n), ey (s)\n";

	for(int i = 0; i < 51; i++){
		file << i << ",";
		file << res[i][0] << ",";
		file << res[i][1] << ",";
		file << res[i][2] << ",";
		file << res[i][3] << "\n";
	}

	file.close();

	destroyWindow("Calibration");

    return 0;
}
