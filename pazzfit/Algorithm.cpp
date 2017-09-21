#include "Algorithm.h"

Algorithm::Algorithm() {
	clone_piece = cont.piece;
	flag = -1;
	collision_no = 0;
}

void Algorithm::init() {
	//clear.evalution;
}

void Algorithm::fit_piece() {
	flag++;
	//�s�[�X�Ƃ߂�A���S���Y�����܂Ƃ߂�
	//�g�̊�ƂȂ钸�_������
	for (int i = 0; i < clone_piece.back().point.size(); i++) {
		evaluation(i);
		select_piece(i);
		/*�g��vector��0�Ȃ�ΐ�*/
		if (1) {
			//�X�N���[���V���b�g��ۑ�
			break;
		}
		if (flag == 1) {
			init();
		}
	}
}

void Algorithm::evaluation(int i) {
	//�g�E�s�[�X�̒��_�E�p�x�E�ӂ̒������󂯎��
	//�s�[�X�Ƙg�̕]���_���쐬
	//�s�[�X�������
	for (int n = 0; n < (clone_piece.size()); n++) {
		//�s�[�X�̊p(���_)�������
		for (int k = 0; k < clone_piece[n].angle.size(); k++) {
			//�g�ƃs�[�X�̊p�x���r
			one_evalution.push_back(0);
			if (equal_angle(clone_piece.back().angle[i], clone_piece[n].angle[k])) {
				one_evalution[k] = 1;
				//���̗��[�̕ӂ���r
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
	//��̃s�[�X�̊p�x�E�ӂ��󂯎��
	//�s�[�X���m�̕]���_���쐬
	//�]���_�����Ƀs�[�X������
}

bool Algorithm::update_frame(int n,int i) {
		//�s�[�X�̔ԍ����󂯎��
		collision_checker(n,i);
		//�s�[�X�̒��_����g�̒��_���ɑ}��

		//�g�̌`����̍X�V
		//�Ƃ߂��s�[�X�̍폜�̑O��return_piece��push_back
		//�g�Ɋւ��Ă�return_frame��push_back
		//�Ƃ߂��s�[�X�̍폜
		//�s�[�X���Ƃ܂����ꍇ�Afit_piece()���Ăяo���ċA
		//�s�[�X���S�Ė��܂����̂Ȃ�X�N�V����ۑ�����
}

void Algorithm::select_piece(int i) {
	//�]���_�������s�[�X������Ȃ�update_piece()��
	/*�]���_�������s�[�X������Ȃ琳*/
	//�s�[�X�̔ԍ�������
	for (int n = 0; n < (clone_piece.size()); n++) {
		//�s�[�X�̊p(���_)����
		for (int k = 0; k < clone_piece[n].angle.size(); k++) {
			if (three_evalution[flag][n][k] == 3) {
				//�s�[�X�̔ԍ�������
				update_frame(n,i);
				fit_piece();
			}
		}
	}
}

bool Algorithm::check_collision(int n) {
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

void Algorithm::turn_piece(int n) {
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

void Algorithm::spin90_piece(int n) {
	/*
	�s�[�X��90�x����]������
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first = cont.piece[n].point[i].first * (-1);
	}
}

void Algorithm::spin180_piece(int n) {
	/*
	�s�[�X��180�x����]������
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].first = cont.piece[n].point[i].first * (-1);
		clone_piece[n].point[i].second = cont.piece[n].point[i].second * (-1);
	}
}

void Algorithm::spin270_piece(int n) {
	/*
	�s�[�X��270�x����]������
	*/
	for (int i = 0; i < int(clone_piece[n].point.size()); i++) {
		clone_piece[n].point[i].second = cont.piece[n].point[i].second * (-1);
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
		return true;
	}
}

bool Algorithm::equal_line(double first_line, double second_line) {
	/*
	�g�ƃs�[�X�̕ӏ����󂯎��
	�����덷�͈͓̔��œ������Ȃ��True
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

bool Algorithm::collision_checker(int n,int i) {
		//��],���],�����蔻��ɂ���ē��Ă͂܂邩����
		bool collision = true;
		Piece set = cont.piece[n];
		int set_x;
		int set_y;

		set_x = set.point[i].first;
		set_y = set.point[i].second;

		for (int j=0; j < set.point.size(); j++) {
				clone_piece[n].point[j].first -= set_x;
				clone_piece[n].point[j].second -= set_y;
		}

		if (collision == true && collision_no == 0) {
				collision = check_collision(n);
				collision_no++;
		}
		if (collision == true && collision_no == 1) {
				spin90_piece(n);
				collision = check_collision(n);
				collision_no++;
		}
		if (collision == true && collision_no == 2) {
				clone_piece[n] = set;
				spin180_piece(n);
				collision = check_collision(n);
				collision_no++;
		}
		if (collision == true && collision_no == 3) {
				clone_piece[n] = set;
				spin270_piece(n);
				collision = check_collision(n);
				collision_no++;
		}
		if (collision == true && collision_no == 4) {
				clone_piece[n] = set;
				turn_piece(n);
				collision = check_collision(n);
				collision_no++;
		}
		if (collision == true && collision_no == 5) {
				clone_piece[n] = set;
				turn_piece(n);
				spin90_piece(n);
				collision = check_collision(n);
				collision_no++;
		}
		if (collision == true && collision_no == 6) {
				clone_piece[n] = set;
				turn_piece(n);
				spin180_piece(n);
				collision = check_collision(n);
				collision_no++;
		}
		if (collision == true && collision_no == 7) {
				clone_piece[n] = set;
				turn_piece(n);
				spin270_piece(n);
				collision = check_collision(n);
				collision_no = 0;
		}
		if (collision == true) {
				clone_piece[n] = set;
				return false;
		}
		if (collision == false) {
				return true;
		}

}