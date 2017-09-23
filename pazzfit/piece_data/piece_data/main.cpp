#include "opencv2\opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cvaux.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void piece();

int main(int argc, const char* argv[]) {

	piece();

	cv::Mat redImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255));

	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);

	cv::imshow("red", redImg);

	waitKey(0);

	return 0;
}

void piece() {
	//�g�ƃs�[�X�ł��낤�l���i�[���Ƃ�
	vector<Point> frame;
	vector<vector<Point>> piece;
	Mat test;
	Mat gray_test;
	Mat bin_test;
	for (int j = 1;; j++) {
		//�֊s�̒��_���W
		vector<vector<Point> > contours;
		ostringstream oss;
		oss << "img/test00" << j << ".bmp";
		test = imread(oss.str(), 1);
		if (test.data == NULL) {
			break;
		}
		//�O���[�X�P�[���ɕϊ�
		cvtColor(test, gray_test, CV_BGR2GRAY);
		//2�l��
		//illigal instruction��opencv3�𓱓����邱�Ƃŉ���(�����s��)
		threshold(gray_test, bin_test, 80, 255, THRESH_TOZERO);
		//bitwise_not(bin_test, bin_test);
		threshold(bin_test, bin_test, 100, 255, THRESH_BINARY);
		//�m�C�Y����
		//GaussianBlur(bin_test, bin_test, cv::Size(5, 5), 3);
		//�֊s�̎擾
		findContours(bin_test, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
		//�֊s���̕`��
		for (auto contour = contours.begin(); contour != contours.end(); contour++) {
			cv::polylines(test, *contour, true, cv::Scalar(0, 255, 0), 5);
		}

		vector<double> map;
		vector<vector<Point>> app;

		for (auto contour = contours.begin(); contour != contours.end(); contour++) {
			std::vector< cv::Point > approx;

			//�֊s�𒼐��ߎ�����
			cv::approxPolyDP(cv::Mat(*contour), approx, 0.003 * cv::arcLength(*contour, true), true);

			// �ߎ��̖ʐς����ȏ�Ȃ�擾
			double area = cv::contourArea(approx);

			if (area > 1000.0) {
				map.push_back(area);
				app.push_back(approx);
				cout << approx.size() << endl;
				cout << approx << endl;
				cout << area << endl;
				//�ň͂ޏꍇ            
				cv::polylines(test, approx, true, cv::Scalar(0, 0, 255), 10);
				std::stringstream sst;
				sst << "area : " << area;
				cv::putText(test, sst.str(), approx[0], CV_FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 128, 0));

				//���͉摜�ɕ\������ꍇ
				//cv::drawContours(imgIn, contours, i, CV_RGB(0, 0, 255), 4);
			}
		}
		//�g�̎�
		if (map.size() <= 2) {
			//��ڂ����g
			if (map[0] < map[1]) {
				for (int i = 0; i < app[0].size(); i++) {
					frame.push_back(app[0][i]);
				}
			}
			//��ڂ����g
			else {
				for (int i = 0; i < app[1].size(); i++) {
					frame.push_back(app[1][i]);
				}
			}
		}
		//�s�[�X�̎�
		else {
			for (int i = 0; i < app.size(); i++) {
				piece.push_back(app[i]);
			}
		}
	}
//-----------�����܂Ń��[�v-----------//
	double max_x = 0, max_y = 0;
	int x, y;
	for (int i = 0; i < frame.size(); i++) {
		if (i == 0) {
			x = frame[0].x;
			y = frame[0].y;
			frame[0].x = 0;
			frame[0].y = 0;
		}
		else {
			frame[i].x -= x;
			frame[i].y -= y;
		}
	}
	//��ԑ傫��x,y�̒l��T��
	for (int i = 0; i < frame.size(); i++) {
		if (frame[i].x >= max_x) {
			max_x = frame[i].x;
		}
		if (frame[i].y >= max_y) {
			max_y = frame[i].y;
		}
	}
	max_x /= 64;
	max_y /= 100;
	for (int i = 0; i < frame.size();i++) {
		frame[i].x /= max_x;
		frame[i].y /= max_y;
	}
	for (int i = 0; i < piece.size(); i++) {
		for (int j = 0; j < piece[i].size(); j++) {
			piece[i][j].x /= max_x;
			piece[i][j].y /= max_y;
		}
	}
	cout << frame.size() << endl;
	cout << piece.size() << endl;

	//�k�����ĕ\��
	resize(test, test, Size(), 0.5, 0.5);
	resize(gray_test, gray_test, Size(), 0.2, 0.2);
	resize(bin_test, bin_test, Size(), 0.2, 0.2);
	imshow("hoge", test);
	imshow("fuga", gray_test);
	imshow("piyo", bin_test);

	waitKey(0);
}
