#include "tri.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <GL/glut.h>
using namespace std;

void tri::load() {
	// read the path
	string path;
	cout << ">load:\t";
	cin >> path;

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
		int* buffer = new int[7];

		//read
		while (infile >> buffer[0]) {
			// read other 6 value
			for (int j = 1; j < 7; j++) {
				infile >> buffer[j];
			}

			// add to vec
			if (buffer[0] == id) {
				vec.push_back(buffer);
			}

			// renew the buffer
			buffer = new int[7];
		}
	}

	infile.close();
}

int tri::select(int x, int y) {
	// -1 means the mouse clicked the blank
	int seq = -1;

	for (int i = 0; i < vec.size(); i++) {
		// read type
		if (vec[i][0] == id) {
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

			if (abs(s) == (abs(s12) + abs(s34) + abs(s56))) { seq = i; }

			if (seq != -1) { break; }
		}

		return seq;
	}
}

void tri::painter() {
	for (int i = 0; i < vec.size(); i++) {
		// show records
		glColor3f(0.7, 0.8, 0.6);

		// triangle
		if (vec[i][0] == id) {
			glBegin(GL_TRIANGLES);
			glVertex2d(vec[i][1], vec[i][2]);
			glVertex2d(vec[i][3], vec[i][4]);
			glVertex2d(vec[i][5], vec[i][6]);
			glEnd();
		}
	}
}