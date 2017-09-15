#pragma once
#include "Control.h"

class Algorithm {
public :
	Control cont;
	Algorithm();

	void init();
	void fit_piece();
	void evaluation(int);
	void union_piece();
	bool update_frame(int);
	void select_piece();
	bool check_collision(int);

	void turn_piece(int);
	void spin90_piece(int);
	void spin180_piece(int);
	void spin270_piece(int);
	bool equal_angle(double, double);
	bool equal_line(double, double);
	bool equal_point(int, int);
private:
	int flag;
	vector<Piece> return_frame;
	vector<Piece> return_piece;
	vector<Piece> clone_piece;
	vector<vector<vector<int>>> three_evalution;
	vector<vector<int>> two_evalution;
	vector<int> one_evalution;
};