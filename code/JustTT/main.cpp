#include "TipTilt.hpp"

using namespace std;

int eX = 0;
int eY = 0;
mutex mtx;
TipTilt TT("/dev/ttyUSB0", &eX, &eY, &mtx);

int main( int argc, char** argv )
{	
    TT.moveWithWASD();
    TT.closeComm();
	return(0);
}