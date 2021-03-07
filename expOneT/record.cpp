// iillilllil
// wang.tr@outlook.com
//

#include "record.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <GL/glut.h>
using namespace std;

// used by func line
int dist = 5;

// to check if it is in the area of image
int record::tri(int i, int x, int y) {
	// real tri?
	if (vec[i].vec[0] != 0) { return -2; }

	// areas
	int s, s12, s34, s56;
	s = vec[i].vec[1] * vec[i].vec[4] - vec[i].vec[1] * vec[i].vec[6]
		+ vec[i].vec[3] * vec[i].vec[6] - vec[i].vec[3] * vec[i].vec[2]
		+ vec[i].vec[5] * vec[i].vec[2] - vec[i].vec[5] * vec[i].vec[4];

	s12 = x * vec[i].vec[4] - x * vec[i].vec[6]
		+ vec[i].vec[3] * vec[i].vec[6] - vec[i].vec[3] * y
		+ vec[i].vec[5] * y - vec[i].vec[5] * vec[i].vec[4];

	s34 = vec[i].vec[1] * y - vec[i].vec[1] * vec[i].vec[6]
		+ x * vec[i].vec[6] - x * vec[i].vec[2]
		+ vec[i].vec[5] * vec[i].vec[2] - vec[i].vec[5] * y;

	s56 = vec[i].vec[1] * vec[i].vec[4] - vec[i].vec[1] * y
		+ vec[i].vec[3] * y - vec[i].vec[3] * vec[i].vec[2]
		+ x * vec[i].vec[2] - x * vec[i].vec[4];

	if (abs(s) == (abs(s12) + abs(s34) + abs(s56))) { return 0; }
	else { return -1; }
}
int record::rec(int i, int x, int y) {
	// real rect?
	if (vec[i].vec[0] == 0) { return -2; }

	// the edges(x1 <= x2, y1 <= y2)
	int x1, x2, y1, y2;
	if (vec[i].vec[1] >= vec[i].vec[3]) {
		x1 = vec[i].vec[3];
		x2 = vec[i].vec[1];
	}
	else {
		x1 = vec[i].vec[1];
		x2 = vec[i].vec[3];
	}
	if (vec[i].vec[2] >= vec[i].vec[4]) {
		y1 = vec[i].vec[4];
		y2 = vec[i].vec[2];
	}
	else {
		y1 = vec[i].vec[2];
		y2 = vec[i].vec[4];
	}

	// cmp: 0: success
	if (x > x1&& x<x2 && y>y1&& y < y2) { return 0; }
	else { return -1; }
}
int record::line(int i, int x, int y) {
	// real line?
	if (vec[i].vec[0] != 2) { return -2; }

	// use rectangle
	if (rec(i, x, y) == -1) { return -1; }

	// the func of the line
	int a, b, c;
	a = vec[i].vec[4] - vec[i].vec[2];
	b = vec[i].vec[1] - vec[i].vec[3];
	c = vec[i].vec[3] * vec[i].vec[2] - vec[i].vec[1] * vec[i].vec[4];

	// distance
	double d, d1, d2;
	d1 = fabs(a * x + b * y + c);
	d2 = sqrt((pow(a, 2) + pow(b, 2)));
	d = d1 / d2;

	if (d <= dist) { return 0; }
	else { return -1; }
}

// dispaly
void record::display() {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < len; j++) {
			cout << vec[i].vec[j] << " ";
		}
		cout << endl;
	}
}
void record::show(int i) {
	cout <<  vec[i].vec[1] << " ";
	cout <<  vec[i].vec[2] << " ";
	cout <<  vec[i].vec[3] << " ";
	cout <<  vec[i].vec[4] << " ";
	cout <<  vec[i].vec[5] << " ";
	cout <<  vec[i].vec[6] << endl;
}

// read data
void record::load() {
	// read the path
	string path;
	cout << ">load:\t";
	cin >> path;
	cin.clear();
	cin.ignore(1024, '\n');

	// open ioiodata file
	ifstream infile;
	infile.open(path, ios::in);

	// if it is not existed, create it
	if (!infile) {
		ofstream create;
		create.open(path, ios::out);
		printf("not found\n");
		create.close();
	}

	// if exist
	else {
		int* buffer = new int[len];

		//read
		while (infile >> buffer[0]) {
			// read other 6 value
			for (int j = 1; j < len; j++) {
				infile >> buffer[j];
			}

			// add to vec
			shape newshape;
			newshape.vec = buffer;
			vec.push_back(newshape);

			// renew the buffer
			buffer = new int[len];
		}
	}

	infile.close();
}

// save
void record::save() {
	// path
	string path;
	cout << ">save:\t";
	cin >> path;
	cin.clear();
	cin.ignore(1024, '\n');

	ofstream outfile;
	outfile.open(path, ios::out);

	// write
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < len; j++) {
			outfile << vec[i].vec[j] << " ";
		}
	}

	outfile.close();
}

// select
int record::select(int x, int y) {
	// -1 means the mouse clicked the blank
	int seq = -1;
	
	// to mark the iamge slected
	int i = 0;

	for (i = 0; i < vec.size(); i++) {
		// read type
		seq = vec[i].select(x, y);

		if (seq != -1) { break; }
	}

	return i;
}

// move
int record::shift(int i, int dx, int dy) {
	if (i >= vec.size()) { return -2; }

	for (int j = 0; j < 3; j++) {
		vec[i].vec[2 * j + 1] += dx;
		vec[i].vec[2 * j + 2] += dy;
	}

	return 0;
}

//paint
void record::painter() {
	for (int i = 0; i < vec.size(); i++) {
		vec[i].painter();
	}
}

//menu
void record::userEventAction(int key) {
	switch (key)
	{
	// create new record
	memset(newvec->vec, 0, sizeof(newvec->vec));

	// reset
	case '0':
		vec.clear();
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// reset vars
		memset(last, 0, sizeof(last));
		pnum = -1;
		en_select = -1;
		en_move = -1;
		break;

		// triangle
	case '1':
		newvec->vec[0] = 0;

		// set global values 
		pnum = newvec->pn[0];

		// stop moving
		en_select = -1;
		break;

		// rectangle
	case '2':
		newvec->vec[0] = 1;

		// set global values 
		pnum = newvec->pn[1];

		// stop moving
		en_select = -1;
		break;

		// line
	case '3':
		newvec->vec[0] = 2;

		// set global values 
		pnum = newvec->pn[2];

		// stop moving
		en_select = -1;
		break;

		// move
	case '4':
		memset(last, 0, sizeof(last));
		en_select = 0;
		pnum = -1;
		break;

		// save
	case '5':
		save();
		break;

		// load
	case '6':
		vec.clear();
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// reset vars
		memset(last, 0, sizeof(last));
		pnum = -1;
		en_select = -1;
		en_move = -1;

		// load
		 load();
		break;

		// quit
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
	return;
}
