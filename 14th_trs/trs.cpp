#include "cg.h"
#include "draw.h"

int w = 800;
int h = 800;
float tx=0.0;

void house(float x, float y)
{
	glColor3f(0.8, 0.8, 0.8);
	triangle(vector2D(0.15, 0),vector2D(0, -0.15), vector2D(0.30, -0.15));
	glColor3f(0.2, 0.2, 0.8);
	rect(vector2D(0, -0.15), vector2D(0.3, -0.45));
	glColor3f(0.8, 0.2, 0.2);
	rect(vector2D(0.12, -0.3), vector2D(0.22, -0.45));
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.6, 0.6, 0.6, 1.0);
	// Translation
    glLoadIdentity();
	glTranslatef(tx, 0.0, 0.0);
	glColor3f(1, 1, 1);
	rect(vector2D(-1.2, 0.4), vector2D(-0.8, 0.0));

	glTranslatef(tx, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	rect(vector2D(-1.2, 0.0), vector2D(-0.8, -0.4));

	// Scaling
/*    glLoadIdentity();
	float x = cos(tx);
	glScalef(x, x, x);
	glColor3f(0, 0, 0);
	rect(vector2D(-0.5, 0.5), vector2D(0.5, -0.5));

	glColor3f(1, 1, 1);
	rect(vector2D(-2.5, 1.0), vector2D(-0.5, -1.0));
*/

	//rotation
/*	glRotatef(tx, 0.0, 0.0, 1.0);
	glColor3f(1, 1, 1);
	rect(vector2D(-0.7, 0.7), vector2D(0.7, -0.7));
*/
	// house
/*
* 	for (float x = -1.0; x < 0.8; x += 0.4)
	{
		glLoadIdentity();
		glTranslatef(x, 0.7, 0.0);
		house(x, 0.7);

     	glLoadIdentity();
		glTranslatef(x, -0.2, 0.0);
		house(x, -0.2);
	}
*/



	glutSwapBuffers();
}

void idle()
{
	tx += 0.0001;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("transformations");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();
}
