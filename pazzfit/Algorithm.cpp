#include "Algorithm.h"

Algorithm::Algorithm() {
	init();
}

void Algorithm::init() {
	flag = -1;
	collision_no = 0;
	system_end = 0;
}

void Algorithm::fit_piece(vector<Piece> clone_piece) {
 	flag += 1;
	if (flag == 0) {
		piece = clone_piece;
		ans_piece = clone_piece;
	}
	
	//ピース嵌めるアルゴリズムをまとめる
	//枠の基準となる頂点を決定
	for (int sele = 3; sele > 0; sele--) {
		for (int i = 0; i < clone_piece.back().point.size(); i++) {
			if (system_end) {
				break;
			}
			evaluation(i, clone_piece);
			select_piece(i, clone_piece ,sele);
			three_evalution.pop_back();
		}
	}
	flag -= 1;
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
				if (equal_line(clone_piece.back().line[(i - 1 + clone_piece.back().line.size()) % clone_piece.back().line.size()], clone_piece[n].line[(k - 1 + clone_piece[n].line.size()) % clone_piece[n].line.size()])) {
					one_evalution[k] += 1;
				}
				/*if (i == 0 && k == 0) {
					if (equal_line(clone_piece.back().line.back(), clone_piece[n].line.back())) {
						one_evalution[k] += 1;
					}
				}
				else if (i != 0 && k != 0) {
					if (equal_line(clone_piece.back().line[i - 1], clone_piece[n].line[k - 1])) {
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
				}*/
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
	vector<pair<int ,int> > line_piece;
	vector<pair<int, int> > new_frame;
	int piece_symbol = 0;
	int p_erase_count = 0;
	int f_erase_count = 0;
	int se_count = 0;
	int incert_count = 0;
	int point_iter = 0;

	//回転チェック
	if (!(collision_checker(n, i, q, give_piece))) {
		return false;
	}
	//マイナス座標なら除外
	for (int j = 0; j < give_piece[n].point.size(); j++) {
		if (give_piece[n].point[j].first * -1 > 0 || give_piece[n].point[j].second * -1 > 0) {
			return false;
		}
	}
	//ans_pointへの代入;
	ans_piece[flag].ans_point = give_piece[n].point;
	line_piece = give_piece[n].point;
	for (int j = 0; j < give_piece[n].point.size(); j++) {
		if (j == give_piece[n].point.size() - 1) {
			LineInt(give_piece[n].point[j].first * 5, give_piece[n].point[j].second * 5, give_piece[n].point[0].first * 5, give_piece[n].point[0].second * 5).draw(Palette::Black);
		}
		else {
			LineInt(give_piece[n].point[j].first * 5, give_piece[n].point[j].second * 5, give_piece[n].point[j + 1].first * 5, give_piece[n].point[j + 1].second * 5).draw(Palette::Black);
		}
	}
	System::Update();
	//基準を求める
	int fuga = 1;
	/*for (int k = 0; k < give_piece[n].point.size(); k++) {
		if (give_piece.back().point[i].first == give_piece[n].point[k].first && give_piece.back().point[i].second == give_piece[n].point[k].second) {
			piece_symbol = k;
			break;
		}
	}*/
	piece_symbol = q;
	//右回りに頂点が等しい&その角度が等しい場合除外
	while (1){
		if (give_piece.back().point[(i - f_erase_count + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first == give_piece[n].point[(piece_symbol - p_erase_count + 1 + give_piece[n].point.size()) % give_piece[n].point.size()].first) {
			if (give_piece.back().point[(i - f_erase_count + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second == give_piece[n].point[(piece_symbol - p_erase_count + 1 + give_piece[n].point.size()) % give_piece[n].point.size()].second) {
				int ho_frame = (i - f_erase_count + 1 + give_piece.back().point.size()) % give_piece.back().point.size();
				int ho_piece = (piece_symbol - p_erase_count + 1 + give_piece[n].point.size()) % give_piece[n].point.size();
				if (equal_angle(give_piece.back().angle[(i - f_erase_count + 1 + give_piece.back().angle.size()) % give_piece.back().angle.size()], give_piece[n].angle[(piece_symbol - p_erase_count + 1 + give_piece[n].angle.size()) % give_piece[n].angle.size()])) {
					give_piece.back().point.erase(give_piece.back().point.begin() + (i - f_erase_count + 1 + give_piece.back().angle.size()) % give_piece.back().angle.size());
					give_piece.back().angle.erase(give_piece.back().angle.begin() + (i - f_erase_count + 1 + give_piece.back().angle.size()) % give_piece.back().angle.size());
					give_piece[n].point.erase(give_piece[n].point.begin() + (piece_symbol - p_erase_count + 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					give_piece[n].angle.erase(give_piece[n].angle.begin() + (piece_symbol - p_erase_count + 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					if (ho_frame == 0) {
						f_erase_count += 1;
					}
					if (ho_piece == 0) {
						p_erase_count += 1;
					}
				}
				else if (fabs(180 - fabs(give_piece.back().angle[(i - f_erase_count + 1 + give_piece.back().angle.size()) % give_piece.back().angle.size()] - give_piece[n].angle[(piece_symbol - p_erase_count + 1 + give_piece[n].angle.size()) % give_piece[n].angle.size()])) < 0.50) {
					give_piece.back().point.erase(give_piece.back().point.begin() + (i - f_erase_count + 1 + give_piece.back().angle.size()) % give_piece.back().angle.size());
					give_piece.back().angle.erase(give_piece.back().angle.begin() + (i - f_erase_count + 1 + give_piece.back().angle.size()) % give_piece.back().angle.size());
					give_piece[n].point.erase(give_piece[n].point.begin() + (piece_symbol - p_erase_count + 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					give_piece[n].angle.erase(give_piece[n].angle.begin() + (piece_symbol - p_erase_count + 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					if (ho_frame == 0) {
						f_erase_count += 1;
					}
					if (ho_piece == 0) {
						p_erase_count += 1;
					}
				}
				else {
					give_piece[n].point.erase(give_piece[n].point.begin() + (piece_symbol - p_erase_count + 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					give_piece[n].angle.erase(give_piece[n].angle.begin() + (piece_symbol - p_erase_count + 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					if (ho_piece == 0) {
						p_erase_count += 1;
					}
				}
			}
			else {
				break;
			}
		}
		else {
			break;
		}
		/*if (i - f_erase_count + 1 == give_piece.back().point.size()&&piece_symbol - p_erase_count + 1 == give_piece[n].point.size()) {
			if (give_piece.back().point.front().first == give_piece[n].point.front().first && give_piece.back().point.front().second == give_piece[n].point.front().second) {
				if (equal_angle(give_piece.back().angle.front(),give_piece[n].angle.front())) {
					//頂点を削除
					give_piece[n].point.erase(give_piece[n].point.begin());
					give_piece[n].angle.erase(give_piece[n].angle.begin());
					give_piece.back().point.erase(give_piece.back().point.begin());
					give_piece.back().angle.erase(give_piece.back().angle.begin());
					if (i - f_erase_count != 0) {
						f_erase_count += 1;
					} 
					if (piece_symbol - p_erase_count != 0) {
						p_erase_count += 1;
					}
				}
				else {
					if (fabs(180 - fabs(give_piece.back().angle.front() - give_piece[n].angle.front())) <= 0.50) {
						give_piece.back().point.erase(give_piece.back().point.begin());
						give_piece.back().angle.erase(give_piece.back().angle.begin());
						if (i - f_erase_count != 0) {
							f_erase_count += 1;
						}
					}
					give_piece[n].point.erase(give_piece[n].point.begin());
					give_piece[n].angle.erase(give_piece[n].angle.begin());
					if (piece_symbol - p_erase_count != 0) {
						p_erase_count += 1;
					}
				}
			}
			else {
				break;
			}
		}
		else if (i - f_erase_count + 1 != give_piece.back().point.size() && piece_symbol - p_erase_count + 1 != give_piece[n].point.size()) {
			if (give_piece.back().point[i - f_erase_count + 1].first == give_piece[n].point[piece_symbol - p_erase_count + 1].first && give_piece.back().point[i - f_erase_count + 1].second == give_piece[n].point[piece_symbol - p_erase_count + 1].second) {
				if (give_piece.back().angle[i - f_erase_count + 1] == give_piece[n].angle[piece_symbol - p_erase_count + 1]) {
					//頂点を削除
					give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count + 1);
					give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count + 1);
					give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count + 1);
					give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count + 1);
				}
				else {
					if (fabs(180 - fabs(give_piece.back().angle[i - f_erase_count + 1] - give_piece[n].angle[piece_symbol - p_erase_count + 1])) <= 0.50) {
						give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count + 1);
						give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count + 1);
					}
					give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count + 1);
					give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count + 1);
				}
			}
			else {
				break;
			}
		}
		else if (i - f_erase_count + 1 == give_piece.back().point.size() && piece_symbol - p_erase_count + 1 != give_piece[n].point.size()) {
			if (give_piece.back().point.front().first == give_piece[n].point[piece_symbol - p_erase_count + 1].first && give_piece.back().point.front().second == give_piece[n].point[piece_symbol - p_erase_count + 1].second) {
				if (equal_angle(give_piece.back().angle.front(), give_piece[n].angle[piece_symbol - p_erase_count + 1])) {
					//頂点を削除
					give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count + 1);
					give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count + 1);
					give_piece.back().point.erase(give_piece.back().point.begin());
					give_piece.back().angle.erase(give_piece.back().angle.begin());
					if (i - f_erase_count != 0) {
						f_erase_count += 1;
					}
				}
				else {
					if (fabs(180 - fabs(give_piece.back().angle.front() - give_piece[n].angle[piece_symbol - p_erase_count + 1])) <= 0.50) {
						give_piece.back().point.erase(give_piece.back().point.begin());
						give_piece.back().angle.erase(give_piece.back().angle.begin());
						if (i - f_erase_count != 0) {
							f_erase_count += 1;
						}
					}
					give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count + 1);
					give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count + 1);
				}
			}
			else {
				break;
			}
		}
		else if (i - f_erase_count + 1 != give_piece.back().point.size() && piece_symbol - p_erase_count + 1 == give_piece[n].point.size()) {
			if (give_piece.back().point[i - f_erase_count + 1].first == give_piece[n].point.front().first && give_piece.back().point[i - f_erase_count + 1].second == give_piece[n].point.front().second) {
				if (equal_angle(give_piece.back().angle[i - f_erase_count + 1], give_piece[n].angle.front())) {
					//頂点を削除
					give_piece[n].point.erase(give_piece[n].point.begin());
					give_piece[n].angle.erase(give_piece[n].angle.begin());
					give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count + 1);
					give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count + 1);
					if (piece_symbol - p_erase_count != 0) {
						p_erase_count += 1;
					}
				}
				else {
					if (fabs(180 - fabs(give_piece.back().angle[i - f_erase_count + 1] - give_piece[n].angle.front()) <= 0.50)) {
						give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count + 1);
						give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count + 1);
					}
					give_piece[n].point.erase(give_piece[n].point.begin());
					give_piece[n].angle.erase(give_piece[n].angle.begin());
					if (piece_symbol - p_erase_count != 0) {
						p_erase_count += 1;
					}
				}
			}
			else {
				break;
			}
		}*/
	}
	//左回りに頂点が等しい&その角度が等しい場合除外
	while (1) {
		if (give_piece.back().point[(i - f_erase_count - 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first == give_piece[n].point[(piece_symbol - p_erase_count - 1 + give_piece[n].point.size()) % give_piece[n].point.size()].first) {
			if (give_piece.back().point[(i - f_erase_count - 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second == give_piece[n].point[(piece_symbol - p_erase_count - 1 + give_piece[n].point.size()) % give_piece[n].point.size()].second) {
				int ho_frame = (i - f_erase_count - 1 + give_piece.back().point.size()) % give_piece.back().point.size();
				int ho_piece = (piece_symbol - p_erase_count - 1 + give_piece[n].point.size()) % give_piece[n].point.size();
				if (equal_angle(give_piece.back().angle[(i - f_erase_count - 1 + give_piece.back().angle.size()) % give_piece.back().angle.size()], give_piece[n].angle[(piece_symbol - p_erase_count - 1 + give_piece[n].angle.size()) % give_piece[n].angle.size()])) {
					give_piece.back().point.erase(give_piece.back().point.begin() + (i - f_erase_count - 1 + give_piece.back().angle.size()) % give_piece.back().angle.size());
					give_piece.back().angle.erase(give_piece.back().angle.begin() + (i - f_erase_count - 1 + give_piece.back().angle.size()) % give_piece.back().angle.size());
					give_piece[n].point.erase(give_piece[n].point.begin() + (piece_symbol - p_erase_count - 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					give_piece[n].angle.erase(give_piece[n].angle.begin() + (piece_symbol - p_erase_count - 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					if (ho_frame < i - f_erase_count) {
						f_erase_count += 1;
					}
					if (ho_piece < piece_symbol - p_erase_count) {
						p_erase_count += 1;
					}
				}
				else if (fabs(180 - fabs(give_piece.back().angle[(i - f_erase_count - 1 + give_piece.back().angle.size()) % give_piece.back().angle.size()] - give_piece[n].angle[(piece_symbol - p_erase_count - 1 + give_piece[n].angle.size()) % give_piece[n].angle.size()])) < 0.50) {
					give_piece.back().point.erase(give_piece.back().point.begin() + (i - f_erase_count - 1 + give_piece.back().angle.size()) % give_piece.back().angle.size());
					give_piece.back().angle.erase(give_piece.back().angle.begin() + (i - f_erase_count - 1 + give_piece.back().angle.size()) % give_piece.back().angle.size());
					give_piece[n].point.erase(give_piece[n].point.begin() + (piece_symbol - p_erase_count - 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					give_piece[n].angle.erase(give_piece[n].angle.begin() + (piece_symbol - p_erase_count - 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					if (ho_frame < i - f_erase_count) {
						f_erase_count += 1;
					}
					if (ho_piece < piece_symbol - p_erase_count) {
						p_erase_count += 1;
					}
				}
				else {
					give_piece[n].point.erase(give_piece[n].point.begin() + (piece_symbol - p_erase_count - 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					give_piece[n].angle.erase(give_piece[n].angle.begin() + (piece_symbol - p_erase_count - 1 + give_piece[n].angle.size()) % give_piece[n].angle.size());
					if (ho_piece < piece_symbol - p_erase_count) {
						p_erase_count += 1;
					}
				}
			}
			else {
				break;
			}
		}
		else {
			break;
		}
		/*if (i == 0&& piece_symbol == 0) {
			if (give_piece.back().point.back().first == give_piece[n].point.back().first && give_piece.back().point.back().second == give_piece[n].point.back().second) {
				if (equal_angle(give_piece.back().angle.back(), give_piece[n].angle.back())) {
					//頂点を削除
					give_piece[n].point.erase(give_piece[n].point.end() - 1);
					give_piece[n].angle.erase(give_piece[n].angle.end() - 1);
					give_piece.back().point.erase(give_piece.back().point.end() - 1);
					give_piece.back().angle.erase(give_piece.back().angle.end() - 1);
				}
				else {
					if (fabs(180 - fabs(give_piece.back().angle.back() - give_piece[n].angle.back())) <= 0.50) {
						give_piece.back().point.erase(give_piece.back().point.end() - 1);
						give_piece.back().angle.erase(give_piece.back().angle.end() - 1);
					}
					give_piece[n].point.erase(give_piece[n].point.end() - 1);
					give_piece[n].angle.erase(give_piece[n].angle.end() - 1);
				}
			}
			else {
				break;
			}
		}
		else if (i - f_erase_count != 0 && piece_symbol - p_erase_count != 0) {
			if (give_piece.back().point[i - f_erase_count - 1].first == give_piece[n].point[piece_symbol - p_erase_count - 1].first && give_piece.back().point[i - f_erase_count - 1].second == give_piece[n].point[piece_symbol - p_erase_count - 1].second) {
				if (equal_angle(give_piece.back().angle[i - f_erase_count - 1], give_piece[n].angle[piece_symbol - p_erase_count - 1])) {
					//頂点を削除
					give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count - 1);
					give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count - 1);
					give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count - 1);
					give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count - 1);
					if (piece_symbol != 0) {
						p_erase_count += 1;
					}
					if (i != 0) {
						f_erase_count += 1;
					}
				}
				else {
					if (fabs(180 - fabs(give_piece.back().angle[i - f_erase_count - 1] - give_piece[n].angle[piece_symbol - p_erase_count - 1])) <= 0.50) {
						give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count - 1);
						give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count - 1);
						if (i != 0) {
							f_erase_count += 1;
						}
					}
					give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count - 1);
					give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count - 1);
					if (piece_symbol != 0) {
						p_erase_count += 1;
					}
				}
			}
			else {
				break;
			}
		}
		else if (i - f_erase_count == 0 && piece_symbol - p_erase_count != 0) {
			if (give_piece.back().point.back().first == give_piece[n].point[piece_symbol - p_erase_count - 1].first && give_piece.back().point.back().second == give_piece[n].point[piece_symbol - p_erase_count - 1].second) {
				if (equal_angle(give_piece.back().angle.back(), give_piece[n].angle[piece_symbol - p_erase_count - 1])) {
					//頂点を削除
					give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count - 1);
					give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count - 1);
					give_piece.back().point.erase(give_piece.back().point.end() - 1);
					give_piece.back().angle.erase(give_piece.back().angle.end() - 1);
					if (piece_symbol != 0) {
						p_erase_count += 1;
					}
				}
				else {
					if (fabs(180 - fabs(give_piece.back().angle.back() - give_piece[n].angle[piece_symbol - p_erase_count - 1])) <= 0.50) {
						give_piece.back().point.erase(give_piece.back().point.end() - 1);
						give_piece.back().angle.erase(give_piece.back().angle.end() - 1);
					}
					give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count - 1);
					give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count - 1);
					if (piece_symbol != 0) {
						p_erase_count += 1;
					}
				}
			}
			else {
				break;
			}
		}
		else if (i - f_erase_count != 0 && piece_symbol - p_erase_count == 0) {
			if (give_piece.back().point[i - f_erase_count - 1].first == give_piece[n].point.back().first && give_piece.back().point[i - f_erase_count - 1].second == give_piece[n].point.back().second) {
				if (equal_angle(give_piece.back().angle[i - f_erase_count - 1], give_piece[n].angle.back())) {
					//頂点を削除
					give_piece[n].point.erase(give_piece[n].point.end() - 1);
					give_piece[n].angle.erase(give_piece[n].angle.end() - 1);
					give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count - 1);
					give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count - 1);
					if (i != 0) {
						f_erase_count += 1;
					}
				}
				else {
					if (fabs(180 - fabs(give_piece.back().angle[i - f_erase_count - 1] - give_piece[n].angle.back())) <= 0.50) {
						give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count - 1);
						give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count - 1);
						if (i != 0) {
							f_erase_count += 1;
						}
					}
					give_piece[n].point.erase(give_piece[n].point.end() - 1);
					give_piece[n].angle.erase(give_piece[n].angle.end() - 1);
				}
			}
			else {
				break;
			}
		}*/
	}
	//基準になった頂点の削除
	if (1) {
		int ho_piece = piece_symbol - p_erase_count;
		int ho_frame = i - f_erase_count;
		give_piece[n].point.erase(give_piece[n].point.begin() + ho_piece);
		give_piece[n].angle.erase(give_piece[n].angle.begin() + ho_piece);
		//if (ho_piece != 0){
			p_erase_count += 1;
		give_piece.back().point.erase(give_piece.back().point.begin() + ho_frame);
		give_piece.back().angle.erase(give_piece.back().angle.begin() + ho_frame);
		//if (ho_frame != 0) {
			f_erase_count += 1;
		//}
	}
	//最初に入れる方を挿入
	int hoge = 0;
	for (int t = 0; t - hoge < give_piece[n].point.size(); t++) {
		Circle circle(give_piece[n].point[t - hoge].first, give_piece[n].point[t - hoge].second, 0.5);
		for (int k = 0; k < clone_piece.back().point.size(); k++) {
			LineInt h_line = { clone_piece.back().point[k].first, clone_piece.back().point[k].second,
				clone_piece.back().point[(k + 1 + clone_piece.back().point.size()) % clone_piece.back().point.size()].first, clone_piece.back().point[(k + 1 + clone_piece.back().point.size()) % clone_piece.back().point.size()].second };
			/*if (k == clone_piece.back().point.size() - 1) {
				h_line = { clone_piece.back().point[k].first, clone_piece.back().point[k].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second };
			}
			else {
				h_line = { clone_piece.back().point[k].first, clone_piece.back().point[k].second, clone_piece.back().point[k + 1].first, clone_piece.back().point[k + 1].second };
			}*/
			if (h_line.intersects(circle)) {
				/*if (i - f_erase_count == 0) {
					if (se_count == 0) {
							give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[t]);
							give_piece[n].point.erase(give_piece[n].point.begin() + t);
							se_count += 1;
							incert_count = 1;
							break;
						}
					else if (se_count == 1) {
						//正しい頂点の順に挿入
						give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[t]);
						if (check_overlapping(give_piece)) {
							give_piece.back().point.erase(give_piece.back().point.begin());
							give_piece.back().point.insert(give_piece.back().point.begin(), give_piece[n].point[t]);
						}
						se_count += 1;
						give_piece[n].point.erase(give_piece[n].point.begin() + t);
						break;
					}
				}
				else {*/
					if (se_count == 0) {
						int pos = i - f_erase_count;
						//if (pos != 0) {
						point_iter = ((pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size());
							give_piece.back().point.insert(give_piece.back().point.begin() + ((pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size()), give_piece[n].point[t - hoge]);
							if (pos >= ((pos + give_piece.back().point.size()) % give_piece.back().point.size() - 1)) {
								f_erase_count += 1;
							}
							if (piece_symbol - p_erase_count >= t - hoge) {
								p_erase_count += 1;
							}
							se_count += 1;
							incert_count = 1;
							give_piece[n].point.erase(give_piece[n].point.begin() + (t - hoge));
							hoge = 1;
							break;
						/*}
						else {
							give_piece.back().point.insert(give_piece.back().point.end(), give_piece[n].point[t - hoge]);
							give_piece[n].point.erase(give_piece[n].point.begin() + t - hoge);
							se_count += 1;
							incert_count = 1;
							hoge = 1;
							break;
						}*/
					}
					else if(se_count == 1) {
						int pos = i - f_erase_count;
						//if (pos != 0) {
							give_piece.back().point.insert(give_piece.back().point.begin() + point_iter, give_piece[n].point[t - hoge]);
							if (check_overlapping(give_piece)) {
								give_piece.back().point.erase(give_piece.back().point.begin() + ((pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size()));
								give_piece.back().point.insert(give_piece.back().point.begin() + ((pos + 2 + give_piece.back().point.size()) % give_piece.back().point.size()), give_piece[n].point[t - hoge]);
								if (pos >= (pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size() - 1) {
									f_erase_count += 1;
								}
								if (piece_symbol - p_erase_count >= t - hoge) {
									p_erase_count += 1;
								}
								se_count += 1;
								give_piece[n].point.erase(give_piece[n].point.begin() + (t - hoge));
								break;
							}
							if (pos >= (pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size()) {
								f_erase_count += 1;
							}
							if (piece_symbol - p_erase_count >= t - hoge) {
								p_erase_count += 1;
							}
							se_count += 1;
							give_piece[n].point.erase(give_piece[n].point.begin() + (t - hoge));
							break;
						/*}
						else {
							give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[t - hoge]);
							if (check_overlapping(give_piece)) {
								give_piece.back().point.erase(give_piece.back().point.end() - 1);
								give_piece.back().point.insert(give_piece.back().point.end() - 2, give_piece[n].point[t - hoge]);
							}
							se_count += 1;
							give_piece[n].point.erase(give_piece[n].point.begin() + t - hoge);
							break;
						}*/
					}
			//	}
			}
		}
	}
	//ピースの残りの頂点を反対向きに挿入していく
	if (1) {
		if (incert_count == 1) {
			/*if (i - f_erase_count == 0) {
				if (se_count == 1) {
					for (int k = give_piece[n].point.size() - 1; k >= 0; k--) {
						give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[k]);
					}
					if (check_origin_frame(give_piece, line_piece)||check_overlapping(give_piece)) {
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.erase(give_piece.back().point.end() - 1);
						}
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.insert(give_piece.back().point.begin(),give_piece[n].point[k]);
						}
					}
				}
				else if (se_count == 2) {
					for (int k = give_piece[n].point.size() - 1; k >= 0; k--) {
						give_piece.back().point.insert(give_piece.back().point.end() - 1, give_piece[n].point[k]);
					}
				}
			}
			else {*/
			if (se_count == 1) {
				int pos = i - f_erase_count;
				int hos = piece_symbol - p_erase_count;
				for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.insert(give_piece.back().point.begin() + point_iter, give_piece[n].point[k]);
					}
				if (check_overlapping(give_piece)) {
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.erase(give_piece.back().point.begin() + point_iter);
						}
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.insert(give_piece.back().point.begin() + (point_iter + 1), give_piece[n].point[k]);
						}
					}
				if (check_overlapping(give_piece)) {
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.erase(give_piece.back().point.begin() + (point_iter + 1));
						}
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.insert(give_piece.back().point.begin() + point_iter, give_piece[n].point[(hos - k + give_piece[n].point.size()) % give_piece[n].point.size()]);
						}
					}
				if (check_overlapping(give_piece)) {
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.erase(give_piece.back().point.begin() + point_iter);
						}
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.insert(give_piece.back().point.begin() + point_iter, give_piece[n].point[(hos + k + give_piece[n].point.size()) % give_piece[n].point.size()]);
						}
					}
				if (check_overlapping(give_piece)) {
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.erase(give_piece.back().point.begin() + point_iter);
						}
						for (int k = 0; k < give_piece[n].point.size(); k++) {
							give_piece.back().point.insert(give_piece.back().point.begin() + (point_iter + 1), give_piece[n].point[(hos - k + give_piece[n].point.size()) % give_piece[n].point.size()]);
						}
					}
				if (check_overlapping(give_piece)) {
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.erase(give_piece.back().point.begin() + (point_iter + 1));
					}
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.insert(give_piece.back().point.begin() + (point_iter + 1), give_piece[n].point[(hos + k + give_piece[n].point.size()) % give_piece[n].point.size()]);
					}
				}
			}
			else if (se_count == 2) {
				int pos = i - f_erase_count;
				int hos = piece_symbol - p_erase_count;
				for (int k = 0; k < give_piece[n].point.size(); k++) {
					give_piece.back().point.insert(give_piece.back().point.begin() + point_iter,give_piece[n].point[k]);
				}
				if (check_overlapping(give_piece)) {
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.erase(give_piece.back().point.begin() + point_iter);
					}
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.insert(give_piece.back().point.begin() + (point_iter + 1), give_piece[n].point[k]);
					}
				}
				if (check_overlapping(give_piece)) {
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.erase(give_piece.back().point.begin() +( point_iter + 1));
					}
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.insert(give_piece.back().point.begin() + point_iter, give_piece[n].point[(hos - k + give_piece[n].point.size()) % give_piece[n].point.size()]);
					}
				}
				if (check_overlapping(give_piece)) {
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.erase(give_piece.back().point.begin() + point_iter);
					}
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.insert(give_piece.back().point.begin() + (point_iter + 1), give_piece[n].point[(hos + k + give_piece[n].point.size()) % give_piece[n].point.size()]);
					}
				}
				if (check_overlapping(give_piece)) {
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.erase(give_piece.back().point.begin() + (point_iter + 1));
					}
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.insert(give_piece.back().point.begin() + (point_iter + 1), give_piece[n].point[(hos + k + give_piece[n].point.size()) % give_piece[n].point.size()]);
					}
				}
				if (check_overlapping(give_piece)) {
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.erase(give_piece.back().point.begin() + (point_iter + 1));
					}
					for (int k = 0; k < give_piece[n].point.size(); k++) {
						give_piece.back().point.insert(give_piece.back().point.begin() + (point_iter + 1), give_piece[n].point[(hos - k + give_piece[n].point.size()) % give_piece[n].point.size()]);
					}
				}
			}
		}
		else if (incert_count == 0) {
			int pos = i - f_erase_count;
			int hos = piece_symbol - p_erase_count;
			for (int k = 0; k < give_piece[n].point.size(); k++) {
				give_piece.back().point.insert(give_piece.back().point.begin() + ((pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size()), give_piece[n].point[k]);
			}
			if (check_overlapping(give_piece)) {
				for (int k = 0; k < give_piece[n].point.size(); k++) {
					give_piece.back().point.erase(give_piece.back().point.begin() + ((pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size()));
				}
				for (int k = 0; k < give_piece[n].point.size(); k++) {
					give_piece.back().point.insert(give_piece.back().point.begin() + ((pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size()), give_piece[n].point[(hos - k + give_piece[n].point.size()) % give_piece[n].point.size()]);
				}
			}
			if (check_overlapping(give_piece) || check_origin_frame(give_piece, line_piece)) {
				for (int k = 0; k < give_piece[n].point.size(); k++) {
					give_piece.back().point.erase(give_piece.back().point.begin() + ((pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size()));
				}
				for (int k = 0; k < give_piece[n].point.size(); k++) {
					give_piece.back().point.insert(give_piece.back().point.begin() + ((pos + 1 + give_piece.back().point.size()) % give_piece.back().point.size()), give_piece[n].point[(hos + k + give_piece[n].point.size()) % give_piece[n].point.size()]);
				}
			}
		}
	}
	//描写
	for (int j = 0; j < give_piece.back().point.size(); j++) {
		if (j == give_piece.back().point.size() - 1) {
			LineInt(give_piece.back().point[j].first * 5, give_piece.back().point[j].second * 5, give_piece.back().point[0].first * 5, give_piece.back().point[0].second * 5).draw(Palette::Black);
		}
		else {
			LineInt(give_piece.back().point[j].first * 5, give_piece.back().point[j].second * 5, give_piece.back().point[j + 1].first * 5, give_piece.back().point[j + 1].second * 5).draw(Palette::Black);
		}
	}
	System::Update();
	//わくが分離するのを防ぐ
	for (int k = 0; k < give_piece.back().point.size(); k++) {
		for (int n = 0; n < give_piece.back().point.size();n++) {
			if (give_piece.back().point[k].first == give_piece.back().point[(k + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first) {
				if (give_piece.back().point[k].second == give_piece.back().point[(k + 1 + give_piece.back().point.size())%give_piece.back().point.size()].second) {
					return false;
				}
			}
		}
	}
	//多角形が成立するかどうかを判定
	if (check_overlapping(give_piece)) {
		return false;
	}
	//三角形になった場合を判定
	/*if (give_piece.back().point.size() == 3) {
		return false;
	}*/
	//更新した情報の共有
	if (1) {
		new_frame = give_piece.back().point;
		give_piece = clone_piece;
		give_piece.back().point.clear();
		give_piece.back().point = new_frame;
		give_piece.erase(give_piece.begin() + n);
	}
	//小さい角を除外
	for (int i = 0; i < give_piece.back().angle.size(); i++) {
		if (give_piece.back().angle[i] < 3) {
			return false;
		}
		if (give_piece.back().angle[i] > 357) {
			return false;
		}
	}
	//小さい辺を除外
	for (int i = 0; i < give_piece.back().line.size(); i++) {
		if (give_piece.back().line[i] < 1) {
		return false;
		}
	}
	//スクショの保存&&再帰
	if (give_piece.back().point.size() == 0 && give_piece.size() == 1) {
		Control cont;
		cont.output_piece(ans_piece);
		system_end = 1;
	}
	else {
		//再帰
		fit_piece(give_piece);
	}
	return true;
}

void Algorithm::select_piece(int i, vector<Piece> &clone_piece,int sele) {
	//評価点が高いピースがあるならupdate_piece()へ
	/*評価点が高いピースがあるなら正*/
	//ピースの番号を決定
	for (int n = 0; n < (clone_piece.size() - 1); n++) {
		//ピースの角(頂点)決定
		for (int k = 0; k < (clone_piece[n].point.size() - 1); k++) {
			if (three_evalution[flag][n][k] == sele) {
				if (system_end) {
					break;
				}
				//ピースの番号,枠の頂点を引数
				update_frame(n, i, k,clone_piece);
			}
		}
	}
}

bool Algorithm::check_collision(int n,vector<Piece> &clone_piece) {
	//ピースが枠から出てるならTrue
	int count_x, count_y;
	//頂点が外に出ているピースの判定
	for (int j = 0; j < clone_piece[n].point.size(); j++) {
		count_x = 0;
		count_y = 0;
		//y軸へ延長した線分
		//x軸へ延長した線分
		Circle circle(clone_piece[n].point[j].first, clone_piece[n].point[j].second,0.1);
		Line y_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point[j].first, 200);
		Line x_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, 200, clone_piece[n].point[j].second);
		for (int i = 0; i < clone_piece.back().point.size(); i++) {
			//枠の各辺との交わりをカウント
			if (i == clone_piece.back().point.size() - 1) {
				Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second);
				if (f_line.intersects(circle)) {
					count_x = 1;
					count_y = 1;
					break;
				}
				//x軸に伸ばした線分
				if (clone_piece[n].point[j].second == clone_piece.back().point[i].second && clone_piece[n].point[j].second == clone_piece.back().point.front().second) {

				}
				else if (clone_piece[n].point[j].second == clone_piece.back().point[i].second || clone_piece[n].point[j].second == clone_piece.back().point.front().second) {

				}
				else if (x_line.intersects(f_line)) {
						count_x += 1;
				}
				//y軸に伸ばした線分
				if (clone_piece[n].point[j].first == clone_piece.back().point[i].first && clone_piece[n].point[j].first == clone_piece.back().point.front().first) {

				}
				else if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point[j].first == clone_piece.back().point.front().first) {

				}
				else if (y_line.intersects(f_line)) {
					count_y += 1;
				}
			}
			else {
				Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point[i + 1].first, clone_piece.back().point[i + 1].second);
				if (f_line.intersects(circle)) {
					count_x = 1;
					count_y = 1;
					break;
				}
				//x軸に伸ばした線分
				if (clone_piece[n].point[j].second == clone_piece.back().point[i].second && clone_piece[n].point[j].second == clone_piece.back().point[i + 1].second) {

					}
				else if (clone_piece[n].point[j].second == clone_piece.back().point[i].second || clone_piece[n].point[j].second == clone_piece.back().point[i + 1].second) {

					}
				else if (x_line.intersects(f_line)) {
						count_x += 1;
					}
				//y軸に伸ばした線分
				if (clone_piece[n].point[j].first == clone_piece.back().point[i].first && clone_piece[n].point[j].first == clone_piece.back().point[i + 1].first) {

					}
				else if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point[j].first == clone_piece.back().point[i + 1].first) {

					}
				else if (y_line.intersects(f_line)) {
						count_y += 1;
					}
			}
		}
		//偶数なら枠の外側の頂点
		if (count_x % 2 == 0 || count_y % 2 == 0) {
			return true;
		}
 	}
	//頂点が外に出ていないピースの判定
	//例外があるため保留
/*	for (int j = 0; j < clone_piece[n].point.size(); j++) {
		count = 0;
		for (int i = 0; i < clone_piece.back().point.size(); i++) {
			if (i == clone_piece.back().point.size() - 1) {
				if (j == clone_piece[n].point.size() - 1) {
					Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second);
					Line p_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point.front().first, clone_piece[n].point.front().second);
					if (clone_piece[n].point[j].first == clone_piece.back().point[i].first 
						|| clone_piece[n].point.front().first == clone_piece.back().point.front().first) {
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
						//int hoge;
					}
					 if (f_line.intersects(p_line)) {
						count += 1;
					}
				}
			}
		}
		if (count >= 2) {
			return true;
		}
	}
	*/
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
	double x_point[16] = { -0.20, 0.20, 0.40, 0.50, 0.50,0.50,0.50,0.40,0.20,-0.20,-0.40,-0.50,-0.50,-0.50,-0.50,-0.40 };
	double y_point[16] = { -0.50,-0.50,-0.50,-0.40,-0.20,0.20,0.40,0.50,0.50, 0.50, 0.50, 0.40, 0.20,-0.20,-0.40,-0.50 };
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

bool Algorithm::check_overlapping(vector<Piece> &give_piece){
	//貰った枠が正しい多角形でないならTrue
	//隣の辺の比較用
	int line_count = 0;
	//LineInt fuga_line(0, 0, 0, 0);
	//LineInt hoge_line(0, 0, 0, 0);

	for (int k = 0; k < give_piece.back().point.size(); k++) {
		//LineInt fuga_line( give_piece.back().point[k].first ,give_piece.back().point[k].second,give_piece.back().point[(k + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first,give_piece.back().point[(k + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second );
		for (int t = 0; t < give_piece.back().point.size(); t++) {
			//LineInt hoge_line(give_piece.back().point[t].first ,give_piece.back().point[t].second,give_piece.back().point[(t + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first,give_piece.back().point[(t + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second);
			if (closs_line(give_piece.back().point[k].first, give_piece.back().point[k].second, give_piece.back().point[(k + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first, give_piece.back().point[(k + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second,give_piece.back().point[t].first, give_piece.back().point[t].second, give_piece.back().point[(t + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first, give_piece.back().point[(t + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second)) {
				//if (hoge_line.intersects(fuga_line)) {
					line_count += 1;
				//}
			}
		}
		if (line_count > 0) {
			return true;
		}
		line_count = 0;
	}
	return false;
}

void Algorithm::turn_piece(int n, vector<Piece> &clone_piece) {
	/*
	ピースの番号を受け取る
	ピースを反転させ、頂点情報を更新
	axis一番X座標の小さい値が入ってる要素数
	*/
	int mini_point_x = 100, axis = 0;

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
	if (fabs(first_angle - second_angle) <= 2.0) {
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
	
	if (fabs(first_line - second_line) <= 1.0) {
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
		//当てはまるならTrue
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
				clone_piece[n] = base;
				collision_no = 0;
				return false;
		}
		if (collision == false) {
				collision_no = 0;
				return true;
		}
		return true;
}

bool Algorithm::closs_line(double ax, double ay, double bx,double by,double cx,double cy,double dx,double dy) {
	double ta, tb, tc, td;

	if (ax == bx && ax == cx && ax == dx) {
		if (ax > bx) {
			if (!(ax > cx && bx < cx || ax > dx && bx < dx)) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (ax < bx) {
			if (!(bx > cx && ax < cx || bx > dx && ax < dx)) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	if (ay == by && ay == cy && ay == dy) {
		if (ay > by) {
			if (!(ay >= cy && by <= cy || ay >= dy && by <= dy)) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (ay < by) {
			if (!(by >= cy && ay <= cy || by >= dy && ay <= dy)) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
	tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
	tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
	td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);
	if (tc * td < 0 && ta * tb < 0) {
		return true;
	}
	return false;
}

bool Algorithm::check_origin_frame(vector<Piece> &give_piece,vector<pair<int,int> >&line_piece){
	//辺の中点が内側に入ってるならTrue
	int count = 0;
	for (int n = 0; n < give_piece.back().point.size(); n++) {
		Circle circle(((give_piece.back().point[n].first + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first) / 2.0),
			((give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0), 1);
		for (int k = 0; k < line_piece.size(); k++) {
			LineInt p_line(line_piece[k].first, line_piece[k].second, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].first, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].second);
			/*circle.draw(Palette::Red);
			p_line.draw(Palette::Blue);
			//描写
			for (int j = 0; j < give_piece.back().point.size(); j++) {
				if (j == give_piece.back().point.size() - 1) {
					LineInt(give_piece.back().point[j].first * 5, give_piece.back().point[j].second * 5, give_piece.back().point[0].first * 5, give_piece.back().point[0].second * 5).draw(Palette::Black);
				}
				else {
					LineInt(give_piece.back().point[j].first * 5, give_piece.back().point[j].second * 5, give_piece.back().point[j + 1].first * 5, give_piece.back().point[j + 1].second * 5).draw(Palette::Black);
				}
			}
			System::Update();*/
			if (!(circle.intersects(p_line))) {
				/*Polygon shape; 
				switch (line_piece.size()) {
				case 3:
				{
					shape = { { line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second } };
					break;
				}
				case 4:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second }
					};
					break;
				}
				case 5:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second }
					};
					break;
				}
				case 6:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second }
					};
					break;
				}
				case 7:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second }
					};
					break;
				}
				case 8:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second }
					};
					break;
				}
				case 9:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second },{ line_piece[8].first,line_piece[8].second }
					};
					break;
				}
				case 10:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second },{ line_piece[8].first,line_piece[8].second },
						{ line_piece[9].first,line_piece[9].second }
					};
					break;
				}
				case 11:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second },{ line_piece[8].first,line_piece[8].second },
						{ line_piece[9].first,line_piece[9].second },{ line_piece[10].first,line_piece[10].second }
					};
					break;
				}
				case 12:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second },{ line_piece[8].first,line_piece[8].second },
						{ line_piece[9].first,line_piece[9].second },{ line_piece[10].first,line_piece[10].second },{ line_piece[11].first,line_piece[11].second }
					};
					break;
				}
				case 13:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second },{ line_piece[8].first,line_piece[8].second },
						{ line_piece[9].first,line_piece[9].second },{ line_piece[10].first,line_piece[10].second },{ line_piece[11].first,line_piece[11].second },
						{ line_piece[12].first,line_piece[12].second }
					};
					break;
				}
				case 14:
				{shape = {
					{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
					{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
					{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second },{ line_piece[8].first,line_piece[8].second },
					{ line_piece[9].first,line_piece[9].second },{ line_piece[10].first,line_piece[10].second },{ line_piece[11].first,line_piece[11].second },
					{ line_piece[12].first,line_piece[12].second },{ line_piece[13].first,line_piece[13].second }
				};
				break;
				}
				case 15:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second },{ line_piece[8].first,line_piece[8].second },
						{ line_piece[9].first,line_piece[9].second },{ line_piece[10].first,line_piece[10].second },{ line_piece[11].first,line_piece[11].second },
						{ line_piece[12].first,line_piece[12].second },{ line_piece[13].first,line_piece[13].second },{ line_piece[14].first,line_piece[14].second }
					};
					break;
				}
				case 16:
				{
					shape = {
						{ line_piece[0].first,line_piece[0].second },{ line_piece[1].first,line_piece[1].second },{ line_piece[2].first,line_piece[2].second },
						{ line_piece[3].first,line_piece[3].second },{ line_piece[4].first,line_piece[4].second },{ line_piece[5].first,line_piece[5].second },
						{ line_piece[6].first,line_piece[6].second },{ line_piece[7].first,line_piece[7].second },{ line_piece[8].first,line_piece[8].second },
						{ line_piece[9].first,line_piece[9].second },{ line_piece[10].first,line_piece[10].second },{ line_piece[11].first,line_piece[11].second },
						{ line_piece[12].first,line_piece[12].second },{ line_piece[13].first,line_piece[13].second },{ line_piece[14].first,line_piece[14].second },
						{ line_piece[15].first,line_piece[15].second }
					};
					break;
				}
				}
				if (circle.contains(shape)) {
					return true;
				}*/
				for (int j = 0; j < line_piece.size(); j++) {
					if (closs_line(((give_piece.back().point[n].first + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first) / 2.0 + 0.25),
						((give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0 + 0.25), 200.0,
						((give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0 + 0.25),
						line_piece[j].first * 1.0, line_piece[j].second * 1.0, line_piece[(j + 1 + line_piece.size()) % line_piece.size()].first * 1.0, line_piece[(j + 1 + line_piece.size()) % line_piece.size()].second  * 1.0)) {
						count += 1;
					}
					if (count % 2 == 1) {
						return true;
					}
					count = 0;
				}
			}
		}
	}
	/*int origin_count = 0;

	for (int n = 0; n < give_piece.back().point.size(); n++) {
		Line give_line((give_piece.back().point[n].first + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first) / 2.0, (give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0,
						200, (give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0);
		for (int k = 0; k < line_piece.size(); k++) {
			LineInt p_line(line_piece[k].first, line_piece[k].second, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].first, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].second);
		//	if (give_line.intersects(p_line)) {
				if (closs_line((give_piece.back().point[n].first + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first) / 2.0,(give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0,200,(give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0, line_piece[k].first, line_piece[k].second, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].first, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].second)){
					Line((give_piece.back().point[n].first + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first) / 2.0 * 5, (give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0 * 5,
						200, (give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0 * 5).draw(Palette::Black);
					Line(line_piece[k].first * 5, line_piece[k].second * 5, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].first * 5, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].second * 5).draw(Palette::Black);
					System::Update();
					origin_count += 1;
				}
			//}
		}
		if (origin_count % 2 == 1) {
			return true;
		}
		origin_count = 0;
	}*/
	return false;
}
