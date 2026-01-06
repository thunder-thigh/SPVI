#include <iostream>
#include <opencv2/opencv.hpp>
#include "defs.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	Mat image = imread("./../testing/monke.jpeg");
	if (image.empty()){
		cout<<"Image not found\n";
		cin.get();
		return -1;
	}
	cout<<sizeof(image)<<"\n";
	imshow("Window name", image);
	waitKey(0);
	return 0;
}
