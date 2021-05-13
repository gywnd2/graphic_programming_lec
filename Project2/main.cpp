#include "cg.h"
#include <stdlib.h>
#define Width 800
#define Height 600
float red = 1.0, green = 1.0, blue = 1.0;
float startX, startY, endX, endY;
int shape = 0;

void line() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(5.0);
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
	glVertex2f(startX, startY);
	glVertex2f(endX, endY);
	glEnd();
	glFlush();
}

void ellipse() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(red, green, blue);

	float radius = (endX-startX)/2;
	float angle = 3.14 / 180;
	int maxAngle = 360;

	glBegin(GL_POLYGON);
	for (int i = 0; i < maxAngle; i++) {
		float theta = i * angle;
		glVertex2f((cos(theta) * radius), (sin(theta) * radius));
	}
	glEnd();
	glFlush();
}


void triangle() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(red, green, blue);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, startY);
	glVertex2f(startX, endY);
	glVertex2f(endX, endY);
	glEnd();
	glFlush();
}

void rect()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(red, green, blue);
	glBegin(GL_POLYGON);
	glVertex2f(startX, endY);
	glVertex2f(startX, startY);
	glVertex2f(endX, startY);
	glVertex2f(endX, endY);
	glEnd();
	glFlush();
}


void fitOnWindow(int width, int height) {
	if (height == 0) { height = 1; }
	GLfloat ratio = 1.0 * Width / Height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;

	glViewport(0, 0, Width, Height);

	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.4, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}

/*
* void dragMouse(int x, int y) {
	GLint dx, dy;
	if (curX >= 0 || curY >= 0) {
		dx = abs(x - curX);
		dy = abs(y - curY);
		GLint sum = dx + dy;
		if (sum > 0) { 
			shape = (shape + 1) % 4;
			printf("shape : %d\n", shape);
			glutPostRedisplay();
		}
	}
}
*/


void detectButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		startX = (float)((x - (float)Width / 2.0) * (float)(1.0 / (float)(Width / 2.0)));
		startY = -(float)((y - (float)Height / 2.0) * (float)(1.0 / (float)(Height / 2.0)));
		printf("startX: %f, startY=%f\n", startX, startY);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		endX = (float)((x - (float)Width / 2.0) * (float)(1.0 / (float)(Width / 2.0)));
		endY = -(float)((y - (float)Height / 2.0) * (float)(1.0 / (float)(Height / 2.0)));
		printf("endX=%f, endY=%f\n", endX, endY);
	}
}

void detectKey(unsigned char key, int x, int y) {
	printf("%d", key);
	switch (key) {
	case 'r': red = 1.0; green = 0.0; blue = 0.0; break;
	case 'g': red = 0.0; green = 1.0; blue = 0.0; break;
	case 'b': red = 0.0; green = 0.0; blue = 1.0; break;
	case 'c': red = 0.0; green = 1.0; blue = 1.0; break;
	case 'y': red = 1.0; green = 1.0; blue = 0.0; break;
	case 'm': red = 1.0; green = 0.0; blue = 1.0; break;
	case 'w': red = 1.0; green = 1.0; blue = 1.0; break;
	case 49: shape = 1; break;
	case 50: shape = 2; break;
	case 51: shape = 3; break;
	case 52: shape = 4; break;
	case 127: shape = 5; break;
	case 27: exit(0);
	default: break;
	}
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (shape) {
	case 1: line(); break;
	case 2: ellipse(); break;
	case 3: triangle(); break;
	case 4: rect(); break;
	case 5: glClear(GL_COLOR_BUFFER_BIT); break;
	default: break;
	}
	glutSwapBuffers();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Project 2");
	glutDisplayFunc(mydisplay);
	//glutReshapeFunc(fitOnWindow);
	glutKeyboardFunc(detectKey);
	glutMouseFunc(detectButton);
	//glutMotionFunc(dragMouse);
	glutIdleFunc(mydisplay);
	glutMainLoop();
}
