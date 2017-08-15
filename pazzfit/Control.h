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
	void fit_piece();
	void spin_piece();
	void turn_piece();
	void check_collision();
	void evaluation();
	void union_piece();
	void update_frame();
	//ピースの情報
	vector<Piece> piece;
};
