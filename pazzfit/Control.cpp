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