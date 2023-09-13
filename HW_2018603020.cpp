#include <opencv2/opencv.hpp>

using namespace cv;

uchar Range_(double x) {
	if (x < 0) x = 0;
	if ((x > 255)) x = 255;
	return x;
}

Mat Filtering(Mat src, double** filter, int N, int Channel)
{
	int H = src.rows;
	int W = src.cols;
	Mat rtn = src.clone();

	if (Channel == 3) {
		for (int h = 0;h < H;h++) {
			for (int w = 0;w < W;w++) {
				double B = 0;
				double G = 0;
				double R = 0;
				for (int j = -N;j < N + 1;j++) {
					for (int i = -N;i < N + 1;i++) {
						if (h + j<0 || h + j>=H || w + i<0 || w + i>=W) {
							continue;
						}
						else {
							B += src.at<Vec3b>(h + j, w + i)[0] * filter[j + N][i + N];
							G += src.at<Vec3b>(h + j, w + i)[1] * filter[j + N][i + N];
							R += src.at<Vec3b>(h + j, w + i)[2] * filter[j + N][i + N]; 
						}
					}
				}
				rtn.at<Vec3b>(h,  w)[0] = Range_(B);
				rtn.at<Vec3b>(h , w)[1] = Range_(G);
				rtn.at<Vec3b>(h , w)[2] = Range_(R);
			}
		} 
		for (int n = 0; n < N; n++)
			delete[] filter[n];
		delete[] filter;
		return rtn;
	}
	else if (Channel == 1) {
		for (int h = 0;h < H;h++) {
			for (int w = 0;w < W;w++) {
				double B = 0;
				for (int j = -N;j < N + 1;j++) {
					for (int i = -N;i < N + 1;i++) {
						if (h + j < 0 || h + j >= H || w + i < 0 || w + i >= W) 
							continue; 
						else 
							B += src.at<uchar>(h + j, w + i) * filter[j + N][i + N];
					}
				}
				rtn.at<uchar>(h,  w) = Range_(B);
			}
		} 
		for (int n = 0; n < N; n++)
			delete[] filter[n];
		delete[] filter;
		return rtn;
	}
	else {}
}


double** MovingAverage(int N) {
	int size = N * 2 + 1;
	double** filter = new double* [size];
	for (int n = 0; n < size; n++)
	{
		filter[n] = new double[size];
		memset(filter[n], 0, sizeof(double) * size);
	}
	double tmp = size * size;

	for (int h = 0; h < size; h++) {
		for (int w = 0; w < size; w++) {
			filter[h][w] = 1.0 / tmp;
		}
	}
	return filter;
}

double** Laplacian(int N) {
	int size = N * 2 + 1;
	double** filter = new double* [size];
	for (int n = 0; n < size; n++)
	{
		filter[n] = new double[size];
		memset(filter[n], 0, sizeof(double) * size);
	}

	filter[N][N] = -4;
	filter[N-1][N] = 1;
	filter[N][N-1] = 1;
	filter[N+1][N] = 1;
	filter[N][N+1] = 1;

	return filter;
}

double** SharpeningFilter(int N) {
	int size = N * 2 + 1;
	double** filter = new double* [size];
	for (int n = 0; n < size; n++)
	{
		filter[n] = new double[size];
		memset(filter[n], 0, sizeof(double) * size);
	}

	double** LF = Laplacian(N);

	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			if (N == i && N == j) {
				filter[j][i] = 1 - LF[j][i];
			}
			else {
				filter[j][i] -= LF[j][i]; 
			}
		}
	} 
	return filter;
}


int main(void) {
	int N = 1;
	int Channel = 3; 
	Mat src = imread("Lenna.png");
	//Mat src = imread("img.jpg");

	Mat MV_RGB = Filtering(src, MovingAverage(N), N, Channel);
	Mat LP_RGB = Filtering(src, Laplacian(N), N, Channel);
	Mat SF_RGB = Filtering(src, SharpeningFilter(N), N, Channel);

	imshow("원본RGB", src);
	imshow("3x3 moving average RGB", MV_RGB);
	imshow("Laplacian RGB", LP_RGB);
	imshow("Sharpening Filter RGB", SF_RGB);
	waitKey(0);

	cvtColor(src, src, COLOR_RGB2GRAY);
	Channel = 1;

	Mat MV_GRAY = Filtering(src, MovingAverage(N), N, Channel);
	Mat LP_GRAY = Filtering(src, Laplacian(N), N, Channel);
	Mat SF_GRAY = Filtering(src, SharpeningFilter(N), N, Channel);

	imshow("원본 GRAY", src);
	imshow("3x3 moving average GRAY", MV_GRAY);
	imshow("Laplacian GRAY", LP_GRAY);
	imshow("Sharpening Filter GRAY", SF_GRAY);
	waitKey(0);
	return 0;
}
