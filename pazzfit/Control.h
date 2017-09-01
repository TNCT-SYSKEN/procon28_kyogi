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
	void turn_piece(int);
	bool check_collision(int);
	void evaluation();
	void union_piece();
	void update_frame();
	bool equal_angle(int,int);
	bool equal_line(int,int);
	bool equal_point(int,int);
	//ピースの情報
	vector<Piece> piece;
	vector<Piece> clone_piece;
};