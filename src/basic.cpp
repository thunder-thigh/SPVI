#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	Mat image = imread("./../testing/monke.jpeg");
	if (image.empty()){
		cout<<"Image not found";
		cin.get();
		return -1;
	}
	imshow("Window name", image);
	waitKey(0);
	return 0;
}
