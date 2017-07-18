#include "../include/CameraThread.hpp"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_CAMERA_THREAD_COMPLETED)
DEFINE_EVENT_TYPE(wxEVT_COMMAND_CAMERA_THREAD_UPDATE)

CameraThread::CameraThread(wxEvtHandler* _handler, VideoCapture* _cam) : wxThread(wxTHREAD_DETACHED){
    handler = _handler;
    cam = _cam;
}

wxThread::ExitCode CameraThread::Entry()
{
	captureAndProcess();
    // signal the event handler that this thread is going to be destroyed
    // NOTE: here we assume that using the m_pHandler pointer is safe,
    //       (in this case this is assured by the MyFrame destructor)
    wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_MYTHREAD_COMPLETED));
    return (wxThread::ExitCode)0;     // success
}

void CameraThread::captureAndProcess(){

	cout << "Starting capture process" << endl;
	int counter = 0;

	int xErr = 0;
	int yErr = 0;

	while(!TestDestroy()){
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

		counter++;
	}
    cout << "captureAndProcess returned" << endl;
    cout << "Updated Errors " << counter << " times." << endl;

    wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_COMMAND_MYTHREAD_UPDATE));
}