#include "../include/TipTilt.hpp"

TipTilt::TipTilt() { 
	writeBuf = (char *) malloc(8);
	xAlFactor = 1.0308;
	yAlFactor = 1.028;
}


void TipTilt::configSerial(){	
	cfsetispeed(&SerialConfig,B9600);
	cfsetospeed(&SerialConfig,B9600);

	SerialConfig.c_cflag &= ~PARENB;
	SerialConfig.c_cflag &= ~CSTOPB;
	SerialConfig.c_cflag &= ~CSIZE; 
	SerialConfig.c_cflag |=  CS8;   
	SerialConfig.c_cflag &= ~CRTSCTS;
	SerialConfig.c_cflag |= CREAD | CLOCAL;

	cfmakeraw(&SerialConfig);	
}

int TipTilt::openComm(const char* device){	
	fd = open(device, O_RDWR | O_NOCTTY);
	if(fd < 0){
		cout << "Error opening ttyUSB0" << endl;
		return -1;
	}
	configSerial();
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&SerialConfig);
	return 0;
}

void TipTilt::closeComm(){	
	close(fd);
}

int TipTilt::getSteps(int south){
	if(south == 1)
		return sSteps ;
	else if(south == 0)
		return eSteps;
	else
		return -99;
}


void TipTilt::setErrors(int x, int y){
	/*double aux1 = xAlFactor * (double)x;
	int aux2 = xAlFactor * (double)x;
	int aux3 = xAlFactor * x;
	double aux4 = xAlFactor * x;*/
	eError = x;	
	sError = y;
	//cout << "Errors: " << eError << ", " << sError << endl; 

}

void TipTilt::setAlignmentFactors(double x, double y){
	xAlFactor = x;
	yAlFactor = y;
}

void TipTilt::goTo(char dir){
	char out = 'n';

	if(dir == 'K'){
		write(fd, "K", 1);
		read(fd, &out, 1);
		//cout << "Centered, returned: " << out << endl;
		return;
	}
	if(dir == 'N')
        writeBuf = (char *)"GN00001";
    else if(dir == 'S')
        writeBuf = (char *)"GS00001";
    else if(dir == 'E')
        writeBuf = (char *)"GT00001";
    else if(dir == 'W')
        writeBuf = (char *)"GW00001";

    int count = 0;

    while( out != 'L' || count < 10){
        write(fd, writeBuf, 7);
		read(fd, &out, 1);
        if(out == 'L')
            count = count + 1;
        else
            count = 100;
    }
}

void TipTilt::updatePosition(){
	if(eError > 0){
		writeBuf = (char *)"GT00001";
		write(fd, writeBuf, 7);
		eError--;
		eSteps++;
	}
	else if(eError < 0){
		writeBuf = (char *)"GW00001";
		write(fd, writeBuf, 7);		
		eError++;
		eSteps--;
	}
	if(sError > 0){
		writeBuf = (char *)"GN00001";
		write(fd, writeBuf, 7);
		sError--;
		sSteps++;
	}
	else if(sError < 0){
		writeBuf = (char *)"GS00001";
		write(fd, writeBuf, 7);		
		sError++;
		sSteps--;
	}		
}







