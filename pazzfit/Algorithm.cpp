#include "Algorithm.h"

Algorithm::Algorithm() {
	init();
}

void Algorithm::init() {
	flag = -1;
	three_evalution.clear();
}

void Algorithm::fit_piece(vector<Piece> clone_piece) {
	flag++;
	if (flag == 0) {
		piece = clone_piece;
	}
	//�s�[�X�Ƃ߂�A���S���Y�����܂Ƃ߂�
	//�g�̊�ƂȂ钸�_������
	for (int i = 0; i < clone_piece.back().point.size(); i++) {
		evaluation(i, clone_piece);
		select_piece(i,clone_piece);
	}
	flag--;
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
				if (i == 0 && k == 0) {
					if (equal_line(clone_piece.back().line[i], clone_piece[n].line[k])) {
						one_evalution[k] += 1;
					}
					if (equal_line(clone_piece.back().line.back(), clone_piece[n].line.back())) {
						one_evalution[k] += 1;
					}
				}
				else if (i == 0 && k != 0) {
					if (equal_line(clone_piece.back().line[i], clone_piece[n].line[k])) {
						one_evalution[k] += 1;
					}
					if(equal_line(clone_piece.back().line.back(), clone_piece[n].line[k - 1])){
						one_evalution[k] += 1;
					}
				}
				else if (i != 0 && k != 0) {
					if (equal_line(clone_piece.back().line[i], clone_piece[n].line[k])) {
						one_evalution[k] += 1;
					}
					if (equal_line(clone_piece.back().line[i -1], clone_piece[n].line[k - 1])) {
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
}

void Algorithm::union_piece() {
	//��̃s�[�X�̊p�x�E�ӂ��󂯎��
	//�s�[�X���m�̕]���_���쐬
	//�]���_�����Ƀs�[�X������
}

bool Algorithm::update_frame(int n ,int i, vector<Piece> &clone_piece) {
	vector<Piece> give_piece = clone_piece;
	vector<pair<int, int> > new_frame = clone_piece.back().point;
	int piece_symbol = 0;
	int frame = 0;
	int frame_symbol = 0;
	int se_count = 0;
	//�s�[�X�̔ԍ����󂯎��
	//��],���],�����蔻��ɂ���ē��Ă͂܂邩����
	//�s�[�X�̒��_����g�̒��_���ɑ}��
	
	//ans_point�ւ̑��
	clone_piece[n].ans_point = clone_piece[n].point;
	//������߂�
	for (int k = 0; k < clone_piece[n].angle.size(); k++) {
		if (clone_piece.back().point[i].first == clone_piece[n].point[k].first && clone_piece.back().point[i].second == clone_piece[n].point[k].second) {
			piece_symbol = k;
		}
	}
	//�E���ɒ��_��������&���̊p�x���������ꍇ���O
	for (int t = 0; t < (clone_piece[n].point.size() / 2); t++) {
		if (piece_symbol + t > clone_piece[n].point.size() / 2) {
			break;
		}
		if (i + t > clone_piece.back().point.size() / 2) {
			break;
		}
		if (clone_piece.back().point[i + t].first == clone_piece[n].point[piece_symbol + t].first && clone_piece.back().point[i + t].second == clone_piece[n].point[piece_symbol + t].second) {
			if (clone_piece.back().angle[i + t] == clone_piece[n].angle[piece_symbol + t]) {
				//���_���폜
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
				give_piece.back().point.erase(give_piece.back().point.begin() + i + t);
			}
			else {
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
			}
		}
		else {
			break;
		}
	}
	//�����ɒ��_��������&���̊p�x���������ꍇ���O
	for (int t = 0; t < (clone_piece.back().point.size() / 2); t++) {
		if (piece_symbol - t < 0) {
			break;
		}
		if (i - t < 0) {
			break;
		}
		if (clone_piece.back().point[i - t].first == clone_piece[n].point[piece_symbol - t].first && clone_piece.back().point[i - t].second == clone_piece[n].point[piece_symbol - t].second) {
			if (clone_piece.back().angle[t] == clone_piece[n].angle[piece_symbol + t]) {
				//���_���폜
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
				give_piece.back().point.erase(give_piece[n].point.begin() + i - t);
				frame_symbol -= 1;
			}
			else {
				give_piece[n].point.erase(give_piece[n].point.begin() + piece_symbol + t);
			}
		}
		else {
			break;
		}
	}
	//�ŏ��ɓ�������}��
	for (int t = 0; t < clone_piece[n].point.size() / 2; t++) {
		Circle circle(give_piece[n].point[t].first, give_piece[n].point[t].second, 1);
		for (int k = 0; k < clone_piece.back().point.size() / 2; k++) {
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

	//�s�[�X�̎c��̒��_�𔽑Ό����ɑ}�����Ă���
	for (int k = clone_piece[n].angle.size(); k > 0; k--) {
		if (se_count == 2) {
			give_piece.back().point.insert(give_piece.back().point.begin() + i + frame_symbol - 1, give_piece[n].point[k]);
		}
		else {
			give_piece.back().point.insert(give_piece.back().point.begin() + i + frame_symbol, give_piece[n].point[k]);
		}
	}
	//�X�V�������̋��L
	new_frame = give_piece.back().point;
	give_piece = clone_piece;
	give_piece.back().point = new_frame;
	give_piece.erase(give_piece.begin() + n);
	//�X�N�V���̕ۑ�
	if (give_piece.back().point.size() == 0) {

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
		for (int k = 0; k < clone_piece[n].angle.size(); k++) {

			//if (three_evalution[flag][n][k] == 3) {
				//�s�[�X�̔ԍ�,�g�̒��_������
				update_frame(n,i,clone_piece);
			//}
		}
	}
}

bool Algorithm::check_collision(int n,vector<Piece> &clone_piece) {
	double f_slope =  0, p_slope = 0;
	int f_intercept = 0, p_intercept = 0;
	int count_x = 0, count_y = 0;
	/*
	�g�E�s�[�X�̒��_���󂯎��
	�s�[�X��z�u�������ɘg�̒��Ɏ��܂��Ă��邩����
	n-�s�[�X�̔ԍ�,k-�s�[�X�̊e���_,i-�g�̊e���_
	*/
	for (int k = 0; k < clone_piece[n].point.size(); k++) {
		for (int i = 0; i < clone_piece.back().point.size(); i++) {

			//�g�̓�̒��_�̒����̈ꎟ�֐������߂�
			//���[�v�̍Ō�ɂȂ����̂Ȃ�v�f�̍Ō�ƍŏ����g�p����
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
			//�s�[�X�̓�̒��_�̈ꎟ�֐������߂�
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

			//�s�[�X�̒��_����L�΂������s��,�����Ƙg�̊e�ӂƂ���������񐔂��J�E���g
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
			//�g�̊O�Ƀs�[�X���o�Ă���Ȃ�True��Ԃ�
			if (count_y % 2 == 0 && count_x % 2 == 0) {
				return true;
			}
		}
		count_y = 0;
		count_x = 0;
		//�g�̓����Ƀs�[�X�����݂���Ȃ�false��Ԃ�
		return false;
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
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		if (mini_point_x > clone_piece[n].point[i].first) {
			mini_point_x = clone_piece[n].point[i].first;
			axis = i;
		}
	}

	//���]
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first = clone_piece[n].point[axis].first -
			(clone_piece[n].point[i].first - clone_piece[n].point[axis].first);
	}

	//�}�C�i�X���W�̏C��
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		if (abs((clone_piece[n].point[i].first - clone_piece[n].point[axis].first)) > minus) {
			minus = abs((clone_piece[n].point[i].first - clone_piece[n].point[axis].first));
		}
	}
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first += minus;
	}
}

void Algorithm::spin90_piece(int n,vector<Piece> &clone_piece) {
	/*
	�s�[�X��90�x����]������
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first = piece[n].point[i].first * (-1);
	}
}

void Algorithm::spin180_piece(int n,vector<Piece> &clone_piece) {
	/*
	�s�[�X��180�x����]������
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first = piece[n].point[i].first * (-1);
		clone_piece[n].point[i].second = piece[n].point[i].second * (-1);
	}
}

void Algorithm::spin270_piece(int n,vector<Piece> &clone_piece) {
	/*
	�s�[�X��270�x����]������
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].second = piece[n].point[i].second * (-1);
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