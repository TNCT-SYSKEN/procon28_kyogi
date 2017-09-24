#include "Algorithm.h"

Algorithm::Algorithm() {
	init();
}

void Algorithm::init() {
	flag = -1;
	collision_no = 0;
}

void Algorithm::fit_piece(vector<Piece> clone_piece) {
	flag += 1;
	if (flag == 0) {
		piece = clone_piece;
	}
	//ピース嵌めるアルゴリズムをまとめる
	//枠の基準となる頂点を決定
	for (int i = 0; i < clone_piece.back().point.size(); i++) {
		evaluation(i, clone_piece);
		select_piece(i,clone_piece);
		three_evalution.pop_back();
	}
	flag += 1;
}

void Algorithm::evaluation(int i,vector<Piece> &clone_piece) {
	//枠・ピースの頂点・角度・辺の長さを受け取る
	//ピースと枠の評価点を作成
	//ピースを一つ決定
	for (int n = 0; n < (clone_piece.size() - 1); n++) {
		//ピースの角(頂点)を一つ決定
		for (int k = 0; k < clone_piece[n].angle.size(); k++) {
			//枠とピースの角度を比較
			one_evalution.push_back(0);

			if (equal_angle(clone_piece.back().angle[i], clone_piece[n].angle[k])) {
				one_evalution[k] = 1;
				//その両端の辺も比較
				if (equal_line(clone_piece.back().line[i], clone_piece[n].line[k])) {
					one_evalution[k] += 1;
				}
				if (i == 0 && k == 0) {
					if (equal_line(clone_piece.back().line.back(), clone_piece[n].line.back())) {
						one_evalution[k] += 1;
					}
				}
				else if (i != 0 && k == 0) {
					if (equal_line(clone_piece.back().line[i - 1], clone_piece[n].line.back())) {
							one_evalution[k] += 1;
					}
				}
				else if (i == 0 && k != 0) {
					if (equal_line(clone_piece.back().line.back(), clone_piece[n].line[k - 1])) {
						one_evalution[k] += 1;
					}
				}
			}
			else {
				one_evalution[k] = 0;
			}
		}
		two_evalution.push_back(one_evalution);
		one_evalution.clear();
	}
	three_evalution.push_back(two_evalution);
	two_evalution.clear();
}

void Algorithm::union_piece() {
	//二つのピースの角度・辺を受け取る
	//ピース同士の評価点を作成
	//評価点を元にピースを結合
}

