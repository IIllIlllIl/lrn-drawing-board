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
#include "pol.h"
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
		int buffer;

		//read
		while (infile >> buffer) {
			// add to vec
			switch (buffer) {
			case(0):
				//tri
				newvec = new tri;
				newvec->buf.clear();
				for (int i = 0; i < (2*newvec->pn()); i++) {
					infile >> buffer;
					newvec->buf.push_back(buffer);
				}
				newvec->read();
				vec.push_back(newvec);
				break;
			case(1):
				//rec
				newvec = new rec;
				newvec->buf.clear();
				for (int i = 0; i < (2 * newvec->pn()); i++) {
					infile >> buffer;
					newvec->buf.push_back(buffer);
				}
				newvec->read();
				vec.push_back(newvec);
				break;
			case(2):
				//line
				newvec = new line;
				newvec->buf.clear();
				for (int i = 0; i < (2 * newvec->pn()); i++) {
					infile >> buffer;
					newvec->buf.push_back(buffer);
				}
				newvec->read();
				vec.push_back(newvec);
				break;
			defualt:
				cout << "undefined images" << endl;
			}
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
		vec[i]->buf.clear();
		vec[i]->save();
		for (int j = 0; j < vec[i]->buf.size(); j++) {
			outfile << vec[i]->buf[j] << " ";
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
	
	vec[i]->move(dx, dy);
	
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

		// set global values 
		pnum = newvec->pn();
		newvec->buf.clear();

		// stop moving
		en_select = -1;
		break;

		// rectangle
	case '2':
		newvec = new rec;
		newvec->buf.clear();

		// set global values 
		pnum = newvec->pn();

		// stop moving
		en_select = -1;
		break;

		// line
	case '3':
		newvec = new line;
		newvec->buf.clear();

		// set global values 
		pnum = newvec->pn();

		// stop moving
		en_select = -1;
		break;

		// polygon
	case '4':
		newvec = new pol;
		newvec->buf.clear();

		// set global values 
		pnum = newvec->pn();

		// stop moving
		en_select = -1;
		break;
		
		// move
	case '5':
		memset(last, 0, sizeof(last));
		en_select = 0;
		pnum = -1;
		break;

		// save
	case '6':
		save();
		break;

		// load
	case '7':
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
