#pragma once
#include "shape.h"

class rec:public shape
{
public:
	//universal id for every image
	int id = 1;

	int pn();

	void painter();

	int select(int, int);

	void save();
};

