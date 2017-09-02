#include "Control.h"

Control::Control() {
	//ここで画像処理の実行
}

void Control::exe() {
	set_piece();
}

void Control::set_piece() {
	int hoge = 10;
	//テキストを読み込み切り分けてそれぞれpush_backする
	const Rect rect(hoge, hoge, 200, 100);
}