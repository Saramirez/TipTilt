#include "../include/frameProcess.hpp"


void ProcessFrame(Mat* src){
	Moments m = moments((*src >= 200), true);
	Point centroid(m.m10/m.m00, m.m01/m.m00);
	circle(*src, centroid, 5, Scalar(0,0,0));
	imshow("Source", *src);
}

