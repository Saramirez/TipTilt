#include "../include/CameraStreamHandler.hpp"
#include <chrono>

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

CameraStreamHandler::CameraStreamHandler(int* _eX, int* _eY, mutex * _mtx) :
					 roi(fullFramePinholePosition.x - 50, fullFramePinholePosition.y - 50, 100, 100), target(50,50){
	// Posicion del pinhole en frame completo es (607, 507)
    eX = _eX;
    eY = _eY;
    mtx = _mtx;
    oRoi = roi;
}

Point CameraStreamHandler::GetTarget() {
	return target;
}

void CameraStreamHandler::SetPixToStepsFactors(double xp2s, double yp2s) {
	xPixToSteps = xp2s;
	yPixToSteps = yp2s;
}

void CameraStreamHandler::SetAngles(double cos, double sin) {
	cosCorrAngle = cos;
	sinCorrAngle = sin;
}

void CameraStreamHandler::SetRoi(Rect _roi) {
	roi = _roi;
	oRoi = roi;
}

void CameraStreamHandler::SetDevice(const char * _device) {
	device = _device;
}

int CameraStreamHandler::OpenCamera(){
    cam.open(device);

    if(!cam.isOpened()){
        return -1;
        cout << "Cam is not opened" << endl;
    }
    return 0;
}

int CameraStreamHandler::CloseCamera() {
	cam.release();

	if (cam.isOpened()) {
		return -1;
		cout << "Cam is not closed" << endl;
	}
	return 0;
}


Point CameraStreamHandler::GetCentroid(Mat& src) {
	Mat aux;
	threshold(src, aux, thresh, 255, THRESH_TOZERO);
	Moments m2 = moments(aux);
	Point res2(m2.m10 / m2.m00, m2.m01 / m2.m00);
	return res2;
}

void CameraStreamHandler::GetShapeInfo(Point& centroid, double& dist, double dir[2], double& width){
    Mat bw;
    threshold(frame, bw, thresh, 255, THRESH_BINARY);
    
	//Moments m = moments(bw, true);
	//Point res(m.m10/m.m00, m.m01/m.m00);

    Mat aux;
    threshold(frame, aux, thresh, 255, THRESH_TOZERO);
    Moments m2 = moments(aux);
	Point res2(m2.m10/m2.m00, m2.m01/m2.m00);
    centroid = res2;

	dist = sqrt(pow(target.x - centroid.x, 2) + pow(target.y - centroid.y, 2));
    if(centroid.x == 0 && centroid.y == 0){
        dist = -1;
        return;
    }

    dir[0] = (target.x - centroid.x) / dist;
    dir[1] = (centroid.y - target.y) / dist;

    if(dist > (starRadius + pinholeRadius))
        return;
    
    double intensity = 1;
    int flag = 0;	
    width = -0.1;
    while ((intensity != 0 || flag != 1) && width < 2*starRadius){
        width+=0.1;
        Point pixel(target.x - (pinholeRadius + width)*dir[0],
                    target.y + (pinholeRadius + width)*dir[1]);
        intensity = bw.at<uchar>(pixel);

        if (intensity == 255)
            flag = 1;
    }
    if(flag == 0)
        width = 0;
}
void CameraStreamHandler::GetSimpleShapeInfo(Point& centroid, double& area){
    Mat bw;
    threshold(frame, bw, thresh, 255, THRESH_BINARY);
    Moments m = moments(bw, true);
    Point res(m.m10/m.m00, m.m01/m.m00);
    centroid = res;
    area = m.m00;
}

Mat CameraStreamHandler::GetStarParams() {
	cout << "Getting star params" << endl;

	if (!cam.isOpened()) {
		cout << "Cam is not opened" << endl;
		return Mat();
	}

	cam >> frame;

    double starArea;
	GetSimpleShapeInfo(centroid, starArea);
	starRadius = sqrt(starArea / M_PI);

	cout << "Star area = " << starArea << "; Star radius = " << starRadius << endl;

	cvtColor(frame, frame, CV_GRAY2BGR);
	circle(frame, centroid, starRadius, Scalar(0, 128, 0));

	return frame;
}

