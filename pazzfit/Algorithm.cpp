#include "Algorithm.h"

Algorithm::Algorithm() {
	clone_piece = cont.piece;
	init();
}

void Algorithm::init() {
	flag = -1;
	three_evalution.clear();
}

void Algorithm::fit_piece() {
	flag++;
	//ピース嵌めるアルゴリズムをまとめる
	//枠の基準となる頂点を決定
	for (int i = 0; i < clone_piece.back().point.size(); i++) {
		evaluation(i);
		select_piece(i);
		if (flag == 0) {
			init();
		}
	}
	//更新した枠で嵌まらなかった場合、ピース・枠を一つ再帰前のものを代入する
	flag--;
}

void Algorithm::evaluation(int i) {
	//枠・ピースの頂点・角度・辺の長さを受け取る
	//ピースと枠の評価点を作成
	//ピースを一つ決定
	for (int n = 0; n < (clone_piece.size()); n++) {
		//ピースの角(頂点)を一つ決定
		for (int k = 0; k < clone_piece[n].angle.size(); k++) {
			//枠とピースの角度を比較
			one_evalution.push_back(0);
			if (equal_angle(clone_piece.back().angle[i], clone_piece[n].angle[k])) {
				one_evalution[k] = 1;
				//その両端の辺も比較
				if (k == 0) {
					if (equal_line(clone_piece.back().line[i], clone_piece[n].line.back())) {
						one_evalution[k] += 1;
					}
					else if(equal_line(clone_piece.back().line[i], clone_piece[n].line[k])){
						one_evalution[k] += 1;
					}
					if (equal_line(clone_piece.back().line.back(), clone_piece[n].line.back())) {
						one_evalution[k] += 1;
					}
					else if (equal_line(clone_piece.back().line[i], clone_piece[n].line[k])) {
						one_evalution[k] += 1;
					}
				}
				else {
					if (equal_line(clone_piece.back().line[i], clone_piece[n].line[k - 1])) {
						one_evalution[k] += 1;
					}
					else if (equal_line(clone_piece.back().line[i], clone_piece[n].line[k])) {
						one_evalution[k] += 1;
					}
					if (equal_line(clone_piece.back().line.back(), clone_piece[n].line[k - 1])) {
						one_evalution[k] += 1;
					}
					else if (equal_line(clone_piece.back().line[i], clone_piece[n].line[k])) {
						one_evalution[k] += 1;
					}
				}
			}
			else {
				one_evalution[k] = 0;
			}
			two_evalution.push_back(one_evalution);
		}
	}
	three_evalution.push_back(two_evalution);
}

void Algorithm::union_piece() {
	//二つのピースの角度・辺を受け取る
	//ピース同士の評価点を作成
	//評価点を元にピースを結合
}

bool Algorithm::update_frame(int n ,int i) {
	vector<Piece> give_piece = clone_piece;
	int piece_symbol = 0;
	int frame_symbol = 0;
	int se_count = 0;
	//ピースの番号を受け取る
	//回転,反転,あたり判定によって当てはまるか判定
	//ピースの頂点情報を枠の頂点情報に挿入
	
	//ans_pointへの代入
	clone_piece[n].ans_point = clone_piece[n].point;
	//基準を求める
	for (int k = 0; k < clone_piece[n].angle.size(); k++) {
		if (clone_piece.back().point[i].first == clone_piece[n].point[k].first && clone_piece.back().point[i].second == clone_piece[n].point[k].second) {
			piece_symbol = k;
		}
	}
	//右回りに頂点が等しい&その角度が等しい場合除外
	for (int t = 0; t < (clone_piece.back().point.size() / 2); t++) {
		if (piece_symbol + t > clone_piece[n].point.size()) {
			break;
		}
		if (clone_piece.back().point[i + t].first == clone_piece[n].point[piece_symbol + t].first && clone_piece.back().point[i + t].second == clone_piece[n].point[piece_symbol + t].second) {
			if (clone_piece.back().angle[t] == clone_piece[n].angle[piece_symbol + t]) {
				//頂点を削除
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
				give_piece.back().point.erase(give_piece[n].point.begin() + i + t);
			}
			else {
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
			}
		}
	}
	//左回りに頂点が等しい&その角度が等しい場合除外
	for (int t = 0; t < (clone_piece.back().point.size() / 2); t++) {
		if (piece_symbol - t > clone_piece[n].point.size()) {
			break;
		}
		if (clone_piece.back().point[i - t].first == clone_piece[n].point[piece_symbol - t].first && clone_piece.back().point[i - t].second == clone_piece[n].point[piece_symbol - t].second) {
			if (clone_piece.back().angle[t] == clone_piece[n].angle[piece_symbol + t]) {
				//頂点を削除
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
				give_piece.back().point.erase(give_piece[n].point.begin() + i - t);
				frame_symbol -= 1;
			}
			else {
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
			}
		}
	}
	//最初に入れる方を挿入
	for (int t = 0; t < clone_piece[n].angle.size(); t++) {
		Circle circle(give_piece[n].point[t].first, give_piece[n].point[t].second, 1);
		for (int k = 0; k < clone_piece.back().angle.size(); k++) {
			if (k != clone_piece.back().angle.size() - 1) {
				Line line(clone_piece.back().point[k].first, clone_piece.back().point[k].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second);
				if (line.intersects(circle)) {
					give_piece.back().point.insert(give_piece.back().point.begin() + i + frame_symbol, give_piece[n].point[t]);
					frame_symbol += 1;
					break;
					se_count = se_count + 1;
				}
			}
			else {
				Line line(clone_piece.back().point[k].first, clone_piece.back().point[k].second, clone_piece.back().point[k + 1].first, clone_piece.back().point[k + 1].second);
				if (line.intersects(circle)) {
					give_piece.back().point.insert(give_piece.back().point.begin() + i + frame_symbol , give_piece[n].point[t]);
					frame_symbol += 1;
					break;
					se_count = se_count + 1;
				}
			}
		}
	}
	//ピースの残りの頂点を判定向きに挿入していく
	for (int k = clone_piece[n].angle.size(); k > 0; k--) {
		if (se_count == 2) {
			give_piece.back().point.insert(give_piece.back().point.begin() + i + frame_symbol - 1, give_piece[n].point[k]);
		}
		else {
			give_piece.back().point.insert(give_piece.back().point.begin() + i + frame_symbol, give_piece[n].point[k]);
		}
	}
	return true;
}

