#include "pol.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <GL/glut.h>
using namespace std;

int pol::pn() { return 100; }

int pol::select(int x,int y) {
	return 0;
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
	for (int i = 0; i < x.size(); i++) {
		x[i] = buf[2 * i];
		y[i] = buf[2 * i + 1];
	}
}

void pol::save() {
	buf.push_back(id);
	for (int i = 0; i < x.size(); i++) {
		buf.push_back(x[i]);
		buf.push_back(y[i]);
	}
	buf.push_back(0x7f7f7f7f);
}