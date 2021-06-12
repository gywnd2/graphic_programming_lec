#include "cg.h"
#include "draw.h"

int w = 1000;
int h = 600;
float t = 0.0001;

void house()
{
	glColor3f(0.8, 0.8, 0.8);
	triangle(vector2D(0.15, 0), vector2D(0, -0.15), vector2D(0.30, -0.15));
	glColor3f(0.2, 0.2, 0.8);
	rect(vector2D(0, -0.15), vector2D(0.3, -0.45));
	glColor3f(0.8, 0.2, 0.2);
	rect(vector2D(0.12, -0.3), vector2D(0.22, -0.45));
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glClearColor(0.6, 0.6, 0.6, 1.0);
	
	// house moving animation
//	glTranslatef(t, t, 0.0); // T T T T T house
//	house(); 

	// Animation °ú Instancing(TRS)
	glTranslatef(t, t, 0.0);
	glPushMatrix();
	glTranslatef(-1.0, -.5, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);  //  T(t, t )*T(-1.0, -0.5) * R * house 
	house();
	glPopMatrix();
	
	glutSwapBuffers();
}

void idle()
{
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
