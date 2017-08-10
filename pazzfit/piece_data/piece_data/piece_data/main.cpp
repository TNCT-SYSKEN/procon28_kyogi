# include "opencv2\opencv.hpp"
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc/imgproc.hpp>
# include <opencv/cvaux.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, const char* argv[]){
	Mat test;
	Mat gray_test;
	Mat bin_test;
	test = imread("img/test001.bmp", 1);
	if (test.data == NULL) {
		return -1;
	}
	//�O���[�X�P�[���ɕϊ�
	cvtColor(test, gray_test, CV_BGR2GRAY);
	//2�l��
	//illigal instruction��opencv3�𓱓����邱�Ƃŉ���(�����s��)
	threshold(gray_test, bin_test, 0, 255, THRESH_BINARY | THRESH_OTSU);
	
	//�k�����ĕ\��
	resize(test, test, Size(), 0.2, 0.2);
	resize(gray_test, gray_test, Size(), 0.2, 0.2);
	resize(bin_test, bin_test, Size(), 0.2, 0.2);
	imshow("hoge", test);
	imshow("fuga", gray_test);
	imshow("piyo", bin_test);

	waitKey(0);

	return 0;
}
