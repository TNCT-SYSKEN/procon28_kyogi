#pragma once
#include "Control.h"

class Algorithm {
public :
	Control cont;

	void fit_piece();
	void spin90_piece(int);
	void spin180_piece(int);
	void spin270_piece(int);
	void turn_piece(int);
	bool check_collision(int);
	void evaluation();
	void union_piece();
	void update_frame();
	bool equal_angle(double, double);
	bool equal_line(double, double);
	bool equal_point(int, int);
};