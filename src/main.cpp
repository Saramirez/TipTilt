#include "../include/main.hpp"
#include "../include/TTGui.hpp"
#include "../include/SystemControl.hpp"
#include "../include/DisplayControl.hpp"


IMPLEMENT_APP(TipTiltApp);

SystemControl sControl;
DisplayControl dControl;
mutex mtxProtectingDisplayControl;
mutex mtxProtectingBmpAndCamPanel;
mutex mtxProtectingTTPositionsAndPanel;

//"/dev/ttyUSB0", "v4l2src device=/dev/video0 ! video/x-raw,format=GRAY8 ! appsink");
//"/dev/ttyUSB0", "v4l2src device=/dev/video0 ! video/x-raw,format=GRAY8 ! appsink"

bool TipTiltApp::OnInit()
{
	TTGui * gui = new TTGui(NULL);

	sControl.dControl_p = &dControl;
	sControl.mtxProtectingDisplayControl = &mtxProtectingDisplayControl;
	sControl.SetCamDevice(0);
	sControl.SetTTDevice(0);

	dControl.mtxProtectingBmpAndCamPanel = &mtxProtectingBmpAndCamPanel;
	dControl.mtxProtectingTTPositionsAndPanel = &mtxProtectingTTPositionsAndPanel;
	dControl.camPanel_p = gui->GetCamPanel();
	dControl.TTPositionPanel_p = gui->GetTTPosPanel();

	gui->mtxProtectingBmpAndCamPanel = &mtxProtectingBmpAndCamPanel;
	gui->mtxProtectingTTPositionsAndPanel = &mtxProtectingTTPositionsAndPanel;
	gui->mtxProtectingDisplayControl = &mtxProtectingDisplayControl;
	gui->sControl_p = &sControl;
	gui->dControl_p = &dControl;

    gui->Show(true);

	//sControl.StartCapture();

    return true;
}

