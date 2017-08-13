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
	//�֊s�̒��_���W
	vector<vector<Point> > contours;
	test = imread("img/test001.bmp", 1);
	if (test.data == NULL) {
		return -1;
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

	for (auto contour = contours.begin(); contour != contours.end(); contour++) {
		std::vector< cv::Point > approx;

		//�֊s�𒼐��ߎ�����
		cv::approxPolyDP(cv::Mat(*contour), approx, 0.003 * cv::arcLength(*contour, true), true);

		// �ߎ��̖ʐς����ȏ�Ȃ�擾
		double area = cv::contourArea(approx);

		if (area > 1000.0) {
			cout << approx.size() << endl;
			cout << approx << endl;
			cout << area << endl;
			//�ň͂ޏꍇ            
			cv::polylines(test, approx, true, cv::Scalar(255, 0, 0), 10);
			std::stringstream sst;
			sst << "area : " << area;
			cv::putText(test, sst.str(), approx[0], CV_FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0, 128, 0));

			//���͉摜�ɕ\������ꍇ
			//cv::drawContours(imgIn, contours, i, CV_RGB(0, 0, 255), 4);

		}
	}
	//�k�����ĕ\��
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
	//�摜��ێ�����ϐ�
	IplImage* qr;
	//libdecodeqr���g�����߂̃n���h��
	QrDecoderHandle decoder = qr_decoder_open();
	//�摜�̃��[�h
	qr = cvLoadImage("img/fgo_test.png", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	qr_decoder_set_image_buffer(decoder, qr); // �摜���Z�b�g
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
	// �f�R�[�h
	if (qr_decoder_get_header(decoder, &header)){
		if (text_size < header.byte_size + 1){
			if (text) delete[] text;
			text_size = header.byte_size + 1;
			text = new unsigned char[text_size];
		}
		qr_decoder_get_body(decoder, text, text_size); // ������text�Ƀf�R�[�h���ʂ��ۑ������
	}
	/*//qr�̉摜���n���h���ɃZ�b�g
	qr_decoder_set_image_buffer(decoder, qr);
	//�f�R�[�h����
	qr_decoder_get_header(decoder, &header);
	//�K�v�Ȕz��̐��̎擾
	if (text_size < header.byte_size + 1) {
		text_size = header.byte_size + 1;
	}
	//�z��̊m��
	text = new unsigned char[text_size];*/
	//�f�R�[�h���ʏo��
	qr_decoder_get_body(decoder, text, text_size);
	cout << text << endl;
	cout << text_size << endl;
	//�I���A�������J��
	qr_decoder_close(decoder);
}
