#ifndef SC_H
#define SC_H

#include "../include/CameraStreamHandler.hpp"
#include "../include/TipTilt.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class SystemControl {
	private:
		CameraStreamHandler CSH;
		TipTilt TT;
		mutex mtxProtectingErrors;
		wxMutex mtxProtectingBitmap;
		wxStreamPlayer * player_p;
		int eX;
		int eY;
		wxBitmap bmp;
		wxImage img;
	public:
		SystemControl(const char*, const char*);
		int Setup();
		int Start();
		void SetPlayer(wxStreamPlayer *);
		wxImage * GetWxBitmap();
		wxMutex * GetWxMutexProtectingBitmap();
};






#endif // !SC_H