bool Algorithm::update_frame(int n ,int i, int q, vector<Piece> &clone_piece) {
	vector<Piece> give_piece = clone_piece;
	vector<pair<int, int> > new_frame;
	int piece_symbol = 0;
	int p_erase_count = 0;
	int f_erase_count = 0;
	int se_count = 0;
	int incert_count = 0;
	if (!(collision_checker(n, i, q, clone_piece))) {
		return false;
	}
	//ans_pointへの代入;
	piece[n].ans_point = clone_piece[n].point;
	//基準を求める
	for (int k = 0; k < clone_piece[n].point.size(); k++) {
		if (clone_piece.back().point[i].first == clone_piece[n].point[k].first && clone_piece.back().point[i].second == clone_piece[n].point[k].second) {
			piece_symbol = k;
			break;
		}
	}
	//右回りに頂点が等しい&その角度が等しい場合除外
	for (int t = 1; t < clone_piece[n].point.size(); t++) {
		if (piece_symbol + t > clone_piece[n].point.size() - 1) {
			break;
		}
		if (i + t > clone_piece.back().point.size() - 1) {
			break;
		}
		if (clone_piece.back().point[i + t].first == clone_piece[n].point[piece_symbol + t].first && clone_piece.back().point[i + t].second == clone_piece[n].point[piece_symbol + t].second) {
			if (clone_piece.back().angle[i + t] == clone_piece[n].angle[piece_symbol + t]) {
				//頂点を削除
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
				give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol + t);
				give_piece.back().point.erase(give_piece.back().point.begin() + i + t);
				give_piece.back().angle.erase(give_piece.back().angle.begin() + i + t);
			}
			else {
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
				give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol + t);
				if (fabs(180 - fabs(clone_piece.back().angle[i + t] - clone_piece[n].angle[piece_symbol + t])) <= 0.50) {
					give_piece.back().point.erase(give_piece.back().point.begin() + i + t);
					give_piece.back().angle.erase(give_piece.back().angle.begin() + i + t);
				}
			}
		}
		else {
			break;
		}
	}
	//左回りに頂点が等しい&その角度が等しい場合除外
	for (int t = 1; t < clone_piece.back().point.size(); t++) {
		if (piece_symbol - t < 0) {
			break;
		}
		if (i - t < 0) {
			break;
		}
		if (clone_piece.back().point[i - t].first == clone_piece[n].point[piece_symbol - t].first && clone_piece.back().point[i - t].second == clone_piece[n].point[piece_symbol - t].second) {
			if (clone_piece.back().angle[i - t] == clone_piece[n].angle[piece_symbol - t]) {
				//頂点を削除
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - t);
				give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - t);
				p_erase_count += 1;
				give_piece.back().point.erase(give_piece.back().point.begin() + i - t);
				give_piece.back().angle.erase(give_piece.back().angle.begin() + i - t);
				f_erase_count += 1;
			}
			else {
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
				give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - t);
				p_erase_count += 1;
				if (fabs(180 - fabs(clone_piece.back().angle[i - t] - clone_piece[n].angle[piece_symbol - t])) <= 0.50) {
					give_piece.back().point.erase(give_piece.back().point.begin() + i - t);
					give_piece.back().angle.erase(give_piece.back().angle.begin() + i - t);
					f_erase_count += 1;
				}
			}
		}
		else {
			break;
		}
	}
	//基準になった頂点の削除
	give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count);
	give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count);
	give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count);
	give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count);
	//最初に入れる方を挿入
	for (int t = 0; t < give_piece[n].point.size(); t++) {
		Circle circle(give_piece[n].point[t].first, give_piece[n].point[t].second, 0.5);
		for (int k = 0; k < clone_piece.back().point.size(); k++) {
			if (k == clone_piece.back().point.size() - 1) {
				Line line(clone_piece.back().point[k].first, clone_piece.back().point[k].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second);
				if (line.intersects(circle)) {
					if (i - f_erase_count == 0) {
						if (se_count == 0) {
							give_piece.back().point.insert(give_piece.back().point.end(), give_piece[n].point[t]);
							give_piece[n].point.erase(give_piece[n].point.begin() + t);
							se_count += 1;
							incert_count = 1;
							break;
						}
						else {
							//嵌めるピースが一つ前の頂点と近い方を判定
							int a = hypot(fabs(clone_piece.back().point[clone_piece.back().point.size() - 2].first - give_piece[n].point[t].first),
										fabs(clone_piece.back().point[clone_piece.back().point.size() - 2].second - give_piece[n].point[t].second));

							int b = hypot(fabs(clone_piece.back().point[clone_piece.back().point.size() - 2].first - clone_piece.back().point[clone_piece.back().point.size() - 1].first),
										fabs(clone_piece.back().point[clone_piece.back().point.size() - 2].second - clone_piece.back().point[clone_piece.back().point.size() - 1].second));
							if (a > b) {
								give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[t]);
								give_piece[n].point.erase(give_piece[n].point.begin() + t);
								se_count += 1;
								incert_count = 1;
								break;
							}
							else {
								give_piece.back().point.insert(give_piece.back().point.end() - 2, give_piece[n].point[t]);
								give_piece[n].point.erase(give_piece[n].point.begin() + t);
								se_count += 1;
								incert_count = 1;
								break;
							}
						}
					}
					else {
						if (se_count == 0) {
							give_piece.back().point.insert(give_piece.back().point.begin() + i - f_erase_count - 1, give_piece[n].point[t]);
							give_piece[n].point.erase(give_piece[n].point.begin() + t);
							se_count += 1;
							incert_count = 1;
							break;
						}
						else {
							//嵌めるピースが一つ前の頂点と近い方を判定
							int a = hypot(fabs(give_piece.back().point[i - f_erase_count - 1].first - give_piece[n].point[t].first),
										fabs(give_piece.back().point[i - f_erase_count - 1].second - give_piece[n].point[t].second));
							int b = hypot(fabs(give_piece.back().point[i - f_erase_count - 1].first - give_piece.back().point[i - f_erase_count].first),
										fabs(give_piece.back().point[i - f_erase_count - 1].second - give_piece.back().point[i - f_erase_count].second));
							if (a > b) {
								give_piece.back().point.insert(give_piece.back().point.begin() + i - f_erase_count, give_piece[n].point[t]);
								give_piece[n].point.erase(give_piece[n].point.begin() + t);
								se_count += 1;
								incert_count = 1;
								break;
							}
							else {
								give_piece.back().point.insert(give_piece.back().point.begin() + i - f_erase_count - 1, give_piece[n].point[t]);
								give_piece[n].point.erase(give_piece[n].point.begin() + t);
								se_count += 1;
								incert_count = 1;
								break;
							}
						}
					}
				}
			}
			else {
				Line line(clone_piece.back().point[k].first, clone_piece.back().point[k].second, clone_piece.back().point[k + 1].first, clone_piece.back().point[k + 1].second);
				if (line.intersects(circle)) {
					if (i - f_erase_count == 0) {
						if (se_count == 0) {
							give_piece.back().point.insert(give_piece.back().point.end(), give_piece[n].point[t]);
							give_piece[n].point.erase(give_piece[n].point.begin() + t);
							se_count += 1;
							incert_count = 1;
							break;
						}
						else {
							//嵌めるピースが一つ前の頂点と近い方を判定
							int a = hypot(fabs(clone_piece.back().point[clone_piece.back().point.size() - 2].first - give_piece[n].point[t].first),
								fabs(clone_piece.back().point[clone_piece.back().point.size() - 2].second - give_piece[n].point[t].second));

							int b = hypot(fabs(clone_piece.back().point[clone_piece.back().point.size() - 2].first - clone_piece.back().point[clone_piece.back().point.size() - 1].first),
								fabs(clone_piece.back().point[clone_piece.back().point.size() - 2].second - clone_piece.back().point[clone_piece.back().point.size() - 1].second));
							if (a > b) {
								give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[t]);
								give_piece[n].point.erase(give_piece[n].point.begin() + t);
								se_count += 1;
								incert_count = 1;
								break;
							}
							else {
								give_piece.back().point.insert(give_piece.back().point.end() - 2, give_piece[n].point[t]);
								give_piece[n].point.erase(give_piece[n].point.begin() + t);
								se_count += 1;
								incert_count = 1;
								break;
							}
						}
					}
					else {
						if (se_count == 0) {
							give_piece.back().point.insert(give_piece.back().point.begin() + i - f_erase_count - 1, give_piece[n].point[t]);
							give_piece[n].point.erase(give_piece[n].point.begin() + t);
							se_count += 1;
							incert_count = 1;
							break;
						}
						else {
							//嵌めるピースが一つ前の頂点と近い方を判定
							int a = hypot(fabs(give_piece.back().point[i - f_erase_count - 1].first - give_piece[n].point[t].first),
								fabs(give_piece.back().point[i - f_erase_count - 1].second - give_piece[n].point[t].second));
							int b = hypot(fabs(give_piece.back().point[i - f_erase_count - 1].first - give_piece.back().point[i - f_erase_count].first),
								fabs(give_piece.back().point[i - f_erase_count - 1].second - give_piece.back().point[i - f_erase_count].second));
							if (a > b) {
								give_piece.back().point.insert(give_piece.back().point.begin() + i - f_erase_count, give_piece[n].point[t]);
								give_piece[n].point.erase(give_piece[n].point.begin() + t);
								se_count += 1;
								incert_count = 1;
								break;
							}
							else {
								give_piece.back().point.insert(give_piece.back().point.begin() + i - f_erase_count - 1, give_piece[n].point[t]);
								give_piece[n].point.erase(give_piece[n].point.begin() + t);
								se_count += 1;
								incert_count = 1;
								break;
							}
						}
					}
				}
			}
		}
	}
	//ピースの残りの頂点を反対向きに挿入していく
	for (int k = give_piece[n].point.size() - 1; k >= 0; k--) {
		if (incert_count == 1) {
			if (se_count == 1||se_count == 0) {
				give_piece.back().point.insert(give_piece.back().point.end(), give_piece[n].point[k]);
			}
			else if(se_count == 2){
				give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[k]);
			}
		}
		else {
			if (se_count == 1 || se_count == 0) {
				give_piece.back().point.insert(give_piece.back().point.end(), give_piece[n].point[k]);
			}
			else if (se_count == 2) {
				give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[k]);
			}
		}
	}

	//更新した情報の共有
	new_frame = give_piece.back().point;
	give_piece = clone_piece;
	give_piece.back().point.clear();
	give_piece.back().point = new_frame;
	give_piece.back().ans_point.clear();
	give_piece.back().ans_point = new_frame;
	give_piece.erase(give_piece.begin() + n);
	//枠の辺、角度の更新
	sort_frame(give_piece);
	//スクショの保存
	if (give_piece.back().point.size() == 0) {
		Control cont;
		cont.output_piece(give_piece);

	}
	else {
		//再帰
		fit_piece(give_piece);
	}
	return true;
}

