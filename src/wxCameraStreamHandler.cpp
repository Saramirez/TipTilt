#include "../include/wxCameraStreamHandler.hpp"

BEGIN_EVENT_TABLE(wxCameraStreamHandler, wxWindow)
	EVT_PAINT(wxCameraStreamHandler::OnPaint)
	EVT_CHAR(wxCameraStreamHandler::OnKey)
END_EVENT_TABLE()

wxDEFINE_EVENT(FRAME_READ_EVENT, wxCommandEvent);

wxCameraStreamHandler::wxCameraStreamHandler(
	wxWindow* _parent,
	const wxPoint& _position, 
	const wxSize& _size)
	: wxWindow(_parent, -1, _position, _size, wxSIMPLE_BORDER){

 	parent = _parent;
 	Bind(FRAME_READ_EVENT, &wxCameraStreamHandler::OnFrameRead, this, -1);
}

void wxCameraStreamHandler::setTarget(int tx, int ty){
    target.x = tx;
    target.y = ty;
}

Point wxCameraStreamHandler::getCentroid(Mat& src){
	Moments m = moments((src>=150), true);
	Point res(m.m10/m.m00, m.m01/m.m00);
	return res;
}

void wxCameraStreamHandler::calculateErrors(Point centroid, int& xErr, int& yErr){
	int dx = xPixToSteps * (target.x - centroid.x);
    int dy = yPixToSteps * (target.y - centroid.y);
	
	//cout << "Errors: dx, dy = " << dx << "," << dy << endl;
	
    xErr = dx * cosCorrAngle + dy * sinCorrAngle;
    yErr = -dx * sinCorrAngle + dy * cosCorrAngle;

    //cout << "Errors: xErr, yErr = " << *xErr << "," << *yErr << endl;
}

void wxCameraStreamHandler::startCapture(){
	if (!cam.isOpened()){
		cout << "Camera is not opened. Can't start capture." << endl;
		return;
	}
	capturing = true;
	//captureThread = thread(&wxCameraStreamHandler::captureAndProcess, this);
}

void wxCameraStreamHandler::stopCapture(){
	if (!cam.isOpened()){
		cout << "Camera is not opened. Can't stop capture." << endl;
		return;
	}
	capturing = false;
	captureThread.join();
}

void wxCameraStreamHandler::SendEvent(){
	wxCommandEvent event(FRAME_READ_EVENT, GetId());
	event.SetEventObject(this);
	// Do send it
	ProcessWindowEvent(event);
}

void wxCameraStreamHandler::captureAndProcess(){

	cout << "Starting capture process" << endl;
	int counter = 0;

	int xErr = 0;
	int yErr = 0;

	while(capturing){
		if (!cam.isOpened()){
			cout << "Cam is not opened, can't captureAndProcess." << endl;
			return;
		}
		cam >> cvFrame;
		cvFrame = cvFrame(roi);

		if(targetSet){
			Point centroid = getCentroid(cvFrame);
	        calculateErrors(centroid, xErr, yErr);
	        //TT.setErrors(xErr, yErr);

			circle(cvFrame, centroid, 5, Scalar(128,0,0));
		}

		cvtColor(cvFrame, cvFrame, CV_GRAY2RGB);
		circle(cvFrame, Point(target.x,target.y), 3, Scalar(0,128,128));

		//SendEvent();
		//displayFrame();

		counter++;
	}
    cout << "captureAndProcess returned" << endl;
    cout << "Updated Errors " << counter << " times." << endl;
}

bool wxCameraStreamHandler::openCamera(const string gstreamPipeline){
	cam.open(gstreamPipeline);

	if (!cam.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return false;
	}

	cam >> cvFrame;
	cvFrame = cvFrame(roi);
	cvtColor(cvFrame, cvFrame, CV_GRAY2RGB);

	wxFrame = wxImage(cvFrame.cols, cvFrame.rows, cvFrame.data, TRUE);

	SendEvent();

	return true;
}

void wxCameraStreamHandler::OnFrameRead(wxCommandEvent& event){
	wxFrame = wxImage(cvFrame.cols, cvFrame.rows, cvFrame.data, TRUE);
	wxBmp = wxBitmap(wxFrame);
	Refresh(FALSE);
	Update();
}

void wxCameraStreamHandler::OnPaint(wxPaintEvent& event){
	wxPaintDC dc(this);

	if(!dc.IsOk())
		return;

	int x, y, w, h;

	dc.GetClippingBox(&x, &y, &w, &h);
	dc.DrawBitmap(wxBmp, x, y);

	return;
}

void wxCameraStreamHandler::OnKey(wxKeyEvent& event){
	if(event.GetKeyCode() == WXK_ESCAPE) parent->Close();
}