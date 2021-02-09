// iillilllil
// wang.tr@outlook.com
//

#include "record.h"
#include "ui.h"



// menu
ui::menuEntryStruct mainMenu[] = {
	"clear",		  '0',
	"triangle",       '1',
	"rectangle",      '2',
	"line",           '3',
	"move",           '4',
	"save",			  '5',
	"load",			  '6',
	"quit", 		  27,
};
int mainMenuEntries = sizeof(mainMenu) / sizeof(ui::menuEntryStruct);

void ui::userEventAction(int key) {
	switch (key)
	{
		// reset
	case '0':
		image.vec.clear();
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
		// create new record
		newvec = new int[image.len];
		memset(newvec, 0, sizeof(newvec));

		// set global values 
		pnum = image.pn[newvec[0]];

		// stop moving
		en_select = -1;
		break;

		// rectangle
	case '2':
		// create new record
		newvec = new int[image.len];
		memset(newvec, 0, sizeof(newvec));
		newvec[0] = 1;

		// set global values 
		pnum = image.pn[newvec[0]];

		// stop moving
		en_select = -1;
		break;

		// line
	case '3':
		// create new record
		newvec = new int[image.len];
		memset(newvec, 0, sizeof(newvec));
		newvec[0] = 2;

		// set global values 
		pnum = image.pn[newvec[0]];

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
		image.save();
		break;

		// load
	case '6':
		image.vec.clear();
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// reset vars
		memset(last, 0, sizeof(last));
		pnum = -1;
		en_select = -1;
		en_move = -1;

		// load
		image.load();
		break;

		// quit
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
	return;
}

void ui::selectMain(int choice) { userEventAction(mainMenu[choice].key); }

void ui::setMenuEntries() {
	setupSelectMainCallback();
	for (int i = 0; i < mainMenuEntries; i++) {
		glutAddMenuEntry(mainMenu[i].label, i);
	}

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void ui::init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glLineWidth(5);
	setMenuEntries();
}


// painter
void ui::display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	image.painter();
	glFlush();
}

void ui::mouseButton(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
	{
		x = x * (xwcMax - xwcMin) / W;         
		x -= xwcMax;
		y = y * (ywcMax - ywcMin) / H;
		y -= ywcMax;
		y = -y;

		// write into pvalues
		if (pnum > 0) {
			newvec[2 * pnum - 1] = x;
			newvec[2 * pnum] = y;
			pnum--;
		}
		if (pnum == 0) {
			//add to image
			image.vec.push_back(newvec);
			pnum = -1;
		}

		// selcet
		if (pnum == -1 && en_select == 0) {
			index = image.select(x, y);
			if (index >= 0) {
				en_move = 0;
				memset(last, 0, sizeof(last));
			}
		}

		// dispaly
		glutPostRedisplay();
	}
	else if (GLUT_UP) {
		// stop moving
		en_move = -1;

		// dispaly
		glutPostRedisplay();
	}
}

void ui::mouseMotion(int x, int y) {
	x = x * (xwcMax - xwcMin) / W;
	x -= xwcMax;
	y = y * (ywcMax - ywcMin) / H;
	y -= ywcMax;
	y = -y;

	// move
	if (en_move == 0) {
		int dx, dy;
		if (last[0] * last[1] == 0) {
			dx = dy = 0;
		}
		else {
			dx = x - last[0];
			dy = y - last[1];
		}

		last[0] = x;
		last[1] = y;

		// rewrite the image
		if (index >= 0) {
			image.shift(index, dx, dy);
		}
	}

	glutPostRedisplay();
	return;
}

void ui::myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ui::paint() {
	init();
	setupDisplayCallback();
	setupReshapeCallback();
	setupMouseButtonCallback();
	setupMouseMotionCallback();
}


