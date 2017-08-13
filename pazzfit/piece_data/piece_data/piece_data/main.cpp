#include "opencv2\opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cvaux.h>
#include <iostream>
#include <vector>

#include "decodeqr.h"
#pragma comment(lib, "WS2_32.LIB")
#pragma comment(lib, "libdecodeqr.lib")

using namespace std;
using namespace cv;

int piece();

void qr_read();

int main(int argc, const char* argv[]){
	//piece();

	qr_read();

	Mat test;
	test = imread("img/test001.bmp", 1);
	imshow("hoge", test);

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

	for (auto contour = contours.begin(); contour != contours.end(); contour++) {
		std::vector< cv::Point > approx;

		//輪郭を直線近似する
		cv::approxPolyDP(cv::Mat(*contour), approx, 0.003 * cv::arcLength(*contour, true), true);

		// 近似の面積が一定以上なら取得
		double area = cv::contourArea(approx);

		if (area > 1000.0) {
			cout << approx.size() << endl;
			cout << approx << endl;
			cout << area << endl;
			//青で囲む場合            
			cv::polylines(test, approx, true, cv::Scalar(255, 0, 0), 10);
			std::stringstream sst;
			sst << "area : " << area;
			cv::putText(test, sst.str(), approx[0], CV_FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 128, 0));

			//入力画像に表示する場合
			//cv::drawContours(imgIn, contours, i, CV_RGB(0, 0, 255), 4);

		}
	}
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

void qr_read() {
	//画像を保持する変数
	IplImage* qr;
	//libdecodeqrを使うためのハンドル
	QrDecoderHandle decoder = qr_decoder_open();
	//画像のロード
	qr = cvLoadImage("img/fgo_test.png", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	qr_decoder_set_image_buffer(decoder, qr); // 画像をセット
	if (!qr_decoder_is_busy(decoder)){
		int adaptive_th_size = 25;
		int adaptive_th_delta = 10;
		short stat = qr_decoder_decode(decoder, adaptive_th_size, adaptive_th_delta);

		for (adaptive_th_size = 25, stat = 0; (adaptive_th_size >= 3) && ((stat & QR_IMAGEREADER_DECODED) == 0); adaptive_th_size -= 2) {
			stat = qr_decoder_decode(decoder, adaptive_th_size, adaptive_th_delta);
		}
	}

	int text_size = 0;
	unsigned char* text = new unsigned char[text_size];
	QrCodeHeader header;
	// デコード
	if (qr_decoder_get_header(decoder, &header)){
		if (text_size < header.byte_size + 1){
			if (text) delete[] text;
			text_size = header.byte_size + 1;
			text = new unsigned char[text_size];
		}
		qr_decoder_get_body(decoder, text, text_size); // ここでtextにデコード結果が保存される
	}
	/*//qrの画像をハンドルにセット
	qr_decoder_set_image_buffer(decoder, qr);
	//デコードする
	qr_decoder_get_header(decoder, &header);
	//必要な配列の数の取得
	if (text_size < header.byte_size + 1) {
		text_size = header.byte_size + 1;
	}
	//配列の確保
	text = new unsigned char[text_size];*/
	//デコード結果出力
	qr_decoder_get_body(decoder, text, text_size);
	cout << text << endl;
	cout << text_size << endl;
	//終了、メモリ開放
	qr_decoder_close(decoder);
}
