#include "../include/TipTiltControl.hpp"

TipTiltControl::TipTiltControl(const char* TTDevice, const char* camDevice) :
				CSH(camDevice, &eX, &eY, &mtx),
				TT(TTDevice, &eX, &eY, &mtx){
	eX = 0;
	eY = 0;
}