void Algorithm::select_piece(int i, vector<Piece> &clone_piece) {
	//評価点が高いピースがあるならupdate_piece()へ
	/*評価点が高いピースがあるなら正*/
	//ピースの番号を決定
	for (int n = 0; n < (clone_piece.size() - 1); n++) {
		//ピースの角(頂点)決定
		for (int k = 0; k < (clone_piece[n].point.size() - 1); k++) {
			if (three_evalution[flag][n][k] == 3) {
			//ピースの番号,枠の頂点を引数
			update_frame(n, i, k,clone_piece);
			}
		}
	}
	for (int n = 0; n < (clone_piece.size()- 1); n++) {
		//ピースの角(頂点)決定
		for (int k = 0; k < (clone_piece[n].point.size() - 1); k++) {
			if (three_evalution[flag][n][k] == 2) {
				//ピースの番号,枠の頂点を引数
				update_frame(n, i, k, clone_piece);
			}
		}
	}
	for (int n = 0; n < (clone_piece.size() - 1); n++) {
		//ピースの角(頂点)決定
		for (int k = 0; k < (clone_piece[n].point.size() - 1); k++) {
			if (three_evalution[flag][n][k] == 1) {
				//ピースの番号,枠の頂点を引数
				update_frame(n, i,k, clone_piece);
			}
		}
	}
}

