#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, const char* argv[]){
	// ��320px�A����240px�ŐԐF�̉摜�f�[�^�𐶐�
	cv::Mat redImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255));

	// �摜�\���p�̃E�B���h�E�𐶐�
	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);

	// �E�B���h�E�ɉ摜��\��
	cv::imshow("red", redImg);

	// �L�[���͂�ҋ@
	cv::waitKey(0);

	// �쐬�����E�B���h�E��S�Ĕj��
	cv::destroyAllWindows();

	return 0;
}
