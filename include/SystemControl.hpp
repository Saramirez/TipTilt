#ifndef SC_H
#define SC_H

#include "CameraStreamHandler.hpp"
#include "TipTilt.hpp"
#include "DisplayControl.hpp"
#include "opencv2/opencv.hpp"

#include <atomic>
#include <thread>
#include <mutex>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

const int sControlId = 9;
using namespace std;

class SystemControl {
	private:
		CameraStreamHandler CSH;
		TipTilt TT;
		mutex mtxProtectingErrors;
		int eX;
		int eY;
		int TTposX;
		int TTposY;
		atomic<bool> capturingInternal;
		atomic<bool> correctingInternal;
		bool capturing;
		bool correcting;
		bool showThresh;
		mutex mtxProtectingValues;
		mutex mtxProtectingDisplayControl;
		thread capturingThread;
		thread correctingThread;
		Mat frame;
		void RunCapture();
		void RunCorrection();
	public:
		DisplayControl * dControl_p;
		SystemControl(const char*, const char*);
		int StartCapture();
		int StartCorrection();
		int StopCorrection();
		int StopCapture();
		bool IsCapturing();
		bool IsCorrecting();
		void ToggleShowThresh();
		void SetThreshold(int);
		void SetStarSize(double);
		double GetStarSize();
};






#endif // !SC_H
