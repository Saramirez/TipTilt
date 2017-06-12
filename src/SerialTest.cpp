#include <iostream>
#include "../include/TipTilt.hpp"

using namespace std;

TipTilt TT;
int main( int argc, char** argv )
{
	TT.openComm("/dev/ttyUSB0");

	cout << "e, s: " << TT.getSteps(0) << ", " << TT.getSteps(1) << endl;

	TT.setErrors(2,-1);
	TT.updatePosition();
	cout << "e, s: " << TT.getSteps(0) << ", " << TT.getSteps(1) << endl;
	TT.center();

	TT.closeComm();

	return 0;
}
