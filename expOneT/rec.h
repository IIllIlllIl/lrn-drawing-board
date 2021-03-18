#pragma once
#include <string>
#include "shape.h"

class rec:public shape
{
public:
	//universal id for every image
	int id = 1;

	// data
	int x1, y1;
	int x2, y2;

	int pn();

	void painter();

	int select(int, int);

	void move(int, int);

	void read();

	void save();

	int end(int, int);
};

