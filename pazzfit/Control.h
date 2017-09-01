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
	void turn_piece(int);
	bool check_collision(int);
	void evaluation();
	void union_piece();
	void update_frame();
	bool equal_angle(int,int);
	bool equal_line(int,int);
	bool equal_point(int,int);
	//�s�[�X�̏��
	vector<Piece> piece;
	vector<Piece> clone_piece;
};