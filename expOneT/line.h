#pragma once
#include "shape.h"
class line:public shape
{
public:
	//universal id for every image
	int id = 2;

	int pn();

	void painter();

	int select(int, int);

	void save();
};

