#pragma once
#include "Piece.h"
#include "Algorithm.h"
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
	void make_angle();

	void output_piece(vector<Piece> &piece);
	void use_position();

	void make_point_position();

private:
	//�s�[�X�̏��
	vector<Piece> piece;
};