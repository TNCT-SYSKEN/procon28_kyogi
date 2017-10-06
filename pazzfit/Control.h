#pragma once
#include "Piece.h"
#include "Algorithm.h"
class Control {
public:
	//コンストラクタ
	Control();

	//実行するときに使う
	void exe();
	//配置情報を使ってピースの値をpieceに格納する(セッターじゃないよー)
	void set_piece();
	//この部分にアルゴリズムを書き込んでく
	void exec_argolithm();

	void set_shape_data();

	void make_point();
	void make_line();
	void make_angle();

	void output_piece(vector<Piece> &piece);
	void use_position();

	void make_point_position();

private:
	//ピースの情報
	vector<Piece> piece;
};