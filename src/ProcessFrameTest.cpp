#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../include/frameProcess.hpp"

using namespace cv;
using namespace std;

Mat src;

int main( int argc, char** argv )
{
	/// Load source image and convert it to gray
	src = imread( argv[1], IMREAD_GRAYSCALE);

	Point centroid = GetCentroid(&src);	
	
	circle(src, centroid, 5, Scalar(0,0,0));
	
	imshow("Frame", src);

	waitKey(0);
	return(0);
}
