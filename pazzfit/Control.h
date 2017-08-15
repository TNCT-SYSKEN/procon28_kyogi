#pragma once
#include "Piece.h"
#include "common.h"
class Control {
public:
	//�R���X�g���N�^
	Control();

	//���s����Ƃ��Ɏg��
	void exe();
	//�z�u�����g���ăs�[�X�̒l��piece�Ɋi�[����(�Z�b�^�[����Ȃ���[)
	void set_piece();
	//���̕����ɃA���S���Y������������ł�
	void fit_piece();
	void spin_piece();
	void turn_piece();
	void check_collision();
	void evaluation();
	void union_piece();
	void update_frame();
	//�s�[�X�̏��
	vector<Piece> piece;
};
