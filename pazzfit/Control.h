#pragma once
#include "Piece.h"
#include "common.h"
class Control {
public:
	//コンストラクタ
	Control();

	//実行するときに使う
	void exe();
	//配置情報を使ってピースの値をpieceに格納する(セッターじゃないよー)
	void set_piece();
	//この部分にアルゴリズムを書き込んでく
	void output_piece();
	void use_position();

	void make_point_position();

	//ピースの情報
	vector<Piece> piece;
};
