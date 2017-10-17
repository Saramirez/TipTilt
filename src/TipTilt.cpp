#include "../include/TipTilt.hpp"

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

// probar disminuir restTime
const int restTime = 8; //ms

TipTilt::TipTilt(int* _eX, int* _eY, mutex * _mtx) { 
	eX = _eX;
	eY = _eY;
	eXX = 0;
	eYY = 0;
	mtx = _mtx;
}

void TipTilt::setDevice(const char * _device) {
	device = _device;
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
		cout << "Error opening comm" << endl;
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
	//cout << "eX: " << *eX << ". eY" << *eY << endl;
	mtx->lock();
	if(*eX != 0){
		if(*eX > 0 && eSteps < 45){
			writeBuf = (char *)"GT00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);
			(*eX)--;
			eSteps++;
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		else if(*eX < 0 && eSteps > -45){
			writeBuf = (char *)"GW00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);
			(*eX)++;
			eSteps--;
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		//cout << "Out: " << out << endl;
	}
	if(*eY != 0){
		if(*eY > 0 && sSteps > -45){
			writeBuf = (char *)"GS00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);
			(*eY)--;
			sSteps--;
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		else if(*eY < 0 && sSteps < 45){
			writeBuf = (char *)"GN00001";
			write(fd, writeBuf, 7);	
			//write(fd, "L", 1);	
			(*eY)++;
			sSteps++;
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		//cout << "Out: " << out << endl;
	}
	mtx->unlock();
	//this_thread::sleep_for(chrono::microseconds(100));
}

void TipTilt::updatePositionV2() {
	if (!opened) {
		//cout << "Device is not opened. Can't update position." << endl;
		return;
	}
	//cout << "eX: " << *eX << ". eY" << *eY << endl;
	internalMtx.lock();
	if (eXX != 0) {
		if (eXX > 0 && eSteps < 45) {
			writeBuf = (char *)"GT00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);
			(eXX)--;
			eSteps++;
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		else if (eXX < 0 && eSteps > -45) {
			writeBuf = (char *)"GW00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);
			(eXX)++;
			eSteps--;
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		//cout << "Out: " << out << endl;
	}
	if (eYY != 0) {
		if (eYY > 0 && sSteps > -45) {
			writeBuf = (char *)"GS00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);
			(eYY)--;
			sSteps--;
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		else if (eYY < 0 && sSteps < 45) {
			writeBuf = (char *)"GN00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);	
			(eYY)++;
			sSteps++;
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		//cout << "Out: " << out << endl;
	}
	internalMtx.unlock();
	//this_thread::sleep_for(chrono::microseconds(100));
}

void TipTilt::setErrors(int x, int y) {
	internalMtx.lock();
	eXX = x;
	eYY = y;
	internalMtx.unlock();
}

void TipTilt::move(char dir){
	if(dir == 'n')
		writeBuf = (char *)"GN00001";
	else if(dir == 's')
		writeBuf = (char *)"GS00001";
	else if(dir == 'e')
		writeBuf = (char *)"GT00001";
	else if(dir == 'w')
		writeBuf = (char *)"GW00001";
	write(fd, writeBuf, 7);	
}

void TipTilt::moveWithWASD(){
	char dir = 'n';
	while(dir != 'q'){
		cin>>dir;
		cout << "input: " << dir << endl;
		if(dir == 'w')
			writeBuf = (char *)"GN00001";
		else if(dir == 's')
			writeBuf = (char *)"GS00001";
		else if(dir == 'd')
			writeBuf = (char *)"GT00001";
		else if(dir == 'a')
			writeBuf = (char *)"GW00001";
		else
			continue;		
		write(fd, writeBuf, 7);		
	}
}