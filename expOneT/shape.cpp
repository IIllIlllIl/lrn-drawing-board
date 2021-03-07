#include "shape.h" 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <GL/glut.h>
using namespace std;

#define e(x) cout<<#x<<"="<<x<<endl;
#define c(y) cout<<#y<<endl;

void shape::painter() {
	glColor4f(0.6, 0.7, 0.5, 0.1);

	// triangle
	if (vec[0] == 0) {
		glBegin(GL_TRIANGLES);
		glVertex2d(vec[1], vec[2]);
		glVertex2d(vec[3], vec[4]);
		glVertex2d(vec[5], vec[6]);
		glEnd();
	}
	// rectangle
	if (vec[0] == 1) {
		glRecti(vec[1], vec[2], vec[3], vec[4]);
	}
	// line
	if (vec[0] == 2) {
		glBegin(GL_LINES);
		glVertex2d(vec[1], vec[2]);
		glVertex2d(vec[3], vec[4]);
		glEnd();
	}
}

// select
int shape::select(int x, int y) {
	// -1 means the mouse clicked the blank
	int seq = -1;

	// rec&line
	int x1, x2, y1, y2;

	// read type
	switch (vec[0]) {
		// triangle
		case(0):
			// areas
			int s, s12, s34, s56;
			s = vec[1] * vec[4] - vec[1] * vec[6]
				+ vec[3] * vec[6] - vec[3] * vec[2]
				+ vec[5] * vec[2] - vec[5] * vec[4];

			s12 = x * vec[4] - x * vec[6]
				+ vec[3] * vec[6] - vec[3] * y
				+ vec[5] * y - vec[5] * vec[4];

			s34 = vec[1] * y - vec[1] * vec[6]
				+ x * vec[6] - x * vec[2]
				+ vec[5] * vec[2] - vec[5] * y;

			s56 = vec[1] * vec[4] - vec[1] * y
				+ vec[3] * y - vec[3] * vec[2]
				+ x * vec[2] - x * vec[4];

			if (abs(s) == (abs(s12) + abs(s34) + abs(s56))) { seq = 0; }

			break;

		// rectangle
		case(1):
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
			break;

		// line
		case(2):
			// use rectangle
			// the edges(x1 <= x2, y1 <= y2)
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
			if (x > x1&& x<x2 && y>y1&& y < y2){
				// the func of the line
				int a, b, c;
				a = vec[4] - vec[2];
				b = vec[1] - vec[3];
				c = vec[3] * vec[2] - vec[1] * vec[4];

				// distance
				double d, d1, d2;
				d1 = fabs(a * x + b * y + c);
				d2 = sqrt((pow(a, 2) + pow(b, 2)));
				d = d1 / d2;

				if (d <= 5) { seq = 0; }
			}
			break;

		default:
			seq = -2;
	}
	return seq;
}
