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
#include "creator.h"
#include "tri_ctr.h"
#include "rec_ctr.h"
#include "line_ctr.h"
#include "pol_ctr.h"
using namespace std;

// used by func line
int dist = 5;

// menuAction
// 0:reset
void menu0(record* t) {
	t->vec.clear();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// reset vars
	memset(t->last, 0, sizeof(t->last));
	t->pnum = -1;
	t->en_select = -1;
	t->en_move = -1;
}
// 1-20:images
void menu1(record* t) {
	t->newvec = new tri;

	// set global values 
	t->pnum = t->newvec->pn();
	t->newvec->buf.clear();

	// stop moving
	t->en_select = -1;
}
void menu2(record* t) {
	t->newvec = new rec;
	t->newvec->buf.clear();

	// set global values 
	t->pnum = t->newvec->pn();

	// stop moving
	t->en_select = -1;
}
void menu3(record* t) {
	t->newvec = new line;
	t->newvec->buf.clear();

	// set global values 
	t->pnum = t->newvec->pn();

	// stop moving
	t->en_select = -1;
}
void menu4(record* t) {
	t->newvec = new pol;
	t->newvec->buf.clear();

	// set global values 
	t->pnum = t->newvec->pn();

	// stop moving
	t->en_select = -1;
}
void menu5(record* t) {}
void menu6(record* t) {}
void menu7(record* t) {}
void menu8(record* t) {}
void menu9(record* t) {}
void menu10(record* t) {}
void menu11(record* t) {}
void menu12(record* t) {}
void menu13(record* t) {}
void menu14(record* t) {}
void menu15(record* t) {}
void menu16(record* t) {}
void menu17(record* t) {}
void menu18(record* t) {}
void menu19(record* t) {}
void menu20(record* t) {}
// 21-27:options
void menu21(record* t) {
	memset(t->last, 0, sizeof(t->last));
	t->en_select = 0;
	t->pnum = -1;
}
void menu22(record* t) {
	t->save();
}
void menu23(record* t) {
	t->vec.clear();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// reset vars
	memset(t->last, 0, sizeof(t->last));
	t->pnum = -1;
	t->en_select = -1;
	t->en_move = -1;

	// load
	t->load();
}
void menu24(record* t) {}
void menu25(record* t) {}
void menu26(record* t) {}
void menu27(record* t) {
	exit(0);
}

// init
record::record() {
	// init creators
	creators.push_back(new tri_ctr);
	creators.push_back(new rec_ctr);
	creators.push_back(new line_ctr);
	creators.push_back(new pol_ctr);

	// init menuAction
	menuAction.push_back(menu0);
	menuAction.push_back(menu1);
	menuAction.push_back(menu2);
	menuAction.push_back(menu3);
	menuAction.push_back(menu4);
	menuAction.push_back(menu5);
	menuAction.push_back(menu6);
	menuAction.push_back(menu7);
	menuAction.push_back(menu8);
	menuAction.push_back(menu9);
	menuAction.push_back(menu10);
	menuAction.push_back(menu11);
	menuAction.push_back(menu12);
	menuAction.push_back(menu13);
	menuAction.push_back(menu14);
	menuAction.push_back(menu15);
	menuAction.push_back(menu16);
	menuAction.push_back(menu17);
	menuAction.push_back(menu18);
	menuAction.push_back(menu19);
	menuAction.push_back(menu20);
	menuAction.push_back(menu21);
	menuAction.push_back(menu22);
	menuAction.push_back(menu23);
	menuAction.push_back(menu24);
	menuAction.push_back(menu25);
	menuAction.push_back(menu26);
	menuAction.push_back(menu27);
}

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
		// read into iobuf
		int iobuf[1024];
		int buffer;
		int n = 0;
		while (infile >> buffer) {
			iobuf[n++] = buffer;
		}

		// read into classes(shape)
		int ptr = 0;
		while (ptr < n - 1) {
			newvec = creators[iobuf[ptr++]]->create();
			newvec->read(ptr, iobuf);
			vec.push_back(newvec);
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

	// show points when drawing
	if (pnum >= 0) {
		glColor3f(0.7, 0.8, 0.6);
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i < newvec->buf.size() / 2; i++) {
			glVertex2d(newvec->buf[2 * i], newvec->buf[2 * i + 1]);
		}
		glEnd();
	}
}

//menu
void record::userEventAction(int key) {
	menuAction[key](this);
	glutPostRedisplay();
	return;
}