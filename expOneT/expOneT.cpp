// iillilllil
// wang.tr@outlook.com
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <memory.h>
#include <GL/glut.h>
#include "record.h"
#include "ui.h"

// 用函数调用gui的函数
ui gui;
ui* ui::ptr = &gui;

void main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(gui.W, gui.H);
	glutCreateWindow("pianter");
	gui.paint();
	glutMainLoop();
	return;
}