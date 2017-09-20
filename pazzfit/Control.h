#pragma once
#include "Piece.h"
class Control {
public:
	//コンストラクタ
	Control();

	//実行するときに使う
	void exe();
	//この部分にアルゴリズムを書き込んでく
	void exec_argolithm();

	void set_shape_data();

	void make_point();
	void make_line();
	void make_angle();

	void output_piece();
	void use_position();

	void make_point_position();


	//ピースの情報
	vector<Piece> piece;
};