bool Algorithm::check_collision(int n,vector<Piece> &clone_piece) {
	//ピースが枠から出てるならTrue
	int count_x, count_y;
	int count;
	
	//頂点が外に出ているピースの判定
	for (int j = 0; j < clone_piece[n].point.size(); j++) {
		count_x = 0;
		count_y = 0;
		//y軸へ延長した線分
		//x軸へ延長した線分
		Line y_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point[j].first, 200);
		Line x_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, 200, clone_piece[n].point[j].second);
		for (int i = 0; i < clone_piece.back().point.size(); i++) {
			//枠の各辺との交わりをカウント
			if (i == clone_piece.back().point.size() - 1) {
				Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second);
				if (clone_piece[n].point[j].second == clone_piece.back().point[i].second && clone_piece[n].point[j].second == clone_piece.back().point.front().second) {
					count_x += 1;
				}
				else if (clone_piece[n].point[j].second == clone_piece.back().point[i].second || clone_piece[n].point[j].second == clone_piece.back().point.front().second) {
					//count_x += 1;
					}
				else if (x_line.intersects(f_line)) {
						count_x += 1;
					}
				if (clone_piece[n].point[j].first == clone_piece.back().point[i].first && clone_piece[n].point[j].first == clone_piece.back().point.front().first) {
					count_y += 1;
				}
				else if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point[j].first == clone_piece.back().point.front().first) {
					//count_y += 1;
					}
				else if (y_line.intersects(f_line)) {
					count_y += 1;
				}
			}
			else {
				Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point[i + 1].first, clone_piece.back().point[i + 1].second);
				if (clone_piece[n].point[j].second == clone_piece.back().point[i].second && clone_piece[n].point[j].second == clone_piece.back().point[i + 1].second) {
					count_x += 1;
				}
				else if (clone_piece[n].point[j].second == clone_piece.back().point[i].second || clone_piece[n].point[j].second == clone_piece.back().point[i + 1].second) {
					//count_x += 1;
				}
				else if (x_line.intersects(f_line)) {
					count_x += 1;
				}
				if (clone_piece[n].point[j].first == clone_piece.back().point[i].first && clone_piece[n].point[j].first == clone_piece.back().point[i + 1].first) {
					count_y += 1;
				}
				else if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point[j].first == clone_piece.back().point[i + 1].first) {
					//count_y += 1;
				}
				else if (y_line.intersects(f_line)) {
					count_y += 1;
				}
			}
		}
		//偶数なら枠の外側の頂点
		if (count_x % 2 == 0 && count_y % 2 == 0) {
			return true;
		}
 	}
	//頂点が外に出ていないピースの判定
	for (int j = 0; j < clone_piece[n].point.size(); j++) {
		count = 0;
		for (int i = 0; i < clone_piece.back().point.size(); i++) {
			if (i == clone_piece.back().point.size() - 1) {
				if (j == clone_piece[n].point.size() - 1) {
					Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second);
					Line p_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point.front().first, clone_piece[n].point.front().second);
					if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point.front().first == clone_piece.back().point.front().first) {
						//hoge
					}
					else if (f_line.intersects(p_line)) {
						count += 1;
					}
				}
				else {
					Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second);
					Line p_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point[j + 1].first, clone_piece[n].point[j + 1].second);
					if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point[j + 1].first == clone_piece.back().point.front().first) {
						//hoge
					}
					else if (f_line.intersects(p_line)) {
						count += 1;
					}
				}
			}
			else {
				if (j == clone_piece[n].point.size() - 1) {
					Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point[i + 1].first, clone_piece.back().point[i + 1].second);
					Line p_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point.front().first, clone_piece[n].point.front().second);
					if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point.front().first == clone_piece.back().point[i + 1].first) {
						//hoge
					}
					else if (f_line.intersects(p_line)) {
						count += 1;
					}
				}
				else {
					Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point[i + 1].first, clone_piece.back().point[i + 1].second);
					Line p_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point[j + 1].first, clone_piece[n].point[j + 1].second);
					if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point[j + 1].first == clone_piece.back().point[i + 1].first) {
						//hoge
					}
					else if (f_line.intersects(p_line)) {
						count += 1;
					}
				}
			}
		}
		if (count >= 2) {
			return true;
		}
	}
	return false;
}

