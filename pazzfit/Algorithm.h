#pragma once
#include "Control.h"

class Algorithm {
public :
	Algorithm();

	void init();
	void fit_piece(vector<Piece>);
	void evaluation(int,vector<Piece> &clone_piece);
	void union_piece();
	bool update_frame(int,int,vector<Piece> &clone_piece);
	void select_piece(int,vector<Piece> &clone_piece);
	bool check_collision(int, vector<Piece> &clone_piece);
	void sort_frame(vector<Piece> &give_frame);
	void algo_make_line(vector<Piece> &give_frame);
	void algo_make_angle(vector<Piece> &give_frame);

	void turn_piece(int, vector<Piece> &clone_piece);
	void spin90_piece(int, vector<Piece> &clone_piece);
	void spin180_piece(int, vector<Piece> &clone_piece);
	void spin270_piece(int, vector<Piece> &clone_piece);
	bool equal_angle(double, double);
	bool equal_line(double, double);
	bool equal_point(int, int);
	bool collision_checker(int,int, vector<Piece> &clone_piece);
private:
	int flag;
	vector<Piece> piece;
	int collision_no;
	vector<vector<vector<int>>> three_evalution;
	vector<vector<int>> two_evalution;
	vector<int> one_evalution;
};