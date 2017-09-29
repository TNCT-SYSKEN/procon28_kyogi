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
	Mat po;
	Mat test;
	Mat gray_test;
	Mat bin_test;
	for (int j = 1;; j++) {
		//�֊s�̒��_���W
		vector<vector<Point> > contours;
		ostringstream oss;
		oss << "img/test00" << j << ".bmp";
		po = imread(oss.str(), 1);
		if (po.data == NULL) {
			break;
		}
		test = imread(oss.str(), 1);
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
	//���낦����l���`����ɂ����f�[�^
	vector<vector<pair<double,double>>> clone_piece;
	vector<vector<Point>> shape_piece;
	vector<Point> shape_frame;
	double max_x = 0, max_y = 0;
	int x, y;
	Point hoge;
	//�g������ɂ��킹��
	for (int i = 0; i < frame.size(); i++) {
		if (i == 0) {
			x = frame[0].x;
			y = frame[0].y;
			hoge.x = 0;
			hoge.y = 0;
			shape_frame.push_back(hoge);
		}
		else {
			hoge.x = frame[i].x - x;
			hoge.y = frame[i].y - y;
			shape_frame.push_back(hoge);
		}
	}
	//clone_piece��piece�̃f�[�^���R�s�[
	for (int i = 0; i < piece.size(); i++) {
		vector<pair<double, double>> hoge;
		clone_piece.push_back(hoge);
		for (int j = 0; j < piece[i].size(); j++) {
			pair<double, double> fuga = { piece[i][j].x,piece[i][j].x };
			clone_piece[i].push_back(fuga);
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

	//�ȂȂ߂ɂȂ��Ă���s�[�X���O���b�h�ɏ悹��
	for (int i = 0; i < piece.size(); i++) {
		int x;
		int y;
		//����ɐ}�`�𓮂���
		for (int j = 0; j < clone_piece[i].size(); j++) {
			if (j == 0) {
				x = clone_piece[i][0].first;
				y = clone_piece[i][0].second;
				clone_piece[i][0].first = 0;
				clone_piece[i][0].second = 0;
			}
			else {
				clone_piece[i][j].first -= x;
				clone_piece[i][j].second -= y;
			}
		}
		int error = 100, angle;
		for (int j = 1; j <= 360; j++) {
			double error_test = 0;
			//j�x�����}�`����]������
			//��]�s����|�����킹��
			for (int k = 0; k < clone_piece[i].size(); k++) {
				clone_piece[i][k].first = clone_piece[i][k].first * cos(j) - clone_piece[i][k].second * sin(j);
				clone_piece[i][k].second = clone_piece[i][k].first * sin(j) + clone_piece[i][k].second * cos(j);
				error_test += abs(fmod(clone_piece[i][k].first,max_x) + fmod(clone_piece[i][k].second, max_y));
			}
			//�l�����ɖ߂�
			for (int k = 0; k < clone_piece[i].size(); k++) {
				clone_piece[i][k].first = piece[i][k].x;
				clone_piece[i][k].second = piece[i][k].y;
			}
			//����ɐ}�`�𓮂���
			for (int k = 0; k < clone_piece[i].size(); k++) {
				if (k == 0) {
					x = clone_piece[i][0].first;
					y = clone_piece[i][0].second;
					clone_piece[i][0].first = 0;
					clone_piece[i][0].second = 0;
				}
				else {
					clone_piece[i][k].first -= x;
					clone_piece[i][k].second -= y;
				}
			}
			//�덷�������Ƃ������������p�x��ۑ����Ă���
			if (error > error_test / clone_piece[i].size()) {
				angle = j;
			}
		}
		//�����Ƃ������������p�x�Ɉړ�������
		for (int k = 0; k < clone_piece[i].size(); k++) {
			clone_piece[i][k].first = clone_piece[i][k].first * cos(angle) - clone_piece[i][k].second * sin(angle);
			clone_piece[i][k].second = clone_piece[i][k].first * sin(angle) + clone_piece[i][k].second * cos(angle);
		}
		double minus_x = 0, minus_y = 0;
		//�ł��傫�����̒l��T��
		for (int k = 0; k < clone_piece[i].size(); k++) {
			if (clone_piece[i][k].first < minus_x) {
				minus_x = clone_piece[i][k].first;
			}
			if (clone_piece[i][k].second < minus_y) {
				minus_y = clone_piece[i][k].second;
			}
		}
		//���̒l������΂��炷
		if (minus_x != 0 || minus_y != 0) {
			for (int k = 0; k < clone_piece[i].size(); k++) {
				clone_piece[i][k].first += abs(minus_x);
				clone_piece[i][k].second += abs(minus_y);
			}
		}
	}
	cout << clone_piece[0][0].first << endl;
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

	//waitKey(0);
}
