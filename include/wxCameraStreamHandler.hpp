#ifndef wxCSH_HH
#define wxCSH_HH

#include "opencv2/opencv.hpp"
#include <iostream>
#include "../include/TipTilt.hpp"
#include <math.h>
#include <atomic>
#include <thread>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

using namespace cv;
using namespace std;

class wxCameraStreamHandler : public wxWindow {

	public:
		wxCameraStreamHandler(wxWindow*,
							  const wxPoint&, 
							  const wxSize&);
		virtual ~wxCameraStreamHandler() {};
		bool openCamera(const string);
		void stopCapture();
		void startCapture();

	private:
		atomic<bool> capturing;
		thread captureThread;
		Point target = Point(64, 64);
		double xPixToSteps = 0.42;
		double yPixToSteps = 0.43;
		bool targetSet = true;

		double corrAngle = 0.023;
		double cosCorrAngle = 1;
		double sinCorrAngle = 0.023;

		Rect roi = Rect(265, 168, 128, 128);

		VideoCapture cam;
		Mat cvFrame;
		wxImage wxFrame;
		wxBitmap wxBmp;
		wxWindow* parent;

		void setTarget(int, int);	
		Point getCentroid(Mat&);
		void calculateErrors(Point, int&, int&);
		void captureAndProcess();
	
		void displayFrame();
		void OnPaint(wxPaintEvent& e);
		void OnKey(wxKeyEvent& e);

	protected:
		DECLARE_EVENT_TABLE();
};

#endif