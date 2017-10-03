#ifndef TTGui_H
#define TTGui_H

/**
@file
Subclass of MainFrame, which is generated by wxFormBuilder.
*/

#include "MainFrame.h"
#include "DisplayControl.hpp"
#include "SystemControl.hpp"
#include <mutex>

using namespace std;

//// end generated include

/** Implementing MainFrame */
class TTGui : public MainFrame
{
	private:
		mutex mtxProtectingBmpAndCamPanel;
		mutex mtxProtectingTTPositionsAndPanel;
	protected:
		// Handlers for MainFrame events.
		void OnSelectCalibrate(wxCommandEvent& event);
		void OnSelectCameraSettings(wxCommandEvent& event);
		void OnClickCapture(wxCommandEvent& event);
		void OnCaptureDeviceChoice(wxCommandEvent& event);
		void OnClickCorrection(wxCommandEvent& event);
		void OnTTDeviceChoice(wxCommandEvent& event);
		void OnFramePaint(wxPaintEvent& event);
		void OnThrshTextSet(wxCommandEvent& event);
		void OnShowThresholdChecked(wxCommandEvent& event);
		void OnGetStarSizeClicked(wxCommandEvent& event);
		void OnStrSzTextSet(wxCommandEvent& event);
		void OnDefaultClicked(wxCommandEvent& event);
		void OnClickCenterTT(wxCommandEvent& event);
		void OnTTPosPaint(wxPaintEvent& event);
		void OnClickExit(wxCommandEvent& event);
	public:
		shared_ptr<DisplayControl> dControl_p;
		SystemControl * sControl_p;
		/** Constructor */
		TTGui( wxWindow* parent );
	//// end generated class members
	
};

#endif // TTGui_H
