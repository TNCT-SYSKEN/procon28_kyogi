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
	clone_piece = piece;

	//ピース嵌めるアルゴリズムをまとめる
	//枠の基準となる頂点を決定
	for (int i = 0; i < clone_piece.back().point.size();i++) {
		//ピースを一つ決定
		for (int n = 0; n < (clone_piece.size() - 1); ++n) {
			//ピースの角を一つ決定
			for (int k = 0; k < clone_piece[n].angle.size(); ++k) {
				if (/*枠とピースの角度を比較*/) {
					//piece[n].evalution[k].push_back(1);
					if (/*その両端の辺も比較*/) {
						//評価点を追加
					}
				}
				else {
					//評価点に0を追加
				}
			}
		}
		if (/*評価点が高いピースがあるなら正*/) {
			//評価点が高いピースを枠の情報に追加
			//新たな枠の角度と辺を算出して上書き？
			//嵌めたピースの削除
		}
		else {
			break;
		}
		if (/*残りピースが0ならば正*/) {
			//ans_pointへ追加
			break;
		}
		//再帰でsort();を呼び出す(更新した枠の情報を引数として渡す)     
	}
}

void Control::spin_piece() {
	//ピースを90度回転させる
}

void Control::turn_piece() {
	//ピースの頂点情報を受け取る
	//ピースを反転させ、頂点情報を更新

}

bool Control::check_collision(int n) {
	double f_slope, p_slope;
	int f_intercept, p_intercept;
	int count_x = 0, count_y = 0;
	//枠・ピースの頂点を受け取る
	//ピースを配置した時に枠の中に収まっているか判定

	for (int k = 0; k < clone_piece[n].point.size; k++) {
		for (int i = 0; i < clone_piece.back().point.size(); i++) {

			//枠の二つの頂点の直線の一次関数を求める
			//ループの最後になったのなら要素の最後と最初を使用する
			if ((clone_piece.back().point.size - 1) == i) {
				f_slope = (clone_piece.back().point[i].second - clone_piece.back().point[0].second) /
					(clone_piece.back().point[i].first - clone_piece.back().point[0].first);
				f_intercept = clone_piece.back().point[i].second - f_slope * clone_piece.back().point[i].first;
			}
			else {
				f_slope = (clone_piece.back().point[i].second - clone_piece.back().point[i + 1].second) /
					(clone_piece.back().point[i].first - clone_piece.back().point[i + 1].first);
				f_intercept = clone_piece.back().point[i].second - f_slope * clone_piece.back().point[i].first;
			}
			if ((clone_piece[n].point.size - 1) == k) {
				p_slope = (clone_piece[n].point[k].second - clone_piece[n].point[0].second) /
					(clone_piece[n].point[k].first - clone_piece[n].point[0].first);
				p_intercept = clone_piece[n].point[k].second - f_slope * clone_piece[n].point[k].first;
			}
			else if (i == 0) {
				p_slope = (clone_piece[n].point[k].second - clone_piece[n].point[k + 1].second) /
					(clone_piece[n].point[k].first - clone_piece[n].point[k + 1].first);
				p_intercept = clone_piece[n].point[k].second - f_slope * clone_piece[n].point[k].first;
			}

			//ピースの頂点から伸ばした平行線,垂線と枠の各辺とが交わった回数をカウント
			if ((clone_piece[n].point[k].second - f_slope * clone_piece[n].point[k].first - f_intercept) *
				(clone_piece[n].point[k].second - f_slope * 120 - f_intercept) < 0) {
				if ((clone_piece.back().point.size - 1) == i) {
					if ((clone_piece.back().point[i].second - p_slope * clone_piece.back().point[i].first - p_intercept) *
						(clone_piece.back().point[0].second - p_slope * clone_piece.back().point[0].first - p_intercept) < 0) {
						count_x++;
					}
				}
				else {
					if ((clone_piece.back().point[i].second - p_slope * clone_piece.back().point[i].first - p_intercept) *
						(clone_piece.back().point[i + 1].second - p_slope * clone_piece.back().point[i + 1].first - p_intercept) < 0) {
						count_x++;
					}
				}
			}
			if ((clone_piece[n].point[k].second - f_slope * clone_piece[n].point[k].first - f_intercept) *
				(120 - f_slope * clone_piece[n].point[k].second - f_intercept) < 0) {
				if ((clone_piece.back().point.size - 1) == i) {
					if ((clone_piece.back().point[i].second - p_slope * clone_piece.back().point[i].first - p_intercept) *
						(clone_piece.back().point[0].second - p_slope * clone_piece.back().point[0].first - p_intercept) < 0) {
						count_y++;
					}
				}
			}
			//枠の外にピースが出ているならTrueを返す
			if (count_y % 2 == 0 && count_x % 2 == 0) {
				return true;
			}
		}
		count_y = 0;
		count_x = 0;
		//枠の内側にピースが存在するならfalseを返す
		return false;
	}
}

void Control::evaluation() {
	//枠・ピースの頂点・角度・辺の長さを受け取る
	//ピースと枠の評価点を作成
	
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

bool Control::equal_angle(int i,int k) {

}

bool Control::equal_line(int i, int k) {

}

bool Control::equal_point(int frame_point, int piece_point) {

}