void Algorithm::sort_frame(vector<Piece> &give_piece) {
	algo_make_angle(give_piece);
	algo_make_line(give_piece);
}

void Algorithm::algo_make_line(vector<Piece> &give_piece) {
	//頂点から辺、角度の算出
	//元の辺を削除
	give_piece.back().line.clear();
	for (int i = 0; i < give_piece.back().point.size(); i++) {
		if (i == give_piece.back().point.size() - 1) {
			double base, height;
			double line;
			base = give_piece.back().point[i].first - give_piece.back().point[0].first;
			height = give_piece.back().point[i].second - give_piece.back().point[0].second;
			line = sqrt(pow(base, 2) + pow(height, 2));
			give_piece.back().line.push_back(line);
		}
		else {
			double base, height;
			double line;
			base = give_piece.back().point[i].first - give_piece.back().point[i + 1].first;
			height = give_piece.back().point[i].second - give_piece.back().point[i + 1].second;
			line = sqrt(pow(base, 2) + pow(height, 2));
			give_piece.back().line.push_back(line);
		}
	}
}

void Algorithm::algo_make_angle(vector<Piece> &give_piece) {
	//元の角度の削除
	give_piece.back().angle.clear();
	//16方を参照するための配列
	double x_point[16] = { 0,0.25,0.5,0.5,0.5,0.5,0.5,0.25,0,-0.25,-0.5,-0.5,-0.5,-0.5,-0.5,-0.25 };
	double y_point[16] = { -0.5,-0.5,-0.5,-0.25,0,0.25,0.5,0.5,0.5,0.5,0.5,0.25,0,-0.25,-0.5,-0.5 };
	//交わった辺をカウントするための変数
	int count_x, count_y;

	for (int j = 0; j < give_piece.back().point.size(); j++) {
		int check_angle = 0;
		for (int k = 0; k < 16; k++) {
			count_x = 0;
			count_y = 0;
			//y軸へ延長した線分
			//x軸へ延長した線分
			Line y_line(give_piece.back().point[j].first + x_point[k], give_piece.back().point[j].second + y_point[k], give_piece.back().point[j].first,200);
			Line x_line(give_piece.back().point[j].first + x_point[k], give_piece.back().point[j].second + y_point[k], 200, give_piece.back().point[j].second);
			for (int i = 0; i < give_piece.back().point.size(); i++) {
				//枠の各辺との交わりをカウント
				if (i == give_piece.back().point.size() - 1) {
					Line f_line(give_piece.back().point[i].first, give_piece.back().point[i].second, give_piece.back().point.front().first, give_piece.back().point.front().second);
					if (give_piece.back().point[j].second + y_point[k] == give_piece.back().point[i].second || give_piece.back().point[j].second + y_point[k] == give_piece.back().point.front().second) {

					}
					else if (x_line.intersects(f_line)) {
						count_x += 1;
					}
					if (give_piece.back().point[j].first + x_point[k] == give_piece.back().point[i].first || give_piece.back().point[j].first + x_point[k] == give_piece.back().point.front().first) {

					}
					else if (y_line.intersects(f_line)) {
						count_y += 1;
					}
				}
				else {
					Line f_line(give_piece.back().point[i].first, give_piece.back().point[i].second, give_piece.back().point[i + 1].first, give_piece.back().point[i + 1].second);
					if (give_piece.back().point[j].second + y_point[k] == give_piece.back().point[i].second || give_piece.back().point[j].second + y_point[k] == give_piece.back().point[i + 1].second) {

					}
					else if (x_line.intersects(f_line)) {
						count_x += 1;
					}
					if (give_piece.back().point[j].first + x_point[k] == give_piece.back().point[i].first || give_piece.back().point[j].first + x_point[k] == give_piece.back().point[i + 1].first) {

					}
					else if (y_line.intersects(f_line)) {
						count_y += 1;
					}
				}
				count_x;
				count_y;
			}
			//奇数なら枠の内側の頂点
			if (count_x % 2 == 1 || count_y % 2 == 1) {
				check_angle += 1;
			}
		}
		//必要な変数
		double a1, a2, b1, b2;
		double a, b, c, d;
		double angle;
		//基準の頂点からのベクトル成分
		a1 = give_piece.back().point[(j + 1) % give_piece.back().point.size()].first - give_piece.back().point[j].first;
		a2 = give_piece.back().point[(j + 1) % give_piece.back().point.size()].second - give_piece.back().point[j].second;
		b1 = give_piece.back().point[(j + give_piece.back().point.size() - 1) % give_piece.back().point.size()].first - give_piece.back().point[j].first;
		b2 = give_piece.back().point[(j + give_piece.back().point.size() - 1) % give_piece.back().point.size()].second - give_piece.back().point[j].second;
		//ベクトルの内積
		a = a1 * b1;
		b = a2 * b2;
		c = sqrt(pow(a1, 2) + pow(a2, 2));
		d = sqrt(pow(b1, 2) + pow(b2, 2));
		angle = (a + b) / (c * d);
		angle = acos(angle);
		angle = angle * 180 / Pi;
		//凹角である
		if (check_angle >= 9) {
			angle = 360 - angle;
			give_piece.back().angle.push_back(angle);
		}
		//凸角である
		else {
			give_piece.back().angle.push_back(angle);
		}
		/*if (give_piece.back().angle.back() == 0) {
			give_piece.back().angle.pop_back();
			give_piece.back().point.erase(give_piece.back().point.begin() + j);
		}*/
	}
}

