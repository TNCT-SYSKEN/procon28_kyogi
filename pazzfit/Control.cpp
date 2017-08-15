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

void Control::fit_piece() {
	//ピース嵌めるアルゴリズムをまとめる
}

void Control::spin_piece() {
	//ピースを90度回転させる
}

void Control::turn_piece() {
	//ピースの頂点情報を受け取る
	//ピースを反転させ、頂点情報を更新
}

void Control::check_collision() {
	//枠・ピースの頂点を受け取る
	//ピースを配置した時に枠の中に収まっているか判定
}

void Control::evaluation() {
	//枠・ピースの頂点・角度・辺の長さを受け取る
	//ピースと枠の評価点を作成

	if (fabs(-1.0) == 1) {
		Rect(10, 10, 20, 20).draw(Palette::White);
	}
}

void Control::union_piece() {
	//二つのピースの角度・辺を受け取る
	//ピース同士の評価点を作成
	//評価点を元にピースを結合
}

void Control::update_frame() {
	//枠・ピースの頂点を受け取る
	//評価点を元にピースの形状情報を枠の形状情報に挿入
}