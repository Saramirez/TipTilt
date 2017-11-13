#include "../include/SystemControl.hpp"
#include "../include/DisplayControl.hpp"
#include "../include/cxxopts.h"
#include <iostream>

SystemControl sControl;

int main(int argc, char** argv)
{
// std::cout << cv::getBuildInformation() << std::endl;

	sControl.SetCamDevice(0);
	sControl.SetTTDevice(0);

//	system("guvcview -z &");

	cxxopts::Options options(argv[0], " - TipTilt correction system");

	options.add_options()
		("c, calibrate", "Calibrate the tip tilt device")
		("g, guide", "Take a full frame video for guiding, prior to correcting")
		;
	
	options.parse(argc, argv);


	if (options.count("c")) {
		cout << "Calibration option selected" << endl;
		sControl.CalibrateTT();
	}

	if (options.count("g")) {
		cout << "Guiding first option selected" << endl;
		if (sControl.Guide() != 0)
			return 0;
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	sControl.StartCapture();

	return 0;
}
