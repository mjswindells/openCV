//#include <math.h> 
//#include <opencv2/opencv.hpp> 
//
//using namespace cv;
//using namespace std;
//
//void My_Interpolation(Mat& img_in, Mat& img_out, Size img_size) {
//
//	// 4개의 좌표값
//	int x1, y1, x2, y2;
//	double rx, ry, p, q;
//	double val; 
//	int cx = img_size.width;
//	int cy = img_size.height;
//
//	printf("height : %d\n", cy);
//	printf("width : %d\n", cx);
//
//	uchar* pt = img_in.data;
//	uchar* pt_out = img_out.data;
//
//	for (int j = 0; j < cy; j++)
//		for (int i = 0; i < cx; i++)
//		{
//			// rx ry double형 비율
//			rx = (img_in.cols - 1) * i / (cx - 1.);
//			ry = (img_in.rows - 1) * j / (cy - 1.); 
//			// 내림 값
//			x1 = rx; 
//			y1 = ry; 
//			// x1 y1의 다음 픽셀
//			x2 = x1 + 1; 
//			if (x2 == img_in.cols) x2 = img_in.cols - 1;
//			y2 = y1 + 1; 
//			if (y2 == img_in.rows) y2 = img_in.rows - 1; 
//
//			p = rx - (double)x1;
//			q = ry - (double)y1; 
//
//			val = (1. - p) * (1. - q) * pt[y1 * img_in.cols + x1]
//				+ p * (1. - q) * pt[y1 * img_in.cols + x2]
//				+ (1. - p) * q * pt[y2 * img_in.cols + x1]
//				+ p * q * pt[y2 * img_in.cols + x2];
//
//			pt_out[j * img_out.cols + i] = val;
//		}
//}
//void My_Rotate(Mat& img_in, double angle) {
//	Mat img_out;
//	img_out = Mat::zeros(Size(img_in.cols, img_in.rows), img_in.type());
//	int pt_x = img_in.cols / 2;
//	int pt_y = img_in.rows / 2;
//	int new_x;
//	int new_y;
//	double PI = 3.141592;
//	double seta = PI / (180.0 / angle);
//
//	uchar* pt = img_in.data;
//	uchar* pt_out = img_out.data;
//
//	for (int i = 0; i < img_in.rows; i++) {
//		for (int j = 0; j < img_in.cols; j++) {
//			new_x = (i - pt_y) * sin(seta) + (j - pt_x) * cos(seta) + pt_x;
//			new_y = (i - pt_y) * cos(seta) - (j - pt_x) * sin(seta) + pt_y;
//
//			// 범위 체크
//			if (new_x < 0)		continue;
//			if (new_x >= img_in.cols)	continue;
//			if (new_y < 0)		continue;
//			if (new_y >= img_in.rows)	continue;
//
//			pt_out[new_y * img_in.cols + new_x] = pt[i * img_in.cols + j];
//		}
//	}
//	int dx, dy;
//	for (int i = 0; i < img_out.rows; i++) {
//		for (int j = 0; j < img_out.cols; j++) {
//
//			if (j == 0) dx = dy = pt_out[i * img_in.cols + j + 1];
//			else if (j == img_out.cols - 1) dx = dy = pt_out[i * img_in.cols + j - 1];
//			else {
//				dx = pt_out[i * img_in.cols + j - 1];
//				dy = pt_out[i * img_in.cols + j + 1];
//			}
//			if (pt_out[i * img_in.cols + j] == 0 && dx != 0 && dy != 0)
//				pt_out[i * img_in.cols + j] = (dx + dy) / 2;
//		}
//	}
//	img_in = img_out;
//}
//
//int main()
//{
//	Mat img_in;
//
//	// image 읽고 gray로 바꾸기
//	img_in = imread("Lenna_256x256.png",-1);
//	cvtColor(img_in, img_in, cv::COLOR_RGB2GRAY);
//	imshow("source img", img_in);
//
//	Mat img_out_1 = Mat::zeros(436, 436, img_in.type());
//	Mat img_out_2 = Mat::zeros(512, 512, img_in.type());
//	My_Interpolation(img_in, img_out_1, Size(436, 436));
//	imshow("436 x 436", img_out_1); 
//	waitKey(0);
//
//	My_Interpolation(img_in, img_out_2, Size(512, 512));
//	imshow("512 x 512", img_out_2); 
//	waitKey(0);
//
//	Mat i1, i2, i3;
//	i1 = i2 = i3 = img_out_1;
//	My_Rotate(i1, 30);
//	imshow("30도 회전", i1); 
//	waitKey(0);
//
//	My_Rotate(i2, 45);
//	imshow("45도 회전", i2); 
//	waitKey(0);
//
//	My_Rotate(i3, 60);
//	imshow("60도 회전", i3); 
//	waitKey(0);
//
//	return 0;
//}