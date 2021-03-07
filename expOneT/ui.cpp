// iillilllil
// wang.tr@outlook.com
//

#include "record.h"
#include "ui.h"

#define e(x) cout<<#x<<"="<<x<<endl;
#define c(y) cout<<#y<<endl;

// menu
record::menuEntryStruct mainMenu[] = {
	"clear",		  '0',
	"triangle",       '1',
	"rectangle",      '2',
	"line",           '3',
	"move",           '4',
	"save",			  '5',
	"load",			  '6',
	"quit", 		  27,
};
int mainMenuEntries = sizeof(mainMenu) / sizeof(record::menuEntryStruct);

void ui::selectMain(int choice) { image.userEventAction(mainMenu[choice].key); }

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
		if (image.pnum > 0) {
			image.newvec->vec[2 * image.pnum - 1] = x;
			image.newvec->vec[2 * image.pnum] = y;
			image.pnum--;
		}
		if (image.pnum == 0) {
			//add to image
			image.vec.push_back(*image.newvec);
			image.newvec = new shape;
			image.pnum = -1;
		}

		// selcet
		if (image.pnum == -1 && image.en_select == 0) {
			image.index = image.select(x, y);
			if (image.index >= 0) {
				image.en_move = 0;
				memset(image.last, 0, sizeof(image.last));
			}
		}

		// dispaly
		glutPostRedisplay();
	}
	else if (GLUT_UP) {
		// stop moving
		image.en_move = -1;

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
	if (image.en_move == 0) {
		int dx, dy;
		if (image.last[0] * image.last[1] == 0) {
			dx = dy = 0;
		}
		else {
			dx = x - image.last[0];
			dy = y - image.last[1];
		}

		image.last[0] = x;
		image.last[1] = y;

		// rewrite the image
		if (image.index >= 0) {
			image.shift(image.index, dx, dy);
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


