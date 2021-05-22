#include "cg.h"


void rect(float x1, float y1, float x2, float y2)
{
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}


void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.6, 0.3, 0.2);
	rect(-1, -1, 1, 1);
	glColor3f(0.0, 0.5, 0.3);
	rect(-0.7, -1, 0.7, 0.7);
	glColor3f(0.0, 0.3, 0.5);
	rect(-0.5, -1, 0.5, 0.3);
	glColor3f(0.6, 0.6, 0.6);
	rect(-0.2, -1, 0.2, -0.3);
	glutSwapBuffers();
}

/*
void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glutSwapBuffers();
}
*/

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);

	glutMainLoop();
}
