// this class serve as a data stuct (mainly a vector)
// which describes iamges painted by gui
//
// iillilllil
// wang.tr@outlook.com
//

#pragma once
#include <vector>
#include <algorithm>
using namespace std;

class record
{
public:
	// io vec[7]: type(1)+points(3*2=6)
	vector<int*> vec;

	// how much points is needed to describe an image
	// triangle rectangle line
	int pn[3] = { 3, 2, 2 };

	// length of ptr in vec 
	// 1(id) + 2(x,y) * 3(the maxium of points)
	const int len = 7;

	// painter
	void painter();


	// read or write files
	void load();
	void save();

	// select the clicked image
	int select(int, int);

	// move
	int shift(int, int, int);

private:
	// display data
	void display();
	void show(int);

	int tri(int, int, int);
	int rec(int, int, int);
	int line(int, int, int);
};

