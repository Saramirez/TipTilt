#ifndef SC_H
#define SC_H

#include "../include/CameraStreamHandler.hpp"
#include "../include/TipTilt.hpp"
#include "../include/wxStreamPlayer.hpp"

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
		wxStreamPlayer * player_p;
		int eX;
		int eY;
	public:
		SystemControl(const char*, const char*);
		int Setup();
		int Start();
		void SetPlayer(wxStreamPlayer *);
};






#endif // !SC_H
