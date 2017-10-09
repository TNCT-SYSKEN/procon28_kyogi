#pragma once
#include "Piece.h"

class Frame{
public:
	int no_piece;
	vector<double> line;
	vector<double> angle;
	vector<pair<int, int> > point;
	vector<pair<int, int> > ans_point;
};
