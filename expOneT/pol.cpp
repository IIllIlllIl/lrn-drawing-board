#include "pol.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <GL/glut.h>
using namespace std;

#define e(x) cout<<#x<<"="<<x<<endl;
#define c(y) cout<<#y<<endl;

int pol::pn() { return 100; }

int pol::select(int px,int py) {
	for (int i = 1; i < x.size() - 1; i++) {
		if (tri(px, py, i) == 0) {
			return 0;
		}
	}

	return -1;
}

void pol::move(int dx, int dy) {
	for (int i = 0; i < x.size(); i++) {
		x[i] += dx;
		y[i] += dy;
	}
}

void pol::painter() {
	glColor3f(0.7, 0.8, 0.6);
	glBegin(GL_POLYGON);
	for (int i = 0; i < x.size(); i++) {
		glVertex2d(x[i], y[i]);
	}
	glEnd();
}

void pol::read() {
	for (int i = 0; i < buf.size() / 2; i++) {
		x.push_back(buf[2 * i]);
		y.push_back(buf[2 * i + 1]);
	}
}

void pol::save() {
	buf.push_back(id);
	buf.push_back(x.size());
	for (int i = 0; i < x.size(); i++) {
		buf.push_back(x[i]);
		buf.push_back(y[i]);
	}
}

int pol::end(int x, int y) {
	for (int i = 0; i < buf.size() / 2; i++) {
		if (abs(x - buf[2 * i]) < 3
		&& abs(y - buf[2 * i + 1]) < 3) {
			return 0;
		}
	}

	return 1;
}

int pol::tri(int px, int py, int i) {
	int seq = -1;

	// areas
	int s, s12, s34, s56;
	s = x[0] * y[i] - x[0] * y[i+1]
		+ x[i] * y[i+1] - x[i] * y[0]
		+ x[i+1] * y[0] - x[i+1] * y[i];

	s12 = px * y[i] - px * y[i+1]
		+ x[i] * y[i+1] - x[i] * py
		+ x[i+1] * py - x[i+1] * y[i];

	s34 = x[0] * py - x[0] * y[i+1]
		+ px * y[i+1] - px * y[0]
		+ x[i+1] * y[0] - x[i+1] * py;

	s56 = x[0] * y[i] - x[0] * py
		+ x[i] * py - x[i] * y[0]
		+ px * y[0] - px * y[i];

	if (abs(s) == (abs(s12) + abs(s34) + abs(s56))) { seq = 0; }

	return seq;
}