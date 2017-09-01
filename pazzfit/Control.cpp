#include "Control.h"

Control::Control() {
	//�����ŉ摜�����̎��s
}

void Control::exe() {
	set_piece();
}

void Control::set_piece() {
	int hoge = 10;
	//�e�L�X�g��ǂݍ��ݐ؂蕪���Ă��ꂼ��push_back����
	const Rect rect(hoge, hoge, 200, 100);
}

void Control::fit_piece() {

}

void Control::spin_piece() {
	//�s�[�X��90�x��]������
}

void Control::turn_piece(int n) {
	/*
	�s�[�X�̔ԍ����󂯎��
	�s�[�X�𔽓]�����A���_�����X�V
	axis���X���W�̏������l�������Ă�v�f��
	*/
	int mini_point_x = 100, axis;
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

bool Control::check_collision(int n) {
	double f_slope, p_slope;
	int f_intercept, p_intercept;
	int count_x = 0, count_y = 0;
	/*
	�g�E�s�[�X�̒��_���󂯎��
	�s�[�X��z�u�������ɘg�̒��Ɏ��܂��Ă��邩����
	n-�s�[�X�̔ԍ�,k-�s�[�X�̊e���_,i-�g�̊e���_
	*/
	for (int k = 0; k < int(clone_piece[n].point.size()); k++) {
		for (int i = 0; i < int(clone_piece.back().point.size()); i++) {

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

void Control::evaluation() {
	//�g�E�s�[�X�̒��_�E�p�x�E�ӂ̒������󂯎��
	//�s�[�X�Ƙg�̕]���_���쐬
	
}

void Control::union_piece() {
	//��̃s�[�X�̊p�x�E�ӂ��󂯎��
	//�s�[�X���m�̕]���_���쐬
	//�]���_�����Ƀs�[�X������
}

void Control::update_frame() {
	//�g�E�s�[�X�̒��_���󂯎��
	//�]���_�����Ƀs�[�X�̌`�����g�̌`����ɑ}��
}

bool Control::equal_angle(int i,int k) {
	return true;
}

bool Control::equal_line(int i, int k) {
	return true;
}

bool Control::equal_point(int frame_point, int piece_point) {
	return true;
}