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

	int x1, x2, y1, y2;

	if (vec[1] >= vec[3]) {
		x1 = vec[3];
		x2 = vec[1];
	}
	else {
		x1 = vec[1];
		x2 = vec[3];
	}
	if (vec[2] >= vec[4]) {
		y1 = vec[4];
		y2 = vec[2];
	}
	else {
		y1 = vec[2];
		y2 = vec[4];
	}

	// cmp: 0: success
	if (x > x1&& x<x2 && y>y1&& y < y2) { seq = 0; }

	return seq;

}

void rec::painter() {
	glColor3f(0.7, 0.8, 0.6);

	// triangle
	if (vec[0] == id) {
		glRecti(vec[1], vec[2], vec[3], vec[4]);
	}
}

void rec::save() {

}