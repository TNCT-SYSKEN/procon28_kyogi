#include "opencv2\opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cvaux.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int piece();

int main(int argc, const char* argv[]) {

	piece();

	cv::Mat redImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255));

	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);

	cv::imshow("red", redImg);

	waitKey(0);

	return 0;
}

int piece() {
	Mat test;
	Mat gray_test;
	Mat bin_test;
	//—ÖŠs‚Ì’¸“_À•W
	vector<vector<Point> > contours;
	test = imread("img/test001.bmp", 1);
	if (test.data == NULL) {
		return -1;
	}
	//ƒOƒŒ[ƒXƒP[ƒ‹‚É•ÏŠ·
	cvtColor(test, gray_test, CV_BGR2GRAY);
	//2’l‰»
	//illigal instruction‚Íopencv3‚ğ“±“ü‚·‚é‚±‚Æ‚Å‰ğŒˆ(Œ´ˆö•s–¾)
	threshold(gray_test, bin_test, 80, 255, THRESH_TOZERO);
	//bitwise_not(bin_test, bin_test);
	threshold(bin_test, bin_test, 100, 255, THRESH_BINARY);
	//ƒmƒCƒYœ‹
	//GaussianBlur(bin_test, bin_test, cv::Size(5, 5), 3);
	//—ÖŠs‚Ìæ“¾
	findContours(bin_test, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	//—ÖŠsü‚Ì•`‰æ
	for (auto contour = contours.begin(); contour != contours.end(); contour++) {
		cv::polylines(test, *contour, true, cv::Scalar(0, 255, 0), 5);
	}

	vector<double> map;
	vector<vector<Point>> app;
	vector<Point> point;
	double max_x = 0, max_y = 0;

	for (auto contour = contours.begin(); contour != contours.end(); contour++) {
		std::vector< cv::Point > approx;

		//—ÖŠs‚ğ’¼ü‹ß—‚·‚é
		cv::approxPolyDP(cv::Mat(*contour), approx, 0.003 * cv::arcLength(*contour, true), true);

		// ‹ß—‚Ì–ÊÏ‚ªˆê’èˆÈã‚È‚çæ“¾
		double area = cv::contourArea(approx);

		if (area > 1000.0) {
			map.push_back(area);
			app.push_back(approx);
			cout << approx.size() << endl;
			cout << approx << endl;
			cout << area << endl;
			//Â‚ÅˆÍ‚Şê‡            
			cv::polylines(test, approx, true, cv::Scalar(0, 0, 255), 10);
			std::stringstream sst;
			sst << "area : " << area;
			cv::putText(test, sst.str(), approx[0], CV_FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 128, 0));

			//“ü—Í‰æ‘œ‚É•\¦‚·‚éê‡
			//cv::drawContours(imgIn, contours, i, CV_RGB(0, 0, 255), 4);
		}
	}

	if (map.size() <= 2) {
		//ˆê‚Â–Ú‚ª“à˜g
		if (map[0] < map[1]) {
			for (int i = 0; i < app[0].size(); i++) {
				point.push_back(app[0][i]);
			}
		}
		//“ñ‚Â–Ú‚ª“à˜g
		else {
			for (int i = 0; i < app[1].size(); i++) {
				point.push_back(app[1][i]);
			}
		}
	}

	int x, y;
	for (int i = 0; i < point.size(); i++) {
		if (i == 0) {
			x = point[0].x;
			y = point[0].y;
			point[0].x = 0;
			point[0].y = 0;
		}
		else {
			point[i].x -= x;
			point[i].y -= y;
		}
	}
	//ˆê”Ô‘å‚«‚¢x,y‚Ì’l‚ğ’T‚·
	for (int i = 0; i < point.size(); i++) {
		if (point[i].x >= max_x) {
			max_x = point[i].x;
		}
		if (point[i].y >= max_y) {
			max_y = point[i].y;
		}
	}
	max_x /= 64;
	max_y /= 100;
	for (int i = 0; i < point.size();i++) {
		point[i].x /= max_x;
		point[i].y /= max_y;
	}
	cout << point.size() << endl;
	//k¬‚µ‚Ä•\¦
	resize(test, test, Size(), 0.2, 0.2);
	resize(gray_test, gray_test, Size(), 0.2, 0.2);
	resize(bin_test, bin_test, Size(), 0.2, 0.2);
	imshow("hoge", test);
	imshow("fuga", gray_test);
	imshow("piyo", bin_test);

	cout << contours.size() << endl;

	waitKey(0);
}
