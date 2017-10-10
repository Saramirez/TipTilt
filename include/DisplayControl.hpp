#ifndef DC_H
#define DC_H

#include "opencv2/opencv.hpp"
#include <mutex>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

using namespace cv;
using namespace std;

class DisplayControl{
    private:
		wxImage img;
    public:
		DisplayControl();
		void DisplayFrame(Mat);
		void UpdateTTPos(int, int);
		wxBitmap bmp;
		int TTPosX;
		int TTPosY;
		mutex * mtxProtectingBmpAndCamPanel;
		mutex * mtxProtectingTTPositionsAndPanel;
		wxPanel * camPanel_p;
		wxPanel * TTPositionPanel_p;
};


#endif