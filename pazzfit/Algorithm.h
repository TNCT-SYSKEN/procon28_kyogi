#pragma once
#include "Control.h"

class Algorithm {
public :
	Algorithm();

	void init();
	void fit_piece(vector<Piece>);
	void evaluation(int,vector<Piece> &clone_piece);
	void union_piece();
	bool update_frame(int,int,int,vector<Piece> &clone_piece);
	void select_piece(int,vector<Piece> &clone_piece,int);
	bool check_collision(int, vector<Piece> &clone_piece);
	void sort_frame(vector<Piece> &give_frame);
	void algo_make_line(vector<Piece> &give_frame);
	void algo_make_angle(vector<Piece> &give_frame);
	bool check_overlapping(vector<Piece> &give_frame);

	void turn_piece(int, vector<Piece> &clone_piece);
	void spin90_piece(int, vector<Piece> &clone_piece);
	void spin180_piece(int, vector<Piece> &clone_piece);
	void spin270_piece(int, vector<Piece> &clone_piece);
	bool equal_angle(double, double);
	bool equal_line(double, double);
	bool equal_point(int, int);
	bool collision_checker(int,int,int,vector<Piece> &clone_piece);

	bool closs_line(double,double,double,double,double,double,double,double);
	bool check_origin_frame(vector<Piece> &give_piece,vector<pair<int,int> >&line_piece);
private:
	int system_end;
	int flag;
	vector<Piece> piece;
	vector<Piece> ans_piece;
	int collision_no;
	vector<vector<vector<int>>> three_evalution;
	vector<vector<int>> two_evalution;
	vector<int> one_evalution;
};