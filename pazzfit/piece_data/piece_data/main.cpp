#include "opencv2\opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cvaux.h>
#include <iostream>
#include <vector>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

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
	//枠とピースであろう値を格納しとく
	vector<Point> frame;
	vector<vector<Point>> piece;
	Mat po;
	Mat test;
	Mat gray_test;
	Mat bin_test;
	for (int j = 1;; j++) {
		//輪郭の頂点座標
		vector<vector<Point> > contours;
		ostringstream oss;
		oss << "img/test00" << j << ".bmp";
		po = imread(oss.str(), 1);
		if (po.data == NULL) {
			break;
		}
		test = imread(oss.str(), 1);
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
		//枠の時
		if (map.size() <= 2) {
			//一つ目が内枠
			if (map[0] < map[1]) {
				for (int i = 0; i < app[0].size(); i++) {
					frame.push_back(app[0][i]);
				}
			}
			//二つ目が内枠
			else {
				for (int i = 0; i < app[1].size(); i++) {
					frame.push_back(app[1][i]);
				}
			}
		}
		//ピースの時
		else {
			for (int i = 0; i < app.size(); i++) {
				piece.push_back(app[i]);
			}
		}
	}
//-----------ここまでループ-----------//
	//そろえたり値を形状情報にしたデータ
	vector<vector<pair<double,double>>> clone_piece;
	vector<vector<Point>> shape_piece;
	vector<Point> shape_frame;
	double max_x = 0, max_y = 0;
	double min_x = 10000,min_y = 10000;
	int x, y;
	Point hoge;
	//枠を左上にあわせる
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

	//明らかにおかしい頂点を取り除く
	for (int i = 0; i < piece.size(); i++) {
		for (int j = 0; j < piece[i].size(); j++) {
			//うしろの頂点のx,y座標がそれぞれ+-30の間にある(めっちゃ近い)
			if (piece[i][j].x <= piece[i][(j + 1) % piece[i].size()].x + 30 && piece[i][j].x >= piece[i][(j + 1) % piece[i].size()].x - 30) {
				if (piece[i][j].y <= piece[i][(j + 1) % piece[i].size()].y + 30 && piece[i][j].y >= piece[i][(j + 1) % piece[i].size()].y - 30) {
					//合体させる
					piece[i][j].x = (piece[i][j].x + piece[i][(j + 1) % piece[i].size()].x) / 2;
					piece[i][j].y = (piece[i][j].y + piece[i][(j + 1) % piece[i].size()].y) / 2;
					piece[i].erase(piece[i].begin() + j);
					//探索をはじめに戻す
					j = -1;
				}
			}
		}
	}
	//clone_pieceにpieceのデータをコピー
	for (int i = 0; i < piece.size(); i++) {
		vector<pair<double, double>> hoge;
		clone_piece.push_back(hoge);
		for (int j = 0; j < piece[i].size(); j++) {
			pair<double, double> fuga = { piece[i][j].x,piece[i][j].y };
			clone_piece[i].push_back(fuga);
		}
	}

	//一番大きいx,yの値を探す
	for (int i = 0; i < frame.size(); i++) {
		if (frame[i].x >= max_x) {
			max_x = frame[i].x;
		}
		if (frame[i].y >= max_y) {
			max_y = frame[i].y;
		}
		if (frame[i].x <= min_x) {
			min_x = frame[i].x;
		}
		if (frame[i].y <= min_y) {
			min_y = frame[i].y;
		}
	}
	max_x = (max_x - min_x) / 64;
	max_y = (max_y - min_y) / 100;

	//ななめになっているピースをグリッドに乗せる
	for (int i = 0; i < piece.size(); i++) {
		int x;
		int y;
		//左上に図形を動かす
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
		for (double j = 1.0; j <= 360; j += 0.1) {
			double error_test = 0;
			//j度だけ図形を回転させる
			//回転行列を掛け合わせる
			for (int k = 0; k < clone_piece[i].size(); k++) {
				double first = clone_piece[i][k].first;
				double second = clone_piece[i][k].second;
				clone_piece[i][k].first = first * cos(j * (M_PI/180)) + second * sin(j * (M_PI/180));
				clone_piece[i][k].second = first * sin(j * (M_PI/180)) - second * cos(j * (M_PI/180));
				error_test += abs(fmod(clone_piece[i][k].first,max_x) + fmod(clone_piece[i][k].second, max_y));
			}
			/*
			Mat mamama(cv::Size(1000, 1000), CV_8UC3, cv::Scalar(0, 0, 0));
			vector<Point> nanana;
			for (int k = 0; k < clone_piece[i].size(); k++) {
				Point ho;
				ho.x = round(clone_piece[i][k].first + 500);
				ho.y = round(clone_piece[i][k].second + 500);
				nanana.push_back(ho);
			}
			cv::polylines(mamama, nanana, true, cv::Scalar(0, 0, 255), 3);
			imshow("test", mamama);
			waitKey();
			*/
			//値を元に戻す
			for (int k = 0; k < clone_piece[i].size(); k++) {
				clone_piece[i][k].first = piece[i][k].x;
				clone_piece[i][k].second = piece[i][k].y;
			}
			//左上に図形を動かす
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
			//誤差がもっとも小さかった角度を保存しておく
			if (error > error_test / clone_piece[i].size()) {
				angle = j;
			}
		}
		//もっとも小さかった角度に移動させる
		for (int k = 0; k < clone_piece[i].size(); k++) {
			double first = clone_piece[i][k].first;
			double second = clone_piece[i][k].second;
			clone_piece[i][k].first = first * cos(angle * (M_PI / 180)) + second * sin(angle * (M_PI / 180));
			clone_piece[i][k].second = first * sin(angle * (M_PI / 180)) - second * cos(angle * (M_PI / 180));
		}
		double minus_x = 0, minus_y = 0;
		//最も大きい負の値を探す
		for (int k = 0; k < clone_piece[i].size(); k++) {
			if (clone_piece[i][k].first < minus_x) {
				minus_x = clone_piece[i][k].first;
			}
			if (clone_piece[i][k].second < minus_y) {
				minus_y = clone_piece[i][k].second;
			}
		}
		//負の値があればずらす
		if (minus_x != 0 || minus_y != 0) {
			for (int k = 0; k < clone_piece[i].size(); k++) {
				clone_piece[i][k].first += abs(minus_x);
				clone_piece[i][k].second += abs(minus_y);
			}
		}
	}

	//値を近似して整数に戻す/pieceを置き換える
	for (int i = 0; i < clone_piece.size(); i++) {
		for (int j = 0; j < clone_piece[i].size(); j++) {
			piece[i][j].x = round(clone_piece[i][j].first) + i % 5 * 600;
			piece[i][j].y = round(clone_piece[i][j].second) + i / 5 * 600;
		}
	}
	//にゃんぱす～を用意
	Mat test_draw(cv::Size(4000, 6000), CV_8UC3, cv::Scalar(0, 0, 0));
	for (int i = 0; i < piece.size(); i++) {
		cv::polylines(test_draw, piece[i], true, cv::Scalar(0, 0, 255), 8);
	}
	cout << piece[0][0].x << endl;
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

	//テキストにピースデータを書き起こす
	ofstream output("image_shape.txt");
	if (!output) {
		cout << "data error" << endl;
	}
	output << piece.size() + 1 << ":";
	for (int i = 0; i < piece.size(); i++) {
		output << piece[i].size() << " ";
		for (int j = 0; j < piece[i].size(); j++) {
			output << piece[i][j].x << " ";
			output << piece[i][j].y;
			if (j == piece[i].size() - 1) {
				output << ":";
			}
			else {
				output << " ";
			}
		}
	}
	output << frame.size() << " ";
	for (int i = 0; i < frame.size(); i++) {
		output << frame[i].x << " ";
		output << frame[i].y;
		if (i != frame.size() - 1) {
			output << " ";
		}
	}
	output.close();
	cout << frame.size() << endl;
	cout << piece.size() << endl;

	//縮小して表示
	resize(test, test, Size(), 0.2, 0.2);
	resize(gray_test, gray_test, Size(), 0.2, 0.2);
	resize(bin_test, bin_test, Size(), 0.2, 0.2);
	resize(test_draw, test_draw, Size(), 0.2, 0.2);
	imshow("test", test_draw);
	imshow("hoge", test);
	imshow("fuga", gray_test);
	imshow("piyo", bin_test);

	//waitKey(0);
}
