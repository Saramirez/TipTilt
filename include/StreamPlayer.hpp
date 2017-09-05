#ifndef SP_H
#define SP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "opencv2/opencv.hpp"

using namespace cv;

class StreamPlayer{
    private:
		wxPanel * panel_p;
		wxImage img;
		wxBitmap bmp;
    public:
        StreamPlayer(wxPanel *);
		void DisplayFrame(Mat);
};

#endif