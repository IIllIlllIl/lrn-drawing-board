#pragma once
class shape
{
public:

	//data
	int* vec = new int[7];

	// how much points is needed to describe an image
	virtual int pn() = 0;

	// painter
	virtual void painter() = 0;

	// select the clicked image
	virtual int select(int, int) = 0;

	// save
	virtual void save() = 0;
};

