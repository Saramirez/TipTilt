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
const int ConstantFramerate = 10;
const int ConstantTimeBetweenErrorUpdate = 1000 / ConstantFramerate;
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
		bool measuringFWHM;
		bool measuringFWHMaux;
		int errorMode = 0;
		bool constantFramerateMode = false;
		Point FWHMpoint;
		bool simulate;
		mutex mtxProtectingValues;
		thread capturingThread;
		thread correctingThread;
		thread errorUpdateThread;
		Mat frame;
		void RunCapture();
		void RunCorrection();
		void RunErrorUpdate();
		void ToggleCorrection();
		void ChangeThresh(int);
		void ChangeFactors(int);
		void ChangeErrorMode();
		void CheckAndOpenCam();
		void CheckAndOpenTT();
		void ToggleShowThresh();
		void ToggleSimulate();
		void ChangeErrorFilter();
		void SetThreshold(int);
		void SetStarSize(double);
		double GetStarSize();
		void CenterTT();
		//static void GetFWHMPointFromMouse(int, int, int, int, void*);
	public:
		SystemControl();

		//static bool measuringFWHM;
		//static Point FWHMpoint;
		int withFilter;

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
