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
	clone_piece = piece;

	//�s�[�X�Ƃ߂�A���S���Y�����܂Ƃ߂�
	//�g�̊�ƂȂ钸�_������
	for (int i = 0; i < clone_piece.back().point.size();i++) {
		//�s�[�X�������
		for (int n = 0; n < (clone_piece.size() - 1); ++n) {
			//�s�[�X�̊p�������
			for (int k = 0; k < clone_piece[n].angle.size(); ++k) {
				if (/*�g�ƃs�[�X�̊p�x���r*/) {
					//piece[n].evalution[k].push_back(1);
					if (/*���̗��[�̕ӂ���r*/) {
						//�]���_��ǉ�
					}
				}
				else {
					//�]���_��0��ǉ�
				}
			}
		}
		if (/*�]���_�������s�[�X������Ȃ琳*/) {
			//�]���_�������s�[�X��g�̏��ɒǉ�
			//�V���Șg�̊p�x�ƕӂ��Z�o���ď㏑���H
			//�Ƃ߂��s�[�X�̍폜
		}
		else {
			break;
		}
		if (/*�c��s�[�X��0�Ȃ�ΐ�*/) {
			//ans_point�֒ǉ�
			break;
		}
		//�ċA��sort();���Ăяo��(�X�V�����g�̏��������Ƃ��ēn��)     
	}
}

void Control::spin_piece() {
	//�s�[�X��90�x��]������
}

void Control::turn_piece() {
	//�s�[�X�̒��_�����󂯎��
	//�s�[�X�𔽓]�����A���_�����X�V

}

bool Control::check_collision(int n) {
	double f_slope, p_slope;
	int f_intercept, p_intercept;
	int count_x = 0, count_y = 0;
	//�g�E�s�[�X�̒��_���󂯎��
	//�s�[�X��z�u�������ɘg�̒��Ɏ��܂��Ă��邩����

	for (int k = 0; k < clone_piece[n].point.size; k++) {
		for (int i = 0; i < clone_piece.back().point.size(); i++) {

			//�g�̓�̒��_�̒����̈ꎟ�֐������߂�
			//���[�v�̍Ō�ɂȂ����̂Ȃ�v�f�̍Ō�ƍŏ����g�p����
			if ((clone_piece.back().point.size - 1) == i) {
				f_slope = (clone_piece.back().point[i].second - clone_piece.back().point[0].second) /
					(clone_piece.back().point[i].first - clone_piece.back().point[0].first);
				f_intercept = clone_piece.back().point[i].second - f_slope * clone_piece.back().point[i].first;
			}
			else {
				f_slope = (clone_piece.back().point[i].second - clone_piece.back().point[i + 1].second) /
					(clone_piece.back().point[i].first - clone_piece.back().point[i + 1].first);
				f_intercept = clone_piece.back().point[i].second - f_slope * clone_piece.back().point[i].first;
			}
			if ((clone_piece[n].point.size - 1) == k) {
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
				if ((clone_piece.back().point.size - 1) == i) {
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
				if ((clone_piece.back().point.size - 1) == i) {
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

}

bool Control::equal_line(int i, int k) {

}

bool Control::equal_point(int frame_point, int piece_point) {

}