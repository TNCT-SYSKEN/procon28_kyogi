#include "Algorithm.h"

void Algorithm::fit_piece() {

}

void Algorithm::spin90_piece(int n) {
	/*
	�s�[�X��90�x����]������
	*/
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].first = cont.piece[n].point[i].first * (-1);
	}
}

void Algorithm::spin180_piece(int n) {
	/*
	�s�[�X��180�x����]������
	*/
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].first = cont.piece[n].point[i].first * (-1);
		cont.clone_piece[n].point[i].second = cont.piece[n].point[i].second * (-1);
	}
}

void Algorithm::spin270_piece(int n) {
	/*
	�s�[�X��270�x����]������
	*/
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].second = cont.piece[n].point[i].second * (-1);
	}
}

void Algorithm::turn_piece(int n) {
	/*
	�s�[�X�̔ԍ����󂯎��
	�s�[�X�𔽓]�����A���_�����X�V
	axis���X���W�̏������l�������Ă�v�f��
	*/
	int mini_point_x = 100, axis;
	int minus = 0;

	//��ƂȂ���W�̌���
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		if (mini_point_x > cont.clone_piece[n].point[i].first) {
			mini_point_x = cont.clone_piece[n].point[i].first;
			axis = i;
		}
	}

	//���]
	for (int i = 0; i < int(cont.clone_piece[n].point.size()); i++) {
		cont.clone_piece[n].point[i].first = cont.clone_piece[n].point[axis].first -
			(cont.clone_piece[n].point[i].first - cont.clone_piece[n].point[axis].first);
	}

	//�}�C�i�X���W�̏C��
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
	�g�E�s�[�X�̒��_���󂯎��
	�s�[�X��z�u�������ɘg�̒��Ɏ��܂��Ă��邩����
	n-�s�[�X�̔ԍ�,k-�s�[�X�̊e���_,i-�g�̊e���_
	*/
	for (int k = 0; k < int(cont.clone_piece[n].point.size()); k++) {
		for (int i = 0; i < int(cont.clone_piece.back().point.size()); i++) {

			//�g�̓�̒��_�̒����̈ꎟ�֐������߂�
			//���[�v�̍Ō�ɂȂ����̂Ȃ�v�f�̍Ō�ƍŏ����g�p����
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
			//�s�[�X�̓�̒��_�̈ꎟ�֐������߂�
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

			//�s�[�X�̒��_����L�΂������s��,�����Ƙg�̊e�ӂƂ���������񐔂��J�E���g
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

void Algorithm::evaluation() {
	//�g�E�s�[�X�̒��_�E�p�x�E�ӂ̒������󂯎��
	//�s�[�X�Ƙg�̕]���_���쐬

}

void Algorithm::union_piece() {
	//��̃s�[�X�̊p�x�E�ӂ��󂯎��
	//�s�[�X���m�̕]���_���쐬
	//�]���_�����Ƀs�[�X������
}

void Algorithm::update_frame() {
	//�g�E�s�[�X�̒��_���󂯎��
	//�]���_�����Ƀs�[�X�̌`�����g�̌`����ɑ}��
}

bool Algorithm::equal_angle(int first_angle, int second_angle) {
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
	return true;
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