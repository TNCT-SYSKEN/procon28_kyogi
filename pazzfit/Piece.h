<<<<<<< HEAD
=======

>>>>>>> ef7d7becb0de95cb163e73442f987b667314c6a3
#pragma once
#include "common.h"

class Piece {
public:
	int no_piece;
	vector<double> line;
	vector<double> angle;
	vector<pair<int,int> > point;
	vector<pair<int,int> > ans_point;
};
