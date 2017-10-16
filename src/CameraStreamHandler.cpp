#include "../include/CameraStreamHandler.hpp"
#include <chrono>

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

CameraStreamHandler::CameraStreamHandler(int* _eX, int* _eY, mutex * _mtx) :
					 roi(fullFramePinholePosition.x - roiSize / 2, fullFramePinholePosition.y - roiSize / 2, roiSize, roiSize),
					 target(roiSize / 2, roiSize / 2){
	// Posicion del pinhole en frame completo es (616,584)
    eX = _eX;
    eY = _eY;
    mtx = _mtx;
    oRoi = roi;
	for (int i = 0; i < errorCountsToAvg; i++) {
		xErrors.push_back(0);
		yErrors.push_back(0);
	}
	for(int i = 0; i < FWHMCountsToAvg; i++)
		FWHMs.push_back(0);
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

bool CameraStreamHandler::IsCameraOpen() {
	return cam.isOpened();
}

Point CameraStreamHandler::GetCentroid(Mat& src) {
	Mat aux;
	threshold(src, aux, thresh, 255, THRESH_TOZERO);
	Moments m2 = moments(aux);
	Point res2(m2.m10 / m2.m00, m2.m01 / m2.m00);
	return res2;
}

void CameraStreamHandler::GetShapeInfo(Point& centroid, double& dist, double dir[2], double& width, int mode){
    Mat bw;
    threshold(frame, bw, thresh, 255, THRESH_BINARY);
    
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
	// dir es vector unitario que apunta desde el centroide hacia el pinhole
    dir[0] = (target.x - centroid.x) / dist;
    dir[1] = (target.y - centroid.y) / dist;

    if(dist > (starRadius + pinholeRadius))
        return;
    
    double intensity = 1;
    int flag = 0;	
    width = -0.1;

	double limit = 2 * pinholeRadius;
	if (mode == 1)
		limit = 2 * starRadius;

    while ((intensity != 0 || flag != 1) && width < limit){
        width+=0.1;
        Point pixel(target.x - (pinholeRadius + width)*dir[0],
                    target.y - (pinholeRadius + width)*dir[1]);
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
	cout << "Star centroid = " << centroid.x << ", " << centroid.y << endl;

	cvtColor(frame, frame, CV_GRAY2BGR);
	circle(frame, centroid, starRadius, Scalar(0, 128, 0), 2);

	return frame;
}

void CameraStreamHandler::CalculateErrors(int& xErr, int& yErr, double& dist, double dir[2], double& width, int mode){
	if(dist == -1){
		xErr = 0;
		yErr = 0;
		//cout << "No star" << endl;
		return;
	}
	//double xx = xPixToSteps * (cosCorrAngle * dir[0] + sinCorrAngle * dir[1]);
	//double yy = yPixToSteps * (-1 * sinCorrAngle * dir[0] + cosCorrAngle * dir[1]);

	//Asumiendo que está bien alineado. De todas maneras, es casi imposible tener una buena calibración oservando una estrella
	double xx = xPixToSteps * dir[0];
	double yy = yPixToSteps * dir[1];

	if(dist <= (pinholeRadius + starRadius)){ //Si la estrella está traslapada con el pinhole
		if (mode == 0) {
			xx *= width;
			yy *= width;
		}
		if (mode == 1) {
			xx *= (target.x + pinholeRadius + width - starRadius);
			yy *= (target.y + pinholeRadius + width - starRadius);
		}
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

Mat CameraStreamHandler::CaptureAndProcess(bool returnThresh, bool simulate, int filterErrors, int errorMode){
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

    GetShapeInfo(centroid, dist, dir, width, errorMode);

	CalculateErrors(xErr, yErr, dist, dir, width, errorMode);

	if (filterErrors == 1) {
		xErrors.push_back(xErr);
		yErrors.push_back(yErr);
		xErrors.erase(xErrors.begin());
		yErrors.erase(yErrors.begin());

		xErr = accumulate(xErrors.begin(), xErrors.end(), 0.0) / xErrors.size();
		yErr = accumulate(yErrors.begin(), yErrors.end(), 0.0) / yErrors.size();
	}

	else if (filterErrors == 2) {
		iXErr += xErr;
		iYErr += yErr;
		xErr = 0.9 * xErr + 0.1 *iXErr;
		yErr = 0.9 * yErr + 0.1 *iYErr;
	}

	mtx->lock();
	*eX = xErr;
	*eY = yErr;
	mtx->unlock();

	if (returnThresh) {
		threshold(frame, frame, thresh, 255, THRESH_BINARY);
	}

	cvtColor(frame, frame, CV_GRAY2RGB);

    if(dist != -1)
        circle(frame, centroid, 2, Scalar(128,0,0));

    circle(frame, Point(target.x,target.y), pinholeRadius, Scalar(0,128,0));

	resize(frame, frame, Size(), TTzoom, TTzoom);
    return frame;
}

Mat CameraStreamHandler::GrabOneFrame(bool full) {
	cam >> frame;
	if (!full) {
		frame = frame(roi);
	}
	return frame;
}

Mat CameraStreamHandler::GrabGuideFrame(int zoom){
    cam >> frame;

	cvtColor(frame, frame, CV_GRAY2RGB);
	line(frame, Point(fullFramePinholePosition.x, fullFramePinholePosition.y - pinholeRadius - 6),
				Point(fullFramePinholePosition.x, fullFramePinholePosition.y - pinholeRadius), Scalar(0, 128, 0), 2);
	line(frame, Point(fullFramePinholePosition.x, fullFramePinholePosition.y + pinholeRadius),
				Point(fullFramePinholePosition.x, fullFramePinholePosition.y + pinholeRadius + 6), Scalar(0, 128, 0), 2);		
	line(frame, Point(fullFramePinholePosition.x - pinholeRadius - 6, fullFramePinholePosition.y),
				Point(fullFramePinholePosition.x - pinholeRadius, fullFramePinholePosition.y), Scalar(0, 128, 0), 2);		
	line(frame, Point(fullFramePinholePosition.x + pinholeRadius, fullFramePinholePosition.y),
				Point(fullFramePinholePosition.x + pinholeRadius + 6, fullFramePinholePosition.y), Scalar(0, 128, 0), 2);
	
	if(zoom == 0)
		return frame;

	Mat zoomed;
	int oX = max(fullFramePinholePosition.x - guideRoiSize / (zoom * 2), 0);
	int oY = max(fullFramePinholePosition.y - guideRoiSize / (zoom * 2), 0);
	Rect newRoi(oX, oY, guideRoiSize / zoom, guideRoiSize / zoom);
	frame = frame(newRoi);
	resize(frame, zoomed, Size(), zoom, zoom);

	return zoomed;
}

Mat CameraStreamHandler::GrabGuideFrame(int zoom, Mat& plotFrame) {
	cam >> frame;
	MeasureFWMH(frame, plotFrame);

	cvtColor(frame, frame, CV_GRAY2RGB);
	line(frame, Point(fullFramePinholePosition.x, fullFramePinholePosition.y - pinholeRadius - 6),
		Point(fullFramePinholePosition.x, fullFramePinholePosition.y - pinholeRadius), Scalar(0, 128, 0), 2);
	line(frame, Point(fullFramePinholePosition.x, fullFramePinholePosition.y + pinholeRadius),
		Point(fullFramePinholePosition.x, fullFramePinholePosition.y + pinholeRadius + 6), Scalar(0, 128, 0), 2);
	line(frame, Point(fullFramePinholePosition.x - pinholeRadius - 6, fullFramePinholePosition.y),
		Point(fullFramePinholePosition.x - pinholeRadius, fullFramePinholePosition.y), Scalar(0, 128, 0), 2);
	line(frame, Point(fullFramePinholePosition.x + pinholeRadius, fullFramePinholePosition.y),
		Point(fullFramePinholePosition.x + pinholeRadius + 6, fullFramePinholePosition.y), Scalar(0, 128, 0), 2);

	if (zoom == 0)
		return frame;

	Mat zoomed;
	int oX = max(fullFramePinholePosition.x - guideRoiSize / (zoom * 2), 0);
	int oY = max(fullFramePinholePosition.y - guideRoiSize / (zoom * 2), 0);
	Rect newRoi(oX, oY, guideRoiSize / zoom, guideRoiSize / zoom);
	frame = frame(newRoi);
	resize(frame, zoomed, Size(), zoom, zoom);

	return zoomed;
}


void CameraStreamHandler::MeasureFWMH(Mat& frame, Mat& plot) {
	Point FWHMpoint = GetCentroid(frame);

	vector<Point> curvePoints;
	int maxIntensity = 0;
	for (int i = 0; i < 100; i++) {
		Point pixel((FWHMpoint.x - plot.cols / 2 + i), FWHMpoint.y);
		Scalar intensity = frame.at<uchar>(pixel);
		if (intensity.val[0] > maxIntensity)
			maxIntensity = intensity.val[0];
		Point curvePoint(i, plot.rows - intensity.val[0]);
		curvePoints.push_back(curvePoint);
	}
	for (int i = 0; i < curvePoints.size() - 1; i++) {
		line(plot, curvePoints[i], curvePoints[i + 1], Scalar(0, 128, 0), 1, CV_AA);
	}
	int HM = maxIntensity / 2;

	Mat bw = plot.clone();
	cvtColor(bw, bw, CV_BGR2GRAY);

	line(plot, Point(0, plot.rows - HM), Point(plot.cols - 1, plot.rows - HM), Scalar(255, 255, 255));
	int FWHM = 0;
	while (1) {
		FWHM += 1;
		Point pixel(plot.cols / 2 + FWHM, plot.rows - HM);
		Scalar intensity = bw.at<uchar>(pixel);
		if (intensity.val[0] != 0)
			break;
	}
	FWHM += 1;
	FWHM *= 2;
	FWHMs.push_back(FWHM);
	FWHMs.erase(FWHMs.begin());

	FWHM = accumulate(FWHMs.begin(), FWHMs.end(), 0.0) / FWHMs.size();

	cout << "FWHM = " << FWHM << "; HM = " << HM << endl;

	thresh = max(HM, 30);
	line(frame, Point(0, FWHMpoint.y), Point(frame.cols - 1, FWHMpoint.y), Scalar(255));
}