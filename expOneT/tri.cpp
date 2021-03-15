#include "tri.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <GL/glut.h>
using namespace std;   

int tri::pn() { return 3; }

int tri::select(int x, int y) {
	// -1 means the mouse clicked the blank
	int seq = -1;

	// areas
	int s, s12, s34, s56;
	s = x1 * y2 - x1 * y3
		+ x2 * y3 - x2 * y1
		+ x3 * y1 - x3 * y2;

	s12 = x * y2 - x * y3
		+ x2 * y3 - x2 * y
		+ x3 * y - x3 * y2;

	s34 = x1 * y - x1 * y3
		+ x * y3 - x * y1
		+ x3 * y1 - x3 * y;

	s56 = x1 * y2 - x1 * y
		+ x2 * y - x2 * y1
		+ x * y1 - x * y2;

	if (abs(s) == (abs(s12) + abs(s34) + abs(s56))) { seq = 0; }

	return seq;
	
}

void tri::move(int dx, int dy) {
	x1 += dx;
	x2 += dx;
	x3 += dx;
	y1 += dy;
	y2 += dy;
	y3 += dy;
}

void tri::painter() {
	glColor3f(0.7, 0.8, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glEnd();
}

void tri::read() {
	// read err
	if (buf.size() < 6) {
		cout << "read error" << endl;
		return;
	}

	x1 = buf[0];
	y1 = buf[1];
	x2 = buf[2];
	y2 = buf[3];
	x3 = buf[4];
	y3 = buf[5];
}

void tri::save() {
	buf.push_back(id);
	buf.push_back(x1);
	buf.push_back(y1);
	buf.push_back(x2);
	buf.push_back(y2);
	buf.push_back(x3);
	buf.push_back(y3);
}