void Algorithm::turn_piece(int n, vector<Piece> &clone_piece) {
	/*
	ピースの番号を受け取る
	ピースを反転させ、頂点情報を更新
	axis一番X座標の小さい値が入ってる要素数
	*/
	int mini_point_x = 100, axis = 0;
	int minus = 0;

	//基準となる座標の決定
	for (int i = 0; i < clone_piece[n].point.size(); i++) {
		if (mini_point_x > clone_piece[n].point[i].first) {
			mini_point_x = clone_piece[n].point[i].first;
			axis = i;
		}
	}

	//反転
	for (int i = 0; i < clone_piece[n].point.size(); i++) {
		clone_piece[n].point[i].first = clone_piece[n].point[axis].first -
			(clone_piece[n].point[i].first - clone_piece[n].point[axis].first);
	}
}

void Algorithm::spin90_piece(int n,vector<Piece> &clone_piece) {
	/*
	ピースを90度左回転させる
	*/
	int x, y;
	for (int i = 0; i < clone_piece[n].point.size(); i++) {
		x = clone_piece[n].point[i].first;
		y = clone_piece[n].point[i].second;
		clone_piece[n].point[i].first = -1 * y;
		clone_piece[n].point[i].second = x;
	}
}

void Algorithm::spin180_piece(int n,vector<Piece> &clone_piece) {
	/*
	ピースを180度左回転させる
	*/
	int x, y;
	for (int i = 0; i < clone_piece[n].point.size(); i++) {
		x = clone_piece[n].point[i].first;
		y = clone_piece[n].point[i].second;
		clone_piece[n].point[i].first = -1 * y;
		clone_piece[n].point[i].second = -1 *x;
	}
}

