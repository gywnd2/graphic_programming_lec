#include "cg.h"
#include "draw.h"

int w = 1000;
int h = 1000;
float t = 0.0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.6, 0.6, 0.6, 1.0);

	// sun
	glColor3f(1.0, 1.0, 0.0);
	rect(vector2D(-0.1, 0.1), vector2D(0.1, -0.1));

	//earth 
	// RT 와 TR 의 차이 명심할 것
	glPushMatrix();
	glRotatef(3.0 * t, 0.0, 0.0, 1.0);
	glTranslatef(0.8, 0.0, 0.0);  //instancing
	glColor3f(0.0, 0.0, 1.0);
	rect(vector2D(-0.1, 0.05), vector2D(0.1, -0.05));
	
	//moon
	glPushMatrix();
	glRotatef(5*t, 0.0, 0.0, 1.0);
	glTranslatef(-0.2, 0.0, 0.0);// instancing
	glColor3f(1.0, 0.0, 1.0);
	rect(vector2D(-0.02, 0.05), vector2D(0.02, -0.05));
	glPopMatrix();
	
	glPopMatrix();

	glutSwapBuffers();
}

void idle()
{
	t += 0.01;
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
