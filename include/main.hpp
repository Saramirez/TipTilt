#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "opencv2/stitching.hpp"
#include <X11/Xlib.h>

class TipTiltApp : public wxApp
{
  public:
    virtual bool OnInit();
    TipTiltApp(){
        if(XInitThreads() == 0){
            exit(EXIT_FAILURE);
        }
    }
};
