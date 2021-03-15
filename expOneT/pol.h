#pragma once
#include <vector>
#include "shape.h"

class pol :public shape
{
	// universal id for every image
	int id = 3;

	// data
	vector<int> x;
	vector<int> y;

	int pn();

	void painter();

	int select(int, int);

	void move(int, int);

	void read();

	void save();
};

