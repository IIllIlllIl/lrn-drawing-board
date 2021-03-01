#pragma once
#include "record.h"


class tri:public record
{
public:
	int pn = 3;

	void painter();

	int select(int, int);
};