void Algorithm::select_piece(int i) {
	//評価点が高いピースがあるならupdate_piece()へ
	/*評価点が高いピースがあるなら正*/
	//ピースの番号を決定
	for (int n = 0; n < (clone_piece.size()); n++) {
		//ピースの角(頂点)決定
		for (int k = 0; k < clone_piece[n].angle.size(); k++) {
			if (three_evalution[flag][n][k] == 3) {
				//ピースの番号,枠の頂点を引数
				update_frame(n,i);
			}
		}
	}
}

bool Algorithm::check_collision(int n) {
	double f_slope =  0, p_slope = 0;
	int f_intercept = 0, p_intercept = 0;
	int count_x = 0, count_y = 0;
	/*
	枠・ピースの頂点を受け取る
	ピースを配置した時に枠の中に収まっているか判定
	n-ピースの番号,k-ピースの各頂点,i-枠の各頂点
	*/
	for (int k = 0; k < clone_piece[n].point.size(); k++) {
		for (int i = 0; i < clone_piece.back().point.size(); i++) {

			//枠の二つの頂点の直線の一次関数を求める
			//ループの最後になったのなら要素の最後と最初を使用する
			if ((int(clone_piece.back().point.size()) - 1) == i) {
				f_slope = (clone_piece.back().point[i].second - clone_piece.back().point[0].second) /
					(clone_piece.back().point[i].first - clone_piece.back().point[0].first);
				f_intercept = clone_piece.back().point[i].second - f_slope * clone_piece.back().point[i].first;
			}
			else {
				f_slope = (clone_piece.back().point[i].second - clone_piece.back().point[i + 1].second) /
					(clone_piece.back().point[i].first - clone_piece.back().point[i + 1].first);
				f_intercept = clone_piece.back().point[i].second - f_slope * clone_piece.back().point[i].first;
			}
			//ピースの二つの頂点の一次関数を求める
			if ((int(clone_piece[n].point.size()) - 1) == k) {
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
				if ((int(clone_piece.back().point.size()) - 1) == i) {
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
				if ((int(clone_piece.back().point.size()) - 1) == i) {
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

void Algorithm::turn_piece(int n) {
	/*
	ピースの番号を受け取る
	ピースを反転させ、頂点情報を更新
	axis一番X座標の小さい値が入ってる要素数
	*/
	int mini_point_x = 100, axis = 0;
	int minus = 0;

	//基準となる座標の決定
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		if (mini_point_x > clone_piece[n].point[i].first) {
			mini_point_x = clone_piece[n].point[i].first;
			axis = i;
		}
	}

	//反転
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first = clone_piece[n].point[axis].first -
			(clone_piece[n].point[i].first - clone_piece[n].point[axis].first);
	}

	//マイナス座標の修正
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		if (abs((clone_piece[n].point[i].first - clone_piece[n].point[axis].first)) > minus) {
			minus = abs((clone_piece[n].point[i].first - clone_piece[n].point[axis].first));
		}
	}
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first += minus;
	}
}

void Algorithm::spin90_piece(int n) {
	/*
	ピースを90度左回転させる
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first = cont.piece[n].point[i].first * (-1);
	}
}

void Algorithm::spin180_piece(int n) {
	/*
	ピースを180度左回転させる
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first = cont.piece[n].point[i].first * (-1);
		clone_piece[n].point[i].second = cont.piece[n].point[i].second * (-1);
	}
}

void Algorithm::spin270_piece(int n) {
	/*
	ピースを270度左回転させる
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].second = cont.piece[n].point[i].second * (-1);
	}
}

bool Algorithm::equal_angle(double first_angle, double second_angle) {
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