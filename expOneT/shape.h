#pragma once
#include <vector>
#include <string>
using namespace std;

class shape
{
public:
	// io buffer
	vector<int> buf;

	// how much points is needed to describe an image
	virtual int pn() = 0;

	// painter
	virtual void painter() = 0;

	// select the clicked image
	virtual int select(int, int) = 0;

	// move the selected image
	virtual void move(int, int) = 0;

	// read data from buffer
	virtual void read() = 0;

	// save
	virtual void save() = 0;

	// wehen to end drawing
	virtual int end(int, int) = 0;
};
