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
	if (vec[i][0] != 0) { return -2; }

	// areas
	int s, s12, s34, s56;
	s = vec[i][1] * vec[i][4] - vec[i][1] * vec[i][6]
		+ vec[i][3] * vec[i][6] - vec[i][3] * vec[i][2]
		+ vec[i][5] * vec[i][2] - vec[i][5] * vec[i][4];

	s12 = x * vec[i][4] - x * vec[i][6]
		+ vec[i][3] * vec[i][6] - vec[i][3] * y
		+ vec[i][5] * y - vec[i][5] * vec[i][4];

	s34 = vec[i][1] * y - vec[i][1] * vec[i][6]
		+ x * vec[i][6] - x * vec[i][2]
		+ vec[i][5] * vec[i][2] - vec[i][5] * y;

	s56 = vec[i][1] * vec[i][4] - vec[i][1] * y
		+ vec[i][3] * y - vec[i][3] * vec[i][2]
		+ x * vec[i][2] - x * vec[i][4];

	if (abs(s) == (abs(s12) + abs(s34) + abs(s56))) { return 0; }
	else { return -1; }
}
int record::rec(int i, int x, int y) {
	// real rect?
	if (vec[i][0] == 0) { return -2; }

	// the edges(x1 <= x2, y1 <= y2)
	int x1, x2, y1, y2;
	if (vec[i][1] >= vec[i][3]) {
		x1 = vec[i][3];
		x2 = vec[i][1];
	}
	else {
		x1 = vec[i][1];
		x2 = vec[i][3];
	}
	if (vec[i][2] >= vec[i][4]) {
		y1 = vec[i][4];
		y2 = vec[i][2];
	}
	else {
		y1 = vec[i][2];
		y2 = vec[i][4];
	}

	// cmp: 0: success
	if (x > x1&& x<x2 && y>y1&& y < y2) { return 0; }
	else { return -1; }
}
int record::line(int i, int x, int y) {
	// real line?
	if (vec[i][0] != 2) { return -2; }

	// use rectangle
	if (rec(i, x, y) == -1) { return -1; }

	// the func of the line
	int a, b, c;
	a = vec[i][4] - vec[i][2];
	b = vec[i][1] - vec[i][3];
	c = vec[i][3] * vec[i][2] - vec[i][1] * vec[i][4];

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
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}
void record::show(int i) {
	cout <<  vec[i][1] << " ";
	cout <<  vec[i][2] << " ";
	cout <<  vec[i][3] << " ";
	cout <<  vec[i][4] << " ";
	cout <<  vec[i][5] << " ";
	cout <<  vec[i][6] << endl;
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
			vec.push_back(buffer);

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
			outfile << vec[i][j] << " ";
		}
	}

	outfile.close();
}

// select
int record::select(int x, int y) {
	// -1 means the mouse clicked the blank
	int seq = -1;
	// if the point located in an image, pass = 1
	int pass = 0;

	for (int i = 0; i < vec.size(); i++) {
		// read type
		switch (vec[i][0]) {
			// triangle
			case(0):
				if (tri(i, x, y) == 0) { seq = i; }
				break;

			// rectangle
			case(1):
				if (rec(i, x, y) == 0) { seq = i; }
				break;

			// line
			case(2):
				if (line(i, x, y) == 0) { seq = i; }
				break;
		}

		if (seq != -1) { break; }
	}

	return seq;
}

// move
int record::shift(int i, int dx, int dy) {
	if (i >= vec.size()) { return -2; }

	for (int j = 0; j < 3; j++) {
		vec[i][2 * j + 1] += dx;
		vec[i][2 * j + 2] += dy;
	}

	return 0;
}

//paint
void record::painter() {
	for (int i = 0; i < vec.size(); i++) {
		// show records
		glColor3f(0.7, 0.8, 0.6);

		// triangle
		if (vec[i][0] == 0) {
			glBegin(GL_TRIANGLES);
			glVertex2d(vec[i][1], vec[i][2]);
			glVertex2d(vec[i][3], vec[i][4]);
			glVertex2d(vec[i][5], vec[i][6]);
			glEnd();
		}
		// rectangle
		if (vec[i][0] == 1) {
			glRecti(vec[i][1], vec[i][2], vec[i][3], vec[i][4]);
		}
		// line
		if (vec[i][0] == 2) {
			glBegin(GL_LINES);
			glVertex2d(vec[i][1], vec[i][2]);
			glVertex2d(vec[i][3], vec[i][4]);
			glEnd();
		}
	}
}
