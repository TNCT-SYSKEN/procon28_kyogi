#pragma once
#include "Piece.h"
class Control {
public:
	//�R���X�g���N�^
	Control();

	//���s����Ƃ��Ɏg��
	void exe();
	//�z�u�����g���ăs�[�X�̒l��piece�Ɋi�[����(�Z�b�^�[����Ȃ���[)
	void set_piece();
	//���̕����ɃA���S���Y������������ł�
	void exec_argolithm();

	void set_shape_data();

	void make_point();
	void make_line();

	//�s�[�X�̏��
	vector<Piece> piece;
};
