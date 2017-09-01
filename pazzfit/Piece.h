
#pragma once
#include "common.h"

class Piece {
public:
	int no_piece;
	vector<double> line;
	vector<double> angle;
	vector<pair<int,int> > point;
	vector<vector<pair<int,int>>> evalution;
	vector<pair<int,int> > ans_point;
};
