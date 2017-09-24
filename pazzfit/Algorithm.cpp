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
	//�s�[�X�Ƃ߂�A���S���Y�����܂Ƃ߂�
	//�g�̊�ƂȂ钸�_������
	for (int i = 0; i < clone_piece.back().point.size(); i++) {
		evaluation(i, clone_piece);
		select_piece(i,clone_piece);
		three_evalution.pop_back();
	}
	flag += 1;
}

void Algorithm::evaluation(int i,vector<Piece> &clone_piece) {
	//�g�E�s�[�X�̒��_�E�p�x�E�ӂ̒������󂯎��
	//�s�[�X�Ƙg�̕]���_���쐬
	//�s�[�X�������
	for (int n = 0; n < (clone_piece.size() - 1); n++) {
		//�s�[�X�̊p(���_)�������
		for (int k = 0; k < clone_piece[n].angle.size(); k++) {
			//�g�ƃs�[�X�̊p�x���r
			one_evalution.push_back(0);

			if (equal_angle(clone_piece.back().angle[i], clone_piece[n].angle[k])) {
				one_evalution[k] = 1;
				//���̗��[�̕ӂ���r
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
	//��̃s�[�X�̊p�x�E�ӂ��󂯎��
	//�s�[�X���m�̕]���_���쐬
	//�]���_�����Ƀs�[�X������
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
	//ans_point�ւ̑��;
	piece[n].ans_point = clone_piece[n].point;
	//������߂�
	for (int k = 0; k < clone_piece[n].point.size(); k++) {
		if (clone_piece.back().point[i].first == clone_piece[n].point[k].first && clone_piece.back().point[i].second == clone_piece[n].point[k].second) {
			piece_symbol = k;
			break;
		}
	}
	//�E���ɒ��_��������&���̊p�x���������ꍇ���O
	for (int t = 1; t < clone_piece[n].point.size(); t++) {
		if (piece_symbol + t > clone_piece[n].point.size() - 1) {
			break;
		}
		if (i + t > clone_piece.back().point.size() - 1) {
			break;
		}
		if (clone_piece.back().point[i + t].first == clone_piece[n].point[piece_symbol + t].first && clone_piece.back().point[i + t].second == clone_piece[n].point[piece_symbol + t].second) {
			if (clone_piece.back().angle[i + t] == clone_piece[n].angle[piece_symbol + t]) {
				//���_���폜
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
	//�����ɒ��_��������&���̊p�x���������ꍇ���O
	for (int t = 1; t < clone_piece.back().point.size(); t++) {
		if (piece_symbol - t < 0) {
			break;
		}
		if (i - t < 0) {
			break;
		}
		if (clone_piece.back().point[i - t].first == clone_piece[n].point[piece_symbol - t].first && clone_piece.back().point[i - t].second == clone_piece[n].point[piece_symbol - t].second) {
			if (clone_piece.back().angle[i - t] == clone_piece[n].angle[piece_symbol - t]) {
				//���_���폜
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
	//��ɂȂ������_�̍폜
	give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol - p_erase_count);
	give_piece[n].angle.erase(give_piece[n].angle.begin() + piece_symbol - p_erase_count);
	give_piece.back().point.erase(give_piece.back().point.begin() + i - f_erase_count);
	give_piece.back().angle.erase(give_piece.back().angle.begin() + i - f_erase_count);
	//�ŏ��ɓ�������}��
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
							//�Ƃ߂�s�[�X����O�̒��_�Ƌ߂����𔻒�
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
							//�Ƃ߂�s�[�X����O�̒��_�Ƌ߂����𔻒�
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
							//�Ƃ߂�s�[�X����O�̒��_�Ƌ߂����𔻒�
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
							//�Ƃ߂�s�[�X����O�̒��_�Ƌ߂����𔻒�
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
	//�s�[�X�̎c��̒��_�𔽑Ό����ɑ}�����Ă���
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

	//�X�V�������̋��L
	new_frame = give_piece.back().point;
	give_piece = clone_piece;
	give_piece.back().point.clear();
	give_piece.back().point = new_frame;
	give_piece.back().ans_point.clear();
	give_piece.back().ans_point = new_frame;
	give_piece.erase(give_piece.begin() + n);
	//�g�̕ӁA�p�x�̍X�V
	sort_frame(give_piece);
	//�X�N�V���̕ۑ�
	if (give_piece.back().point.size() == 0) {
		Control cont;
		cont.output_piece(give_piece);

	}
	else {
		//�ċA
		fit_piece(give_piece);
	}
	return true;
}

void Algorithm::select_piece(int i, vector<Piece> &clone_piece) {
	//�]���_�������s�[�X������Ȃ�update_piece()��
	/*�]���_�������s�[�X������Ȃ琳*/
	//�s�[�X�̔ԍ�������
	for (int n = 0; n < (clone_piece.size() - 1); n++) {
		//�s�[�X�̊p(���_)����
		for (int k = 0; k < (clone_piece[n].point.size() - 1); k++) {
			if (three_evalution[flag][n][k] == 3) {
			//�s�[�X�̔ԍ�,�g�̒��_������
			update_frame(n, i, k,clone_piece);
			}
		}
	}
	for (int n = 0; n < (clone_piece.size()- 1); n++) {
		//�s�[�X�̊p(���_)����
		for (int k = 0; k < (clone_piece[n].point.size() - 1); k++) {
			if (three_evalution[flag][n][k] == 2) {
				//�s�[�X�̔ԍ�,�g�̒��_������
				update_frame(n, i, k, clone_piece);
			}
		}
	}
	for (int n = 0; n < (clone_piece.size() - 1); n++) {
		//�s�[�X�̊p(���_)����
		for (int k = 0; k < (clone_piece[n].point.size() - 1); k++) {
			if (three_evalution[flag][n][k] == 1) {
				//�s�[�X�̔ԍ�,�g�̒��_������
				update_frame(n, i,k, clone_piece);
			}
		}
	}
}

bool Algorithm::check_collision(int n,vector<Piece> &clone_piece) {
	//�s�[�X���g����o�Ă�Ȃ�True
	int count_x, count_y;
	int count;
	
	//���_���O�ɏo�Ă���s�[�X�̔���
	for (int j = 0; j < clone_piece[n].point.size(); j++) {
		count_x = 0;
		count_y = 0;
		//y���։�����������
		//x���։�����������
		Line y_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point[j].first, 200);
		Line x_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, 200, clone_piece[n].point[j].second);
		for (int i = 0; i < clone_piece.back().point.size(); i++) {
			//�g�̊e�ӂƂ̌������J�E���g
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
		//�����Ȃ�g�̊O���̒��_
		if (count_x % 2 == 0 && count_y % 2 == 0) {
			return true;
		}
 	}
	//���_���O�ɏo�Ă��Ȃ��s�[�X�̔���
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
	//���_����ӁA�p�x�̎Z�o
	//���̕ӂ��폜
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
	//���̊p�x�̍폜
	give_piece.back().angle.clear();
	//16�����Q�Ƃ��邽�߂̔z��
	double x_point[16] = { 0,0.25,0.5,0.5,0.5,0.5,0.5,0.25,0,-0.25,-0.5,-0.5,-0.5,-0.5,-0.5,-0.25 };
	double y_point[16] = { -0.5,-0.5,-0.5,-0.25,0,0.25,0.5,0.5,0.5,0.5,0.5,0.25,0,-0.25,-0.5,-0.5 };
	//��������ӂ��J�E���g���邽�߂̕ϐ�
	int count_x, count_y;

	for (int j = 0; j < give_piece.back().point.size(); j++) {
		int check_angle = 0;
		for (int k = 0; k < 16; k++) {
			count_x = 0;
			count_y = 0;
			//y���։�����������
			//x���։�����������
			Line y_line(give_piece.back().point[j].first + x_point[k], give_piece.back().point[j].second + y_point[k], give_piece.back().point[j].first,200);
			Line x_line(give_piece.back().point[j].first + x_point[k], give_piece.back().point[j].second + y_point[k], 200, give_piece.back().point[j].second);
			for (int i = 0; i < give_piece.back().point.size(); i++) {
				//�g�̊e�ӂƂ̌������J�E���g
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
			//��Ȃ�g�̓����̒��_
			if (count_x % 2 == 1 || count_y % 2 == 1) {
				check_angle += 1;
			}
		}
		//�K�v�ȕϐ�
		double a1, a2, b1, b2;
		double a, b, c, d;
		double angle;
		//��̒��_����̃x�N�g������
		a1 = give_piece.back().point[(j + 1) % give_piece.back().point.size()].first - give_piece.back().point[j].first;
		a2 = give_piece.back().point[(j + 1) % give_piece.back().point.size()].second - give_piece.back().point[j].second;
		b1 = give_piece.back().point[(j + give_piece.back().point.size() - 1) % give_piece.back().point.size()].first - give_piece.back().point[j].first;
		b2 = give_piece.back().point[(j + give_piece.back().point.size() - 1) % give_piece.back().point.size()].second - give_piece.back().point[j].second;
		//�x�N�g���̓���
		a = a1 * b1;
		b = a2 * b2;
		c = sqrt(pow(a1, 2) + pow(a2, 2));
		d = sqrt(pow(b1, 2) + pow(b2, 2));
		angle = (a + b) / (c * d);
		angle = acos(angle);
		angle = angle * 180 / Pi;
		//���p�ł���
		if (check_angle >= 9) {
			angle = 360 - angle;
			give_piece.back().angle.push_back(angle);
		}
		//�ʊp�ł���
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
	�s�[�X�̔ԍ����󂯎��
	�s�[�X�𔽓]�����A���_�����X�V
	axis���X���W�̏������l�������Ă�v�f��
	*/
	int mini_point_x = 100, axis = 0;
	int minus = 0;

	//��ƂȂ���W�̌���
	for (int i = 0; i < clone_piece[n].point.size(); i++) {
		if (mini_point_x > clone_piece[n].point[i].first) {
			mini_point_x = clone_piece[n].point[i].first;
			axis = i;
		}
	}

	//���]
	for (int i = 0; i < clone_piece[n].point.size(); i++) {
		clone_piece[n].point[i].first = clone_piece[n].point[axis].first -
			(clone_piece[n].point[i].first - clone_piece[n].point[axis].first);
	}
}

void Algorithm::spin90_piece(int n,vector<Piece> &clone_piece) {
	/*
	�s�[�X��90�x����]������
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
	�s�[�X��180�x����]������
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
	�s�[�X��270�x����]������
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
	�g�ƃs�[�X�̊p�x�̏����󂯎��
	�����덷�͈͓̔��œ������Ȃ��True
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
	�g�ƃs�[�X�̕ӏ����󂯎��
	�����덷�͈͓̔��œ������Ȃ��True
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
	�g�ƃs�\�X�̒��_���W���󂯎��
	�������_���W�������Ȃ��True��Ԃ�
	*/
	if (first_point == second_point) {
		return true;
	}
	else {
		return false;
	}
}

bool Algorithm::collision_checker(int n,int i,int q,vector<Piece> &clone_piece) {
		//��],���],�����蔻��ɂ���ē��Ă͂܂邩����
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
