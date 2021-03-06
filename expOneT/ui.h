﻿// iillilllil
// wang.tr@outlook.com
//

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <memory.h>
#include <GL/glut.h>
#include "record.h"
#include "creator.h"

class ui
{
public:
	// windows
	int W = 1000, H = 600;
	
	// paint
	void paint();

private:
	// to modify the c++ linkage
	static ui* ptr;
	
	// indows
	float xwcMin = -200.0, xwcMax = 200.0;
	float ywcMin = -200.0, ywcMax = 200.0;

	// global vars
	record image;

	// menu
	void selectMain(int choice);
	static void selectMainCallback(int choice)
	{
		ptr->selectMain(choice);
	}
	void setupSelectMainCallback()
	{
		ptr = this;
		::glutCreateMenu(ui::selectMainCallback);
	}
	
	void setMenuEntries();

	void init();


	//paint
	void display(void);
	static void displayCallback()
	{
		ptr->display();
	}
	void setupDisplayCallback()
	{
		ptr = this;
		::glutDisplayFunc(ui::displayCallback);
	}

	void mouseButton(int button, int state, int x, int y);
	static void mouseButtonCallback(int button, int state, int x, int y)
	{
		ptr->mouseButton(button, state, x, y);
	}
	void setupMouseButtonCallback()
	{
		ptr = this;
		::glutMouseFunc(ui::mouseButtonCallback);
	}

	void mouseMotion(int x, int y);
	static void mouseMotionCallback(int x, int y)
	{
		ptr->mouseMotion(x, y);
	}
	void setupMouseMotionCallback()
	{
		ptr = this;
		::glutMotionFunc(ui::mouseMotionCallback);
	}

	void myReshape(int w, int h);
	static void myReshapeCallback(int w, int h)
	{
		ptr->myReshape(w, h);
	}
	void setupReshapeCallback()
	{
		ptr = this;
		::glutReshapeFunc(ui::myReshapeCallback);
	}

};