void Algorithm::spin270_piece(int n,vector<Piece> &clone_piece) {
	/*
	ピースを270度左回転させる
	*/
	int x, y;
	for (int i = 0; i < clone_piece[n].point.size(); i++) {
		x = clone_piece[n].point[i].first;
		y = clone_piece[n].point[i].second;
		clone_piece[n].point[i].first = y;
		clone_piece[n].point[i].second = -1 * x;
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
		return false;
	}
}

bool Algorithm::equal_line(double first_line, double second_line) {
	/*
	枠とピースの辺情報を受け取る
	もし誤差の範囲内で等しいならばTrue
	*/ 
	
	if (fabs(first_line - second_line) <= 0.10) {
		return true;
	}
	else {
		return false;
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

bool Algorithm::collision_checker(int n,int i,int q,vector<Piece> &clone_piece) {
		//回転,反転,あたり判定によって当てはまるか判定
		bool collision = true;
		Piece base = clone_piece[n];
		int set_x;
		int set_y;

		set_x = clone_piece.back().point[i].first;
		set_y = clone_piece.back().point[i].second;

		if (set_x < clone_piece[n].point[q].first) {
				int p = clone_piece[n].point[q].first - set_x;
				for (int j = 0; j < base.point.size(); j++) {
						clone_piece[n].point[j].first -= p;
				}
		}
		else if (set_x > clone_piece[n].point[q].first) {
				int p = set_x - clone_piece[n].point[q].first;
				for (int j = 0; j < base.point.size(); j++) {
						clone_piece[n].point[j].first += p;
				}
		}
		if (set_y < clone_piece[n].point[q].second) {
				int p = clone_piece[n].point[q].second - set_y;
				for (int j = 0; j < base.point.size(); j++) {
						clone_piece[n].point[j].second -= p;
				}
		}
		else if (set_y > clone_piece[n].point[q].second) {
				int p = set_y - clone_piece[n].point[q].second;
				for (int j = 0; j < base.point.size(); j++) {
						clone_piece[n].point[j].second += p;
				}
		}

		Piece set = clone_piece[n];

		if (collision == true && collision_no == 0) {
				collision = check_collision(n, clone_piece);
				collision_no++;
		}
		if (collision == true && collision_no == 1) {
				spin90_piece(n, clone_piece);
				collision = check_collision(n, clone_piece);
				collision_no++;
		}
		if (collision == true && collision_no == 2) {
				clone_piece[n] = set;
				spin180_piece(n, clone_piece);
				collision = check_collision(n, clone_piece);
				collision_no++;
		}
		if (collision == true && collision_no == 3) {
				clone_piece[n] = set;
				spin270_piece(n, clone_piece);
				collision = check_collision(n, clone_piece);
				collision_no++;
		}
		if (collision == true && collision_no == 4) {
				clone_piece[n] = set;
				turn_piece(n, clone_piece);
				collision = check_collision(n, clone_piece);
				collision_no++;
		}
		if (collision == true && collision_no == 5) {
				clone_piece[n] = set;
				turn_piece(n, clone_piece);
				spin90_piece(n, clone_piece);
				collision = check_collision(n, clone_piece);
				collision_no++;
		}
		if (collision == true && collision_no == 6) {
				clone_piece[n] = set;
				turn_piece(n, clone_piece);
				spin180_piece(n, clone_piece);
				collision = check_collision(n, clone_piece);
				collision_no++;
		}
		if (collision == true && collision_no == 7) {
				clone_piece[n] = set;
				turn_piece(n, clone_piece);
				spin270_piece(n, clone_piece);
				collision = check_collision(n, clone_piece);
		}
		if (collision == true) {
				clone_piece[n] = set;
				collision_no = 0;
				return false;
		}
		if (collision == false) {
				collision_no = 0;
				return true;
		}
		return true;
}
