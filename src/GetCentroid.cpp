#include "../include/frameProcess.hpp"

Point GetCentroid(Mat &src){
	Moments m = moments((src>=150), true);
	Point res(m.m10/m.m00, m.m01/m.m00);
	return res;
}

