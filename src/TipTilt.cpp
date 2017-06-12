#include "../include/TipTilt.hpp"

TipTilt::TipTilt() { 
	writeBuf = (char *) malloc(8);
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
	SerialConfig.c_iflag &= ~(IXON | IXOFF | IXANY);
	SerialConfig.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);	
}

int TipTilt::openComm(const char* device){	
	fd = open(device, O_RDWR | O_NOCTTY);
	if(fd < 0){
		cout << "Error opening ttyUSB0" << endl;
		return -1;
	}
	configSerial();
	tcsetattr(fd,TCSANOW,&SerialConfig);
	return 0;
}

void TipTilt::closeComm(){	
	close(fd);
}

void TipTilt::center(){
	write(fd, "K", 1);	
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
	eError = x;	
	sError = y;
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







