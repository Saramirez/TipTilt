#ifndef SC_H
#define SC_H

#include "../include/CameraStreamHandler.hpp"
#include "../include/TipTilt.hpp"
#include "../include/wxStreamPlayer.hpp"

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
		thread capturingThread;
	public:
		wxStreamPlayer * player_p;
		SystemControl(const char*, const char*);
		int Start();
		void RunCapture();
		int Stop();
};






#endif // !SC_H
