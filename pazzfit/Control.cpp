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
	//�s�[�X�Ƃ߂�A���S���Y�����܂Ƃ߂�
}

void Control::spin_piece() {
	//�s�[�X��90�x��]������
}

void Control::turn_piece() {
	//�s�[�X�̒��_�����󂯎��
	//�s�[�X�𔽓]�����A���_�����X�V
}

void Control::check_collision() {
	//�g�E�s�[�X�̒��_���󂯎��
	//�s�[�X��z�u�������ɘg�̒��Ɏ��܂��Ă��邩����
}

void Control::evaluation() {
	//�g�E�s�[�X�̒��_�E�p�x�E�ӂ̒������󂯎��
	//�s�[�X�Ƙg�̕]���_���쐬

	if (fabs(-1.0) == 1) {
		Rect(10, 10, 20, 20).draw(Palette::White);
	}
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