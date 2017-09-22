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
	//輪郭の頂点座標
	vector<vector<Point> > contours;
	test = imread("img/test001.bmp", 1);
	if (test.data == NULL) {
		return -1;
	}
	//グレースケールに変換
	cvtColor(test, gray_test, CV_BGR2GRAY);
	//2値化
	//illigal instructionはopencv3を導入することで解決(原因不明)
	threshold(gray_test, bin_test, 80, 255, THRESH_TOZERO);
	//bitwise_not(bin_test, bin_test);
	threshold(bin_test, bin_test, 100, 255, THRESH_BINARY);
	//ノイズ除去
	//GaussianBlur(bin_test, bin_test, cv::Size(5, 5), 3);
	//輪郭の取得
	findContours(bin_test, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	//輪郭線の描画
	for (auto contour = contours.begin(); contour != contours.end(); contour++) {
		cv::polylines(test, *contour, true, cv::Scalar(0, 255, 0), 5);
	}

	vector<double> map;
	vector<vector<Point>> app;
	vector<Point> point;
	double max_x = 0, max_y = 0;

	for (auto contour = contours.begin(); contour != contours.end(); contour++) {
		std::vector< cv::Point > approx;

		//輪郭を直線近似する
		cv::approxPolyDP(cv::Mat(*contour), approx, 0.003 * cv::arcLength(*contour, true), true);

		// 近似の面積が一定以上なら取得
		double area = cv::contourArea(approx);

		if (area > 1000.0) {
			map.push_back(area);
			app.push_back(approx);
			cout << approx.size() << endl;
			cout << approx << endl;
			cout << area << endl;
			//青で囲む場合            
			cv::polylines(test, approx, true, cv::Scalar(0, 0, 255), 10);
			std::stringstream sst;
			sst << "area : " << area;
			cv::putText(test, sst.str(), approx[0], CV_FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 128, 0));

			//入力画像に表示する場合
			//cv::drawContours(imgIn, contours, i, CV_RGB(0, 0, 255), 4);
		}
	}

	if (map.size() <= 2) {
		//一つ目が内枠
		if (map[0] < map[1]) {
			for (int i = 0; i < app[0].size(); i++) {
				point.push_back(app[0][i]);
			}
		}
		//二つ目が内枠
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
	//一番大きいx,yの値を探す
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
	//縮小して表示
	resize(test, test, Size(), 0.2, 0.2);
	resize(gray_test, gray_test, Size(), 0.2, 0.2);
	resize(bin_test, bin_test, Size(), 0.2, 0.2);
	imshow("hoge", test);
	imshow("fuga", gray_test);
	imshow("piyo", bin_test);

	cout << contours.size() << endl;

	waitKey(0);
}