void CameraStreamHandler::CalculateErrors(int& xErr, int& yErr, double& dist, double dir[2], double& width){
	if(dist == -1){
		xErr = 0;
		yErr = 0;
		//cout << "No star" << endl;
		return;
	}
	double xx = cosCorrAngle * dir[0] + sinCorrAngle * dir[1];
	double yy = -1 * sinCorrAngle * dir[0] + cosCorrAngle * dir[1];
	//double xx = xPixToSteps * dir[0];
	//double yy = yPixToSteps * dir[1];

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
	xErr = (int)(xx * xPixToSteps);
	yErr = (int)(yy * yPixToSteps);
	//cout << "width = " << width << " area = " << area << "; area/starArea = " << area / starArea << endl;
    //cout << "xErr = " << xErr << "; yErr = " << yErr << endl;
}

Mat CameraStreamHandler::CaptureAndProcess(bool returnThresh, bool simulate){
    cam >> frame;

    if(simulate){
	    auto t = get_time::now();
        auto cTime = chrono::duration_cast<ms>(t.time_since_epoch()).count() / 1000.0;
		double dx = 2.2 * R * sin(2 * w * cTime) *  cos(2 * w * cTime) + R * cos(4 * w * cTime) + 0.5 * R * cos(10 * w * cTime);
		double dy = 2.2 * R * cos(2 * w * cTime) * sin(w/1.5 * cTime) + R * sin(3 * w * cTime) + 0.4 * R * sin(15 * w * cTime);
		roi.x = oRoi.x + dx;
		roi.y = oRoi.y + dy;
    }

    frame = frame(roi);

	if (simulate) {
		//draw the pinhole into the frame
		circle(frame, target, pinholeRadius, Scalar(0, 0, 0), -1);
	}

    GetShapeInfo(centroid, dist, dir, width);

	_xErr = xErr;
	_yErr = yErr;

	CalculateErrors(xErr, yErr, dist, dir, width);

	mtx->lock();
	*eX = xErr;
	*eY = yErr;
	//*eX = 0.5 * xErr + 0.5 * _xErr;
	//*eY = 0.5 * yErr + 0.5 * _yErr;
	mtx->unlock();

	if (returnThresh) {
		threshold(frame, frame, thresh, 255, THRESH_BINARY);
	}

	cvtColor(frame, frame, CV_GRAY2RGB);
    if(dist != -1)
        circle(frame, centroid, 2, Scalar(128,0,0));
    circle(frame, Point(target.x,target.y), 3, Scalar(0,128,128));

    return frame;
}

Mat CameraStreamHandler::GrabOneFrame(bool full, bool pinholePos){
    cam >> frame;
	if(!full)
		frame = frame(roi);
	else
		if (pinholePos) {
			cvtColor(frame, frame, CV_GRAY2RGB);
			//circle(frame, fullFramePinholePosition, pinholeRadius, Scalar(0, 128, 0), -1);
			line(frame, Point(fullFramePinholePosition.x, fullFramePinholePosition.y - pinholeRadius - 6),
						Point(fullFramePinholePosition.x, fullFramePinholePosition.y - pinholeRadius), Scalar(0, 128, 0), 2);
			line(frame, Point(fullFramePinholePosition.x, fullFramePinholePosition.y + pinholeRadius),
						Point(fullFramePinholePosition.x, fullFramePinholePosition.y + pinholeRadius + 6), Scalar(0, 128, 0), 2);		
			line(frame, Point(fullFramePinholePosition.x - pinholeRadius - 6, fullFramePinholePosition.y),
						Point(fullFramePinholePosition.x - pinholeRadius, fullFramePinholePosition.y), Scalar(0, 128, 0), 2);		
			line(frame, Point(fullFramePinholePosition.x + pinholeRadius, fullFramePinholePosition.y),
						Point(fullFramePinholePosition.x + pinholeRadius + 6, fullFramePinholePosition.y), Scalar(0, 128, 0), 2);
		}
		
    return frame;
}

bool CameraStreamHandler::IsCameraOpen() {
	return cam.isOpened();
}
