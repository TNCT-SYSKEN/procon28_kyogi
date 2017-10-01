#pragma once
#include "common.h"

class Piece {
public:
	int no_piece;
	vector<double> line;
	vector<double> angle;
	vector<pair<int,int> > point;
	vector<pair<int,int> > ans_point;
	bool union_flag;
};
