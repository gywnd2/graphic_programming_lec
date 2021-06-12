#include "cg.h"
#include "draw.h"

int w = 1000;
int h = 800;
float t = 0.0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.6, 0.6, 0.6, 1.0);

	glPushMatrix();

	// Base
	glColor3f(0.7, 0.3, 0.3);
	glTranslatef(-0.3, -0.8, 0.0); // instancing : 위치선정
	ellipse(vector2D(0.0, 0.1), 0.2, 0.1);
	
	// Lower Arm
	glColor3f(0.3, 0.3, 0.7);
	glTranslatef(0.0, 0.2, 0.0);   // instancing  : 위치선정
	glRotatef(-15, 0.0, 0.0, 1.0); // instancing  : 방향선정
	ellipse(vector2D(0.0, 0.3), 0.1, 0.3);
	
	// Middle Arm
	glColor3f(0.7, 0.7, 0.3);
	glTranslatef(0.0, 0.6, 0.0);   // instancing  : 위치선정
	glRotatef(-50, 0.0, 0.0, 1.0); // instancing  : 방향선정
	//glRotatef(2*t, 0.0, 0.0, 1.0);
	ellipse(vector2D(0.0, 0.3), 0.08, 0.3);

	// Upper Arm
	glColor3f(0.2, 0.7, 0.3);
	glPushMatrix();
	glTranslatef(0.0, 0.6, 0.0);   // instancing  : 위치선정
	glRotatef(-90, 0.0, 0.0, 1.0); // instancing  : 방향선정
	//glRotatef(t, 0.0, 0.0, 1.0); // 2
	ellipse(vector2D(0.0, 0.3), 0.05, 0.3);
	glPopMatrix();

	glPopMatrix();
	
	glutSwapBuffers();
}

void idle()
{
	t += 0.001;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("transformations");

	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();
}
