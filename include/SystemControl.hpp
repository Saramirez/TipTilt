#ifndef SC_H
#define SC_H

#include "CameraStreamHandler.hpp"
#include "TipTilt.hpp"
#include "DisplayControl.hpp"
#include "opencv2/opencv.hpp"

#include <atomic>
#include <thread>
#include <mutex>

using namespace std;
using namespace cv;

class SystemControl {
	private:
		DisplayControl dControl;
		CameraStreamHandler CSH;
		TipTilt TT;
		mutex mtxProtectingErrors;
		mutex mtxProtectingDisplayControl;
		int eX;
		int eY;
		int TTposX;
		int TTposY;
		atomic<bool> capturingInternal;
		atomic<bool> correctingInternal;
		bool capturing;
		bool correcting;
		bool showThresh;
		bool simulate;
		mutex mtxProtectingValues;
		thread capturingThread;
		thread correctingThread;
		Mat frame;
		void RunCapture();
		void RunCorrection();
		void ToggleCorrection();
		void ChangeThresh(int);
		void CheckAndOpenCam();
		void CheckAndOpenTT();
		void ToggleShowThresh();
		void ToggleSimulate();
		void SetThreshold(int);
		void SetStarSize(double);
		double GetStarSize();
		void CenterTT();
	public:
		SystemControl();
		int GetKeyFromKeyboard();
		void SetCamDevice(int);
		void SetTTDevice(int);
		int CalibrateTT();
		int StartCapture();
		int StartCorrection();
		int StopCorrection();
		int StopCapture();
		bool IsCapturing();
		bool IsCorrecting();
		void Guide();
		void SimpleCalib();
};






#endif // !SC_H
