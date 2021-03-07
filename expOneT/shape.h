#pragma once
class shape
{
public:

	//data
	int* vec = new int[7];

	// how much points is needed to describe an image
	int pn[3] = { 3,2,2 };

	// painter
	void painter();

	// select the clicked image
	int select(int, int);
};

