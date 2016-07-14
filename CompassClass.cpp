/*
 * CompassClass.cpp
 *
 *  Created on: 2016-06-30
 *      Author: keerthana
 */
// 'a' to rotate clockwise
// 'b' to rotate anticlockwise
#include<iostream>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define PI 3.141592
float i = 0.0f;
int count = 0;
using namespace std;
int ver;
float radius;

class CompassClass {
public:
	CompassClass() {
		ver = 33;
		radius = 0.3;
	}
	void display1(void);
	void Lines(void);
	void keyboardFunc1(unsigned char key, int x, int y);
	void displayText(string txt, float x, float y);
	void Orange_Shades(void);
	void f_rotate(void);
};
void CompassClass::display1(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, 0.0f);
	Lines();
	glLineWidth(4.0);
	// for the rotating needle
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.015, 0.03);
	glVertex2f(0.0, 0.3);
	glVertex2f(0.015, 0.03);
	glEnd();
	glFlush();
	glFlush();
}
void CompassClass::Lines(void) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	for (int i = 0; i <= 2 * ver; i++) {
		glVertex2f(radius * cosf(i * PI / ver), radius * sinf(i * PI / ver));
	}
	glEnd();
	string text[] = { "S", "21", "24", "W", "30", "33", "N", "3", "6", "E",
			"12", "15" };
	glLineWidth(2.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (int i = 0; i <= 2 * ver; i++) {
		if (i % 2 != 0) {
			glVertex2f((radius + 0.02) * cosf(i * PI / ver),
					(radius + 0.02) * sinf(i * PI / ver));
			glVertex2f((radius - 0.03) * cosf(i * PI / ver),
					(radius - 0.03) * sinf(i * PI / ver));
		} else {
			glVertex2f((radius + 0.02) * cosf(i * PI / ver),
					(radius + 0.02) * sinf(i * PI / ver));
			glVertex2f((radius - 0.01) * cosf(i * PI / ver),
					(radius - 0.01) * sinf(i * PI / ver));
		}
	}
	glEnd();
	for (int i = 0; i < 12; i++) {
		glColor3f(1.0, 1.0, 1.0);
		displayText(text[i], -(radius - 0.07) * cosf(i * 5.5 * PI / ver),
				(radius - 0.07) * sinf(i * 5.5 * PI / ver));
	}
	displayText("Vacuum", -0.05, -0.10);
	Orange_Shades();
}

void CompassClass::displayText(string txt, float x, float y) {
	string c = txt;
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12,
			(const unsigned char*) c.c_str());

}
void CompassClass::Orange_Shades() {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.5, 0.0);
	glLineWidth(5.0);
	glVertex2f(0.0, 0.35);
	glVertex2f(0.0, 0.26);
	glVertex2f(0.0, 0.36);
	glVertex2f(0.0, 0.27);
	glEnd();
	glColor3f(1.0, 0.5, 0.0);
	glBegin(GL_TRIANGLES);

	glVertex2f((-0.27), -0.0);
	glVertex2f(-0.35, 0.02);
	glVertex2f(-0.35, -0.02);

	glVertex2f((-0.24), 0.24);
	glVertex2f(-0.27, 0.20);
	glVertex2f(-0.22, 0.19);

	glVertex2f((0.24), 0.24);
	glVertex2f(0.27, 0.20);
	glVertex2f(0.22, 0.19);

	glVertex2f((-0.24), -0.24);
	glVertex2f(-0.27, -0.20);
	glVertex2f(-0.22, -0.19);

	glVertex2f((0.24), -0.24);
	glVertex2f(0.27, -0.20);
	glVertex2f(0.22, -0.19);

	glVertex2f((0.0), -0.27);
	glVertex2f(-0.02, -0.37);
	glVertex2f(0.02, -0.37);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(0.30, 0);
	glVertex2f(0.30, 0.01);
	glVertex2f(0.29, 0.02);
	glVertex2f(0.36, 0.02);
	glVertex2f(0.36, 0.0);
	glEnd();
}

void CompassClass::keyboardFunc1(unsigned char key, int x, int y) {

	if (key == 'a' && i <= 0 && i >= -359) {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glEnable(GL_COLOR_LOGIC_OP);
		i--;
		f_rotate();
		Lines();
		glFlush();

	}

	if (key == 'b' && i < 0 && i >= -360) { //count = 1;
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		//glPushMatrix();
		glEnable(GL_COLOR_LOGIC_OP);
		i++;
		f_rotate();
		Lines();
		glFlush();

	}
}
void CompassClass::f_rotate(void) {
	glLogicOp(GL_OR);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(i, 0.0f, 0.0f, 1.0f);
	glScalef(1.0, 1.0, 1.0);
	glLineWidth(4.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.015, 0.03);
	glVertex2f(0.0, 0.3);
	glVertex2f(0.015, 0.03);
	glEnd();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef((360 - i), 0.0f, 0.0f, 1.0f);
	glScalef(1.0, 1.0, 1.0);
}
CompassClass obj;
void display() {
	obj.display1();
}
void keyboardFunction(unsigned char key, int x, int y) {
	obj.keyboardFunc1(key, 1, 2);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Window");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunction);
	glutInitWindowPosition(0, 0);
	//glutTimerfunc(timeInterval);
	glutMainLoop();
	return 0;
}

