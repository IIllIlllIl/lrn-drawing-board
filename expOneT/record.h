// iillilllil
// wang.tr@outlook.com
//

#pragma once
#include <vector>
#include <algorithm>
#include "shape.h"
#include "creator.h"
using namespace std;

class record
{
public:
	// io vec[7]: type(1)+points(3*2=6)
	vector<shape*> vec;
	shape* newvec;

	// to create images
	vector<creator*> creators;

	// menu
	vector<void (*)(record*)> menuAction;

	// length of ptr in vec 
	// 1(id) + 2(x,y) * 3(the maxium of points)
	const int len = 7;

	// global vars
	int index;
	int last[2] = { 0, 0 };

	// enable vars
	int pnum = -1;
	int en_select = -1;
	int en_move = -1;

	// menu
	typedef struct menuEntryStruct {
		const char* label;
		char key;
	} menuEntryStruct;

	void userEventAction(int);

	record();

	// painter
	void painter();

	// read or write files
	void load();
	void save();

	// select the clicked image
	int select(int, int);

	// move
	int shift(int, int, int);
};

