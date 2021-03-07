#pragma once
#include "record.h"

class tri
{
public:
	//universal id for every image
	int id = 0;

	int pn = 3;
	// io vec[7]: type(1)+points(3*2=6)
	vector<int*> vec;

	void load();

	void painter();

	int select(int, int);
};

