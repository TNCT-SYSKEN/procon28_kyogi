#pragma once
#include "Piece.h"
class Control {
public:
	//�R���X�g���N�^
	Control();

	//���s����Ƃ��Ɏg��
	void exe();
	//���̕����ɃA���S���Y������������ł�
	void exec_argolithm();

	void set_shape_data();

	void make_point();
	void make_line();
	void make_angle();

	void output_piece();
	void use_position();

	void make_point_position();


	//�s�[�X�̏��
	vector<Piece> piece;
};

