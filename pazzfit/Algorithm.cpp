#include "Algorithm.h"

void Algorithm::fit_piece() {

}

void Algorithm::spin90_piece(int n) {
	/*
	ピースを90度左回転させる
	*/
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].first = cont.piece[n].point[i].first * (-1);
	}
}

void Algorithm::spin180_piece(int n) {
	/*
	ピースを180度左回転させる
	*/
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].first = cont.piece[n].point[i].first * (-1);
		cont.clone_piece[n].point[i].second = cont.piece[n].point[i].second * (-1);
	}
}

void Algorithm::spin270_piece(int n) {
	/*
	ピースを270度左回転させる
	*/
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].second = cont.piece[n].point[i].second * (-1);
	}
}

void Algorithm::turn_piece(int n) {
	/*
	ピースの番号を受け取る
	ピースを反転させ、頂点情報を更新
	axis一番X座標の小さい値が入ってる要素数
	*/
	int mini_point_x = 100, axis;
	int minus = 0;

	//基準となる座標の決定
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		if (mini_point_x > cont.clone_piece[n].point[i].first) {
			mini_point_x = cont.clone_piece[n].point[i].first;
			axis = i;
		}
	}

	//反転
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].first = cont.clone_piece[n].point[axis].first -
			(cont.clone_piece[n].point[i].first - cont.clone_piece[n].point[axis].first);
	}

	//マイナス座標の修正
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		if (abs((cont.clone_piece[n].point[i].first - cont.clone_piece[n].point[axis].first)) > minus) {
			minus = abs((cont.clone_piece[n].point[i].first - cont.clone_piece[n].point[axis].first));
		}
	}
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].first += minus;
	}
}

bool Algorithm::check_collision(int n) {
	double f_slope, p_slope;
	int f_intercept, p_intercept;
	int count_x = 0, count_y = 0;
	/*
	枠・ピースの頂点を受け取る
	ピースを配置した時に枠の中に収まっているか判定
	n-ピースの番号,k-ピースの各頂点,i-枠の各頂点
	*/
	for (int k = 0; k < int(cont.clone_piece[n].point.size()); k++) {
		for (int i = 0; i < int(cont.clone_piece.back().point.size()); i++) {

			//枠の二つの頂点の直線の一次関数を求める
			//ループの最後になったのなら要素の最後と最初を使用する
			if ((int(cont.clone_piece.back().point.size()) - 1) == i) {
				f_slope = (cont.clone_piece.back().point[i].second - cont.clone_piece.back().point[0].second) /
					(cont.clone_piece.back().point[i].first - cont.clone_piece.back().point[0].first);
				f_intercept = cont.clone_piece.back().point[i].second - f_slope * cont.clone_piece.back().point[i].first;
			}
			else {
				f_slope = (cont.clone_piece.back().point[i].second - cont.clone_piece.back().point[i + 1].second) /
					(cont.clone_piece.back().point[i].first - cont.clone_piece.back().point[i + 1].first);
				f_intercept = cont.clone_piece.back().point[i].second - f_slope * cont.clone_piece.back().point[i].first;
			}
			//ピースの二つの頂点の一次関数を求める
			if ((int(cont.clone_piece[n].point.size()) - 1) == k) {
				p_slope = (cont.clone_piece[n].point[k].second - cont.clone_piece[n].point[0].second) /
					(cont.clone_piece[n].point[k].first - cont.clone_piece[n].point[0].first);
				p_intercept = cont.clone_piece[n].point[k].second - f_slope * cont.clone_piece[n].point[k].first;
			}
			else if (i == 0) {
				p_slope = (cont.clone_piece[n].point[k].second - cont.clone_piece[n].point[k + 1].second) /
					(cont.clone_piece[n].point[k].first - cont.clone_piece[n].point[k + 1].first);
				p_intercept = cont.clone_piece[n].point[k].second - f_slope * cont.clone_piece[n].point[k].first;
			}

			//ピースの頂点から伸ばした平行線,垂線と枠の各辺とが交わった回数をカウント
			if ((cont.clone_piece[n].point[k].second - f_slope * cont.clone_piece[n].point[k].first - f_intercept) *
				(cont.clone_piece[n].point[k].second - f_slope * 120 - f_intercept) < 0) {
				if ((int(cont.clone_piece.back().point.size()) - 1) == i) {
					if ((cont.clone_piece.back().point[i].second - p_slope * cont.clone_piece.back().point[i].first - p_intercept) *
						(cont.clone_piece.back().point[0].second - p_slope * cont.clone_piece.back().point[0].first - p_intercept) < 0) {
						count_x++;
					}
				}
				else {
					if ((cont.clone_piece.back().point[i].second - p_slope * cont.clone_piece.back().point[i].first - p_intercept) *
						(cont.clone_piece.back().point[i + 1].second - p_slope * cont.clone_piece.back().point[i + 1].first - p_intercept) < 0) {
						count_x++;
					}
				}
			}
			if ((cont.clone_piece[n].point[k].second - f_slope * cont.clone_piece[n].point[k].first - f_intercept) *
				(120 - f_slope * cont.clone_piece[n].point[k].second - f_intercept) < 0) {
				if ((int(cont.clone_piece.back().point.size()) - 1) == i) {
					if ((cont.clone_piece.back().point[i].second - p_slope * cont.clone_piece.back().point[i].first - p_intercept) *
						(cont.clone_piece.back().point[0].second - p_slope * cont.clone_piece.back().point[0].first - p_intercept) < 0) {
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

void Algorithm::evaluation() {
	//枠・ピースの頂点・角度・辺の長さを受け取る
	//ピースと枠の評価点を作成

}

void Algorithm::union_piece() {
	//二つのピースの角度・辺を受け取る
	//ピース同士の評価点を作成
	//評価点を元にピースを結合
}

void Algorithm::update_frame() {
	//枠・ピースの頂点を受け取る
	//評価点を元にピースの形状情報を枠の形状情報に挿入
}

bool Algorithm::equal_angle(int first_angle, int second_angle) {
	/*
	枠とピースの角度の情報を受け取る
	もし誤差の範囲内で等しいならばTrue
	*/
	if (fabs(first_angle - second_angle) <= 0.50) {
		return true;
	}
	else {
		return true;
	}
	return true;
}

bool Algorithm::equal_line(double first_line, double second_line) {
	/*
	枠とピースの辺情報を受け取る
	もし誤差の範囲内で等しいならばTrue
	*/ 
	
	if (fabs(first_line - second_line) <= 0.50) {
		return true;
	}
	else {
		return true;
	}
}

bool Algorithm::equal_point(int first_point, int second_point) {
	/*
	枠とピ―スの頂点座標を受け取る
	もし頂点座標が同じならばTrueを返す
	*/
	if (first_point == second_point) {
		return true;
	}
	else {
		return false;
	}
}