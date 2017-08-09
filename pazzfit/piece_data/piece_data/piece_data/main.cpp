#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, const char* argv[]){
	// 幅320px、高さ240pxで赤色の画像データを生成
	cv::Mat redImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255));

	// 画像表示用のウィンドウを生成
	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);

	// ウィンドウに画像を表示
	cv::imshow("red", redImg);

	// キー入力を待機
	cv::waitKey(0);

	// 作成したウィンドウを全て破棄
	cv::destroyAllWindows();

	return 0;
}
