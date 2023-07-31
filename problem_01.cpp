#include <vector>
#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

int main() {
	
	VideoCapture capture1("sample1.mp4");
	VideoCapture capture2("sample2.mp4");
	Mat frame1, frame2, frame3;


	if (!capture1.isOpened()) {
		printf("Video_1 file can not open\n");
		return 0;
	}
	if (!capture2.isOpened()) {
		printf("Video_2 file can not open\n");
		return 0;
	}
	while (1) {
		capture1 >> frame1;
		capture2 >> frame2;

		if (frame1.empty()) break;
		if (frame2.empty()) break;

		if (!frame1.empty() || !frame2.empty()) { 
			hconcat(frame1, frame2, frame3);
		}

		imshow("video_1", frame1);
		imshow("video_2", frame2); 
		imshow("concat", frame3); 
		if (waitKey(10) > 0) break;
	}
	return 0;
}


