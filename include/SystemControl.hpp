#ifndef SC_H
#define SC_H

#include "../include/CameraStreamHandler.hpp"
#include "../include/TipTilt.hpp"
#include "../include/wxStreamPlayer.hpp"
#include "opencv2/opencv.hpp"
#include <chrono>
#include <thread>
#include <atomic>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

const int sControlId = 9;
/*
BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(FRAME_READY, -1);
END_DECLARE_EVENT_TYPES()
*/
class SystemControl {
	private:
		int eX;
		int eY;
		CameraStreamHandler CSH;
		TipTilt TT;
		mutex mtxProtectingErrors;

		wxStreamPlayer * player_p;
		/*mutex mtxFrames;
		condition_variable frameReadyCV;
		void GetFrames();
		void SendEvent();*/
		thread captureThread;
		atomic<bool> capturing;
	public:
		SystemControl(const char*, const char*);
		void SetPlayer(wxStreamPlayer *);
		int Setup();
		void Start();
		void Run();
		void Stop();
};






#endif // !SC_H
