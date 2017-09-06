#include "../include/TipTilt.hpp"

using ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

const int restTime = 8; //ms

TipTilt::TipTilt(const char* _device, int* _eX, int* _eY, mutex * _mtx) { 
	device = _device;
	eX = _eX;
	eY = _eY;
	mtx = _mtx;
	openComm();
	NSCenter = 0;
	WECenter = 0;
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
			addStep(1);
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		else if(*eX < 0 && eSteps > -45){
			writeBuf = (char *)"GW00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);
			(*eX)++;
			eSteps--;
			addStep(1);
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		//cout << "Out: " << out << endl;
	}
	if(*eY != 0){
		if(*eY > 0 && sSteps < 45){
			writeBuf = (char *)"GN00001";
			write(fd, writeBuf, 7);
			//write(fd, "L", 1);
			(*eY)--;
			sSteps++;
			addStep(0);
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		else if(*eY < 0 && sSteps > -45){
			writeBuf = (char *)"GS00001";
			write(fd, writeBuf, 7);	
			//write(fd, "L", 1);	
			(*eY)++;
			sSteps--;
			addStep(0);
			//read(fd, &out, 1);
			this_thread::sleep_for(chrono::milliseconds(restTime));
		}
		//cout << "Out: " << out << endl;
	}
	mtx->unlock();
	//this_thread::sleep_for(chrono::microseconds(100));
}

void TipTilt::addStep(int dir) {
	if (dir == 0) {
		for (int i = avgCount - 1; i > 0; i--)
			sLastSteps[i] = sLastSteps[i - 1];
		sLastSteps[0] = sSteps;
	}
	else {
		for (int i = avgCount - 1; i > 0; i--)
			eLastSteps[i] = eLastSteps[i - 1];
		eLastSteps[0] = eSteps;
	}		
}

int TipTilt::getAvgStep(int dir) {
	double res = 0;
	if (dir == 0) {
		for (int i = 0; i < avgCount; i++)
			res += sLastSteps[i];
		res = res / avgCount;
		return (int)res;
	}
	else {
		for (int i = 0; i < avgCount; i++)
			res += eLastSteps[i];
		res = res / avgCount;
		return (int)res;
	}
}

int TipTilt::start(){
	//Revisa si el dispositivo esta conectado y escuchando, luego parte el loop de control en una thread.
	if(!opened){
		cout << "Device is not opened. Can't start control loop." << endl;
		return -1;
	}
	eSteps = 0;
	sSteps = 0;
	running = true;
	runningThread = thread(&TipTilt::run, this);
	return 0;
}

void TipTilt::run(){
	//Metodo que se estara corriendo en una thread.
	int counter = 0;
	while(running){
		/*
		int avg = getAvgStep(0);
		if (avg < -30)
			NSCenter = -1;
		else if (avg <= 30)
			NSCenter = 0;
		else if (avg > 30)
			NSCenter = 1;

		int avg = getAvgStep(1);
		if (avg < -30)
			WECenter = -1;
		else if (avg <= 30)
			WECenter = 0;
		else if (avg > 30)
			WECenter = 1;
		*/

    	updatePosition();
		counter++;
    }
    //cout << "UpdateTipTilt returned" << endl;
    //cout << "Updated TipTilt " << counter << " times." << endl;
}

int TipTilt::stop(){
	//Se hace terminar la thread al hacer running = false.
	if(!opened){
		cout << "Device is not opened. Can't stop control loop." << endl;
		return -1;
	}
	running = false;
	runningThread.join();
	return 0;
};

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




