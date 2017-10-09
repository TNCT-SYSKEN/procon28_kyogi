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
	
	//�s�[�X�Ƃ߂�A���S���Y�����܂Ƃ߂�
	//�g�̊�ƂȂ钸�_������
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
	//��̃s�[�X�̊p�x�E�ӂ��󂯎��
	//�s�[�X���m�̕]���_���쐬
	//�]���_�����Ƀs�[�X������
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

	//��]�`�F�b�N
	if (!(collision_checker(n, i, q, give_piece))) {
		return false;
	}
	//�}�C�i�X���W�Ȃ珜�O
	for (int j = 0; j < give_piece[n].point.size(); j++) {
		if (give_piece[n].point[j].first * -1 > 0 || give_piece[n].point[j].second * -1 > 0) {
			return false;
		}
	}
	//ans_point�ւ̑��;
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
	//������߂�
	int fuga = 1;
	/*for (int k = 0; k < give_piece[n].point.size(); k++) {
		if (give_piece.back().point[i].first == give_piece[n].point[k].first && give_piece.back().point[i].second == give_piece[n].point[k].second) {
			piece_symbol = k;
			break;
		}
	}*/
	piece_symbol = q;
	//�E���ɒ��_��������&���̊p�x���������ꍇ���O
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
					//���_���폜
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
					//���_���폜
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
					//���_���폜
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
					//���_���폜
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
	//�����ɒ��_��������&���̊p�x���������ꍇ���O
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
					//���_���폜
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
					//���_���폜
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
					//���_���폜
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
					//���_���폜
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
	//��ɂȂ������_�̍폜
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
	//�ŏ��ɓ�������}��
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
						//���������_�̏��ɑ}��
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
	//�s�[�X�̎c��̒��_�𔽑Ό����ɑ}�����Ă���
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
	//�`��
	for (int j = 0; j < give_piece.back().point.size(); j++) {
		if (j == give_piece.back().point.size() - 1) {
			LineInt(give_piece.back().point[j].first * 5, give_piece.back().point[j].second * 5, give_piece.back().point[0].first * 5, give_piece.back().point[0].second * 5).draw(Palette::Black);
		}
		else {
			LineInt(give_piece.back().point[j].first * 5, give_piece.back().point[j].second * 5, give_piece.back().point[j + 1].first * 5, give_piece.back().point[j + 1].second * 5).draw(Palette::Black);
		}
	}
	System::Update();
	//�킭����������̂�h��
	for (int k = 0; k < give_piece.back().point.size(); k++) {
		for (int n = 0; n < give_piece.back().point.size();n++) {
			if (give_piece.back().point[k].first == give_piece.back().point[(k + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first) {
				if (give_piece.back().point[k].second == give_piece.back().point[(k + 1 + give_piece.back().point.size())%give_piece.back().point.size()].second) {
					return false;
				}
			}
		}
	}
	//���p�`���������邩�ǂ����𔻒�
	if (check_overlapping(give_piece)) {
		return false;
	}
	//�O�p�`�ɂȂ����ꍇ�𔻒�
	/*if (give_piece.back().point.size() == 3) {
		return false;
	}*/
	//�X�V�������̋��L
	if (1) {
		new_frame = give_piece.back().point;
		give_piece = clone_piece;
		give_piece.back().point.clear();
		give_piece.back().point = new_frame;
		give_piece.erase(give_piece.begin() + n);
	}
	//�������p�����O
	for (int i = 0; i < give_piece.back().angle.size(); i++) {
		if (give_piece.back().angle[i] < 3) {
			return false;
		}
		if (give_piece.back().angle[i] > 357) {
			return false;
		}
	}
	//�������ӂ����O
	for (int i = 0; i < give_piece.back().line.size(); i++) {
		if (give_piece.back().line[i] < 1) {
		return false;
		}
	}
	//�X�N�V���̕ۑ�&&�ċA
	if (give_piece.back().point.size() == 0 && give_piece.size() == 1) {
		Control cont;
		cont.output_piece(ans_piece);
		system_end = 1;
	}
	else {
		//�ċA
		fit_piece(give_piece);
	}
	return true;
}

void Algorithm::select_piece(int i, vector<Piece> &clone_piece,int sele) {
	//�]���_�������s�[�X������Ȃ�update_piece()��
	/*�]���_�������s�[�X������Ȃ琳*/
	//�s�[�X�̔ԍ�������
	for (int n = 0; n < (clone_piece.size() - 1); n++) {
		//�s�[�X�̊p(���_)����
		for (int k = 0; k < (clone_piece[n].point.size() - 1); k++) {
			if (three_evalution[flag][n][k] == sele) {
				if (system_end) {
					break;
				}
				//�s�[�X�̔ԍ�,�g�̒��_������
				update_frame(n, i, k,clone_piece);
			}
		}
	}
}

bool Algorithm::check_collision(int n,vector<Piece> &clone_piece) {
	//�s�[�X���g����o�Ă�Ȃ�True
	int count_x, count_y;
	//���_���O�ɏo�Ă���s�[�X�̔���
	for (int j = 0; j < clone_piece[n].point.size(); j++) {
		count_x = 0;
		count_y = 0;
		//y���։�����������
		//x���։�����������
		Circle circle(clone_piece[n].point[j].first, clone_piece[n].point[j].second,0.1);
		Line y_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, clone_piece[n].point[j].first, 200);
		Line x_line(clone_piece[n].point[j].first, clone_piece[n].point[j].second, 200, clone_piece[n].point[j].second);
		for (int i = 0; i < clone_piece.back().point.size(); i++) {
			//�g�̊e�ӂƂ̌������J�E���g
			if (i == clone_piece.back().point.size() - 1) {
				Line f_line(clone_piece.back().point[i].first, clone_piece.back().point[i].second, clone_piece.back().point.front().first, clone_piece.back().point.front().second);
				if (f_line.intersects(circle)) {
					count_x = 1;
					count_y = 1;
					break;
				}
				//x���ɐL�΂�������
				if (clone_piece[n].point[j].second == clone_piece.back().point[i].second && clone_piece[n].point[j].second == clone_piece.back().point.front().second) {

				}
				else if (clone_piece[n].point[j].second == clone_piece.back().point[i].second || clone_piece[n].point[j].second == clone_piece.back().point.front().second) {

				}
				else if (x_line.intersects(f_line)) {
						count_x += 1;
				}
				//y���ɐL�΂�������
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
				//x���ɐL�΂�������
				if (clone_piece[n].point[j].second == clone_piece.back().point[i].second && clone_piece[n].point[j].second == clone_piece.back().point[i + 1].second) {

					}
				else if (clone_piece[n].point[j].second == clone_piece.back().point[i].second || clone_piece[n].point[j].second == clone_piece.back().point[i + 1].second) {

					}
				else if (x_line.intersects(f_line)) {
						count_x += 1;
					}
				//y���ɐL�΂�������
				if (clone_piece[n].point[j].first == clone_piece.back().point[i].first && clone_piece[n].point[j].first == clone_piece.back().point[i + 1].first) {

					}
				else if (clone_piece[n].point[j].first == clone_piece.back().point[i].first || clone_piece[n].point[j].first == clone_piece.back().point[i + 1].first) {

					}
				else if (y_line.intersects(f_line)) {
						count_y += 1;
					}
			}
		}
		//�����Ȃ�g�̊O���̒��_
		if (count_x % 2 == 0 || count_y % 2 == 0) {
			return true;
		}
 	}
	//���_���O�ɏo�Ă��Ȃ��s�[�X�̔���
	//��O�����邽�ߕۗ�
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
	double x_point[16] = { -0.20, 0.20, 0.40, 0.50, 0.50,0.50,0.50,0.40,0.20,-0.20,-0.40,-0.50,-0.50,-0.50,-0.50,-0.40 };
	double y_point[16] = { -0.50,-0.50,-0.50,-0.40,-0.20,0.20,0.40,0.50,0.50, 0.50, 0.50, 0.40, 0.20,-0.20,-0.40,-0.50 };
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

bool Algorithm::check_overlapping(vector<Piece> &give_piece){
	//������g�����������p�`�łȂ��Ȃ�True
	//�ׂ̕ӂ̔�r�p
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
	�s�[�X�̔ԍ����󂯎��
	�s�[�X�𔽓]�����A���_�����X�V
	axis���X���W�̏������l�������Ă�v�f��
	*/
	int mini_point_x = 100, axis = 0;

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
	if (fabs(first_angle - second_angle) <= 2.0) {
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
	
	if (fabs(first_line - second_line) <= 1.0) {
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
		//���Ă͂܂�Ȃ�True
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
	//�ӂ̒��_�������ɓ����Ă�Ȃ�True
	int count = 0;
	for (int n = 0; n < give_piece.back().point.size(); n++) {
		Circle circle(((give_piece.back().point[n].first + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].first) / 2.0),
			((give_piece.back().point[n].second + give_piece.back().point[(n + 1 + give_piece.back().point.size()) % give_piece.back().point.size()].second) / 2.0), 1);
		for (int k = 0; k < line_piece.size(); k++) {
			LineInt p_line(line_piece[k].first, line_piece[k].second, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].first, line_piece[(k + 1 + line_piece.size()) % line_piece.size()].second);
			/*circle.draw(Palette::Red);
			p_line.draw(Palette::Blue);
			//�`��
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
