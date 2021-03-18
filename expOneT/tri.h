#pragma once
#include <string>
#include "shape.h"

class tri:public shape
{
public:
	// universal id for every image
	int id = 0;

	// data
	int x1, y1;
	int x2, y2;
	int x3, y3;

	int pn();

	void painter();

	int select(int, int);

	void move(int, int);

	void read();

	void save();

	int end(int, int);
};

