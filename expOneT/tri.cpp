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

	return seq;
	
}

void tri::painter() {
	glColor3f(0.7, 0.8, 0.6);

	// triangle
	if (vec[0] == id) {
		glBegin(GL_TRIANGLES);
		glVertex2d(vec[1], vec[2]);
		glVertex2d(vec[3], vec[4]);
		glVertex2d(vec[5], vec[6]);
		glEnd();		
	}
}

void tri::save() {

}