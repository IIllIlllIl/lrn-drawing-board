#include "rec.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <GL/glut.h>
using namespace std;

int rec::pn() { return 2; }

int rec::select(int x, int y) {
	// -1 means the mouse clicked the blank
	int seq = -1;

	int x_min, x_max, y_min, y_max;

	if (x1 >= x2) {
		x_min = x2;
		x_max = x1;
	}
	else {
		x_min = x1;
		x_max = x2;
	}
	if (y1 >= y2) {
		y_min = y2;
		y_max = y1;
	}
	else {
		y_min = y1;
		y_max = y2;
	}

	// cmp: 0: success
	if (x > x_min&& x<x_max && y>y_min&& y < y_max) { seq = 0; }

	return seq;

}

void rec::move(int dx,int dy) {
	x1 += dx;
	x2 += dx;
	y1 += dy;
	y2 += dy;
}

void rec::painter() {
	glColor3f(0.7, 0.8, 0.6);
	glRecti(x1, y1, x2, y2);
}

void rec::read() {
	// read err
	if (buf.size() < 4) {
		cout << "read error" << endl;
		return;
	}

	x1 = buf[0];
	y1 = buf[1];
	x2 = buf[2];
	y2 = buf[3];
}

void rec::read(int& start, int*iobuf) {
	// input data
	buf.clear();
	for (int i = 0; i < (2 * pn()); i++) {
		buf.push_back(iobuf[start++]);
	}
	
	// read err
	if (buf.size() < 4) {
		cout << "read error" << endl;
		return;
	}

	x1 = buf[0];
	y1 = buf[1];
	x2 = buf[2];
	y2 = buf[3];
}

void rec::save() {
	buf.push_back(id);
	buf.push_back(x1);
	buf.push_back(y1);
	buf.push_back(x2);
	buf.push_back(y2);
}

int rec::end(int x, int y) { return 1; }