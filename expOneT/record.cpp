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
#include "tri.h"
#include "rec.h"
#include "line.h"
using namespace std;

// used by func line
int dist = 5;

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
			switch (buffer[0]) {
			case(0):
				//tri
				newvec = new tri;
				for (int i = 0; i < len; i++) {
					newvec->vec[i] = buffer[i];
				}
				vec.push_back(newvec);
				break;
			case(1):
				//rec
				newvec = new rec;
				for (int i = 0; i < len; i++) {
					newvec->vec[i] = buffer[i];
				}
				vec.push_back(newvec);
				break;
			case(2):
				//line
				newvec = new line;
				for (int i = 0; i < len; i++) {
					newvec->vec[i] = buffer[i];
				}
				vec.push_back(newvec);
				break;
			defualt:
				cout << "undefined images" << endl;
			}
			// renew the buffer
			buffer = new int[len];
		}

		/*for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < 7; j++) {
				cout << vec[i].vec[j] << " ";
			}
			cout << endl;
		}*/
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
			outfile << vec[i]->vec[j] << " ";
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
		seq = vec[i]->select(x, y);

		if (seq != -1) { break; }
	}

	return i;
}

// move
int record::shift(int i, int dx, int dy) {
	if (i >= vec.size()) { return -2; }

	for (int j = 0; j < 3; j++) {
		vec[i]->vec[2 * j + 1] += dx;
		vec[i]->vec[2 * j + 2] += dy;
	}

	return 0;
}

//paint
void record::painter() {
	for (int i = 0; i < vec.size(); i++) {
		vec[i]->painter();
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
		newvec = new tri;
		newvec->vec[0] = 0;

		// set global values 
		pnum = newvec->pn();

		// stop moving
		en_select = -1;
		break;

		// rectangle
	case '2':
		newvec = new rec;
		newvec->vec[0] = 1;

		// set global values 
		pnum = newvec->pn();

		// stop moving
		en_select = -1;
		break;

		// line
	case '3':
		newvec = new line;
		newvec->vec[0] = 2;

		// set global values 
		pnum = newvec->pn();

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
