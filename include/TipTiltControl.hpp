#ifndef TTC_H
#define TTC_H

#include "../include/CameraStreamHandler.hpp"
#include "../include/TipTilt.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class TipTiltControl {
	private:
		CameraStreamHandler CSH;
		TipTilt TT;
		mutex mtxProtectingErrors;
		wxMutex mtxProtectingBitmap;
		wxStreamThread streamThread;
		int eX;
		int eY;
		wxBitmap bmp;
	public:
		TipTiltControl(const char*, const char*);
		int Setup();
		int Start();
};






#endif // !TTC_H
