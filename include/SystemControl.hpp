#ifndef SC_H
#define SC_H

#include "../include/CameraStreamHandler.hpp"
#include "../include/TipTilt.hpp"

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
	public:
		SystemControl(const char*, const char*);
		int Setup();
		int Start();
};






#endif // !SC_H
