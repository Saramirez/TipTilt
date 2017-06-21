#include "../include/TipTilt.hpp"
#include "../include/frameProcess.hpp"

TipTilt::TipTilt() { 
	writeBuf = (char *) malloc(8);
}


void TipTilt::configSerial(){	
	cfsetispeed(&SerialConfig,B9600);
	cfsetospeed(&SerialConfig,B9600);
/*
	SerialConfig.c_iflag |= IGNBRK 

	SerialConfig.c_cflag &= ~PARENB;
	SerialConfig.c_cflag &= ~CSTOPB;
	SerialConfig.c_cflag &= ~CSIZE; 
	SerialConfig.c_cflag |=  CS8;   
	SerialConfig.c_cflag &= ~CRTSCTS;
	SerialConfig.c_cflag |= CREAD | CLOCAL;*/

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


void TipTilt::setErrors(Point target, Point centroid){
	int dx = xPixToSteps * (target.x - centroid.x);
    int dy = yPixToSteps * (target.y - centroid.y);

	//cout << "Errors: dx, dy = " << dx << "," << dy << endl;

	eError = dx * cosCorrAngle + dy * sinCorrAngle;
	sError = -dx * sinCorrAngle + dy * cosCorrAngle;

	//cout << "Errors: eError, sError = " << eError << "," << sError << endl;
}

int TipTilt::goTo(char dir){
	char out = 'n';

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

    while( out != 'L' || count < 10){
        write(fd, writeBuf, 7);
		read(fd, &out, 1);
        if(out == 'L')
            count = count + 1;
        else{
            count = 100;
            count2 ++;
        }
    }
    return count2;
}

void TipTilt::updatePosition(){
	char out = 'n';

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

void TipTilt::calibrate(VideoCapture& cam){
	namedWindow("Calibration",CV_WINDOW_AUTOSIZE);

	Mat K,N,S,E,W;
	Point cK, cN, cS, cE, cW;

	goTo('K');
	cam >> K;

	goTo('N');
	cam >> N;
	int NSSteps = goTo('S');
	cam >> S;

    goTo('K');

    goTo('E');
	cam >> E;
    int EWSteps = goTo('W');
	cam >> W;

	//cam.release();

	cK = GetCentroid(K);
	cN = GetCentroid(N);
	cS = GetCentroid(S);
	cE = GetCentroid(E);
	cW = GetCentroid(W);

	cout << "Centroids: " << cK.x << "," << cK.y << ";" << cN.x << "," << cN.y << ";" 
							<< cS.x << "," << cS.y << ";" << cE.x << "," << cE.y << ";" 
							<< cW.x << "," << cW.y << endl;

	cout << "Steps: " << NSSteps << "," << EWSteps << endl;

	double NSDist = sqrt(pow(cN.x - cS.x, 2) + pow(cN.y - cS.y, 2));
	double EWDist = sqrt(pow(cE.x - cW.x, 2) + pow(cE.y - cW.y, 2));

	cout << "Dists: " << NSDist << "," << EWDist << endl;

	xPixToSteps = NSDist / ((double)NSSteps);
	yPixToSteps = EWDist / ((double)EWSteps);

	cout << "Factors: " << xPixToSteps << "," << yPixToSteps << endl;

	double tan1 = ((double)(cW.y - cE.y))/((double)(cE.x - cW.x));
	double tan2 = ((double)(cN.x - cS.x))/((double)(cN.y - cS.y));

	cout << "Tans: " << tan1 << "," << tan2 << endl;

	double alpha = atan(tan1);
	double beta = atan(tan2);

	double corrAngle = (alpha + beta) / 2.0;
	cosCorrAngle = cos(corrAngle);
	sinCorrAngle = sin(corrAngle);

	cout << "Angles: " << alpha << "," << beta << ";" << corrAngle << endl;

	Mat complete = (K > 150) + (N > 150) + (S > 150) + (E > 150) + (W > 150);
	cvtColor(complete, complete, CV_GRAY2BGR);

	circle(complete, cK, 5, Scalar(0,0,0));
	circle(complete, cN, 5, Scalar(0,128,0));
	circle(complete, cS, 5, Scalar(0,0,128));
	circle(complete, cE, 5, Scalar(128,0,0));
	circle(complete, cW, 5, Scalar(128,128,128));
	imshow("Calibration", complete);


	waitKey(0);

	destroyWindow("Calibration");
}







