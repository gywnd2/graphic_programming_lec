#include "cg.h"
#include "draw.h"

int w = 800;
int h = 800;

void mydisplay()
{
	glClearColor(0.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	// 길 바닥
	glColor3f(0.4, 0.4, 0.4);
	rect(vector2D(-1.0, -0.7), vector2D(1.0, -1.0));
	//빌딩
	glColor3f(0.4, 0.4, 0.4);
	rect(vector2D(-0.8, 0.8), vector2D(-0.4, 0.0));
	glColor3f(0.7, 0.7, 0.7);
	rect(vector2D(-0.7, 0.8), vector2D(-0.4, 0.0));
	glColor3f(0.0, 0.4, 0.6);
	rect(vector2D(-0.7 , 0.75), vector2D(-0.4, 0.7));
	rect(vector2D(-0.7, 0.65), vector2D(-0.4, 0.6));
	rect(vector2D(-0.7, 0.55), vector2D(-0.4, 0.5));

	glColor3f(0.4, 0.4, 0.4);
	rect(vector2D(0.1, 0.8), vector2D(0.5, 0.0));
	glColor3f(0.7, 0.7, 0.7);
	rect(vector2D(0.2, 0.8), vector2D(0.5, 0.0));
	glColor3f(0.0, 0.4, 0.6);
	rect(vector2D(0.2, 0.75), vector2D(0.5, 0.7));
	rect(vector2D(0.2, 0.65), vector2D(0.5, 0.6));
	rect(vector2D(0.2, 0.55), vector2D(0.5, 0.5));

	glColor3f(0.2, 0.2, 0.2);
	rect(vector2D(-0.5, 0.75), vector2D(-0.1, 0.0));
	glColor3f(0.5, 0.5, 0.5);
	rect(vector2D(-0.4, 0.75), vector2D(-0.1, 0.0));
	glColor3f(0.0, 0.4, 0.6);
	rect(vector2D(-0.4, 0.7), vector2D(-0.1, 0.65));
	rect(vector2D(-0.4, 0.6), vector2D(-0.1, 0.55));
	rect(vector2D(-0.4, 0.5), vector2D(-0.1, 0.45));

	//뒷산
	glColor3f(0.0, 0.4, 0.0);
	ridge(vector2D(-0.6, -0.1), 0.8, 0.6);
	//앞산
	glColor3f(0.0, 0.5, 0.0);
	ridge(vector2D(0.4, -0.1), 0.8, 0.6);
	//강물
	glColor3f(0.0, 0.6, 0.6);
	trapzoid(vector2D(-0.8, -0.1), vector2D(0.8, -0.7));
	//공원 바닥
	glColor3f(0.5, 0.2, 0.0);
	trapzoid(vector2D(-1.8, -0.7), vector2D(-0.2, -0.1));
	trapzoid(vector2D(0.2, -0.7), vector2D(1.8, -0.1));
	//공원 잔디밭
	glColor3f(0.0, 0.6, 0.1);
	trapzoid(vector2D(-2.2, -0.7), vector2D(-0.4, -0.1));
	trapzoid(vector2D(0.4, -0.7), vector2D(2.2, -0.1));
	//공원 경사면
	glColor3f(0.0, 0.8, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(1.3, -0.7);
	glVertex2f(0.7, -0.1);
	glVertex2f(1.4, 0.2);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-1.3, -0.7);
	glVertex2f(-0.7, -0.1);
	glVertex2f(-1.4, 0.2);
	glEnd();

	// 뒤쪽 다리
	glColor3f(0.55, 0.55, 0.55);
	rect(vector2D(-1.0, 0.1), vector2D(1.0, 0.0));
	// 난간2
	glColor3f(0.65, 0.65, 0.65);
	rect(vector2D(-1.0, 0.25), vector2D(1.0, 0.2));
	//난간 창살
	glColor3f(0.65, 0.65, 0.65);
	for (float f = 0.0; f < 2; f += 0.08) {
		rect(vector2D(-0.9 + f, 0.2), vector2D(-0.88 + f, 0.1));
	}
	glColor3f(0.4, 0.4, 0.4);
	for (float f = 0.0; f < 1.7; f += 0.25) {
		rect(vector2D(-0.8 + f, 0.0), vector2D(-0.73 + f, -0.2));
	}
	glColor3f(0.2, 0.2, 0.2);
	for (float f = 0.0; f < 1.7; f += 0.25) {
		rect(vector2D(-0.82 + f, -0.2), vector2D(-0.71 + f, -0.25));
	}

	//난간
	glColor3f(0.7, 0.7, 1.0);
	//윗 손잡이
	rect(vector2D(-1.0, -0.3), vector2D(1.0, -0.4));
	//난간 창살
	glColor3f(0.5, 0.5, 0.5);
	for (float f = 0.0; f < 2; f += 0.15) {
		rect(vector2D(-0.9+f, -0.4), vector2D(-0.88+f, -0.7));
	}
	rect(vector2D(-1.0, -0.3), vector2D(1.0, -0.4));

	//사람들
	glColor3f(0.8, 0.8, 0.8);
	people(vector2D(-0.9, -0.5), vector2D(-0.5, -0.9));
	people(vector2D(-0.6, -0.4), vector2D(-0.2, -0.8));
	people(vector2D(-0.7, -0.5), vector2D(-0.3, -0.9));
	people(vector2D(-0.2, -0.5), vector2D(0.2, -0.9));
	people(vector2D(0.4, -0.5), vector2D(0.8, -0.9));

	glutSwapBuffers();
}

void reshape(int rw, int rh) {
	w = rw;
	h = rh;
	glViewport(0, 0, w, h);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(w, h);
	glutCreateWindow("simple");
	glutReshapeFunc(reshape);
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}