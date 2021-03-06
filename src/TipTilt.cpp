#include "../include/TipTilt.hpp"
#include <chrono>

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

TipTilt::TipTilt(const char* _device) { 
	//writeBuf = (char *) malloc(8);
	device = _device;
	openComm();
}

bool TipTilt::isOpened(){
	return opened;
}

void TipTilt::configSerial(){	
	cfsetispeed(&SerialConfig,B9600);
	cfsetospeed(&SerialConfig,B9600);

	cfmakeraw(&SerialConfig);	
}

int TipTilt::openComm(){	
	fd = open(device, O_RDWR | O_NOCTTY);
	if(fd < 0){
		cout << "Error opening ttyUSB0" << endl;
		return -1;
	}
	opened = true;
	configSerial();
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&SerialConfig);
	return 0;
}

void TipTilt::closeComm(){	
	if(!opened){
		cout << "Device is not opened. Can't close comm." << endl;
		return;
	}
	close(fd);
	opened = false;
    cout << "Closed Comm" << endl;
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

int TipTilt::goTo(char dir){
	if(!opened){
		cout << "Device is not opened. Can't go to " << dir << "." << endl;
		return -1;
	}
	cout << "\nGoing to: " << dir << endl;
	out = 'n';
	if(dir == 'K'){
		write(fd, "K", 1);
		read(fd, &out, 1);
		//cout << "Centered, returned: " << out << endl;
		return 0;
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
    int count2 = 0;

	auto start = get_time::now();
	out = 'L';
    while( out != 'L' || count < 10){
        if(out == 'L')
            count = count + 1;
        else{
			if(count2 == 0)
				start = get_time::now();
            count = 100;
            count2 ++;
        }
        write(fd, writeBuf, 7);
		read(fd, &out, 1);
    }
	auto end = get_time::now();
	auto diff = end - start;
	
	cout << "Moved to " << dir << ". Elapsed time is :  "<< chrono::duration_cast<ms>(diff).count() << " ms "<<endl;
    cout << "Moved " << count2 << "times" << endl;
	cout << "Period: " << (count2 / chrono::duration_cast<ms>(diff).count()) << "[ms/step]" << endl;
	return count2;
}

void TipTilt::updatePosition(){
	if(!opened){
		//cout << "Device is not opened. Can't update position." << endl;
		return;
	}
	if(eError != 0){
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
		
		//read(fd, &out, 1);
		//cout << "Out: " << out << endl;
	}
	if(sError != 0){
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

		//read(fd, &out, 1);
		//cout << "Out: " << out << endl;
	}
}

void TipTilt::start(){
	//Revisa si el dispositivo esta conectado y escuchando, luego parte el loop de control en una thread.
	if(!opened){
		cout << "Device is not opened. Can't start control loop." << endl;
		return;
	}
	running = true;
	runningThread = thread(&TipTilt::run, this);
}

void TipTilt::run(){
	//Metodo que se estara corriendo en una thread.
	int counter = 0;
	while(running){
    	updatePosition();
        counter ++;
    }
    cout << "UpdateTipTilt returned" << endl;
    cout << "Updated TipTilt " << counter << " times." << endl;
}

void TipTilt::stop(){
	//Se hace terminar la thread al hacer running = false.
	if(!opened){
		cout << "Device is not opened. Can't stop control loop." << endl;
		return;
	}
	running = false;
	runningThread.join();
};






