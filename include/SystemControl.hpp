#ifndef SC_H
#define SC_H

#include "CameraStreamHandler.hpp"
#include "TipTilt.hpp"
#include "StreamPlayer.hpp"
#include "opencv2/opencv.hpp"

#include <atomic>
#include <thread>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

const int sControlId = 9;

class SystemControl {
	private:
		CameraStreamHandler CSH;
		TipTilt TT;
		mutex mtxProtectingErrors;
		int eX;
		int eY;
		atomic<bool> capturing;
		atomic<bool> correcting;
		thread capturingThread;
		thread correctingThread;
		Mat frame;
		void RunCapture();
		void RunCorrection();
	public:
		StreamPlayer * player_p;
		SystemControl(const char*, const char*);
		int StartCapture();
		int StartCorrection();
		int StopCorrection();
		int StopCapture();
};






#endif // !SC_H
