#include "cg.h"
#include "draw.h"

int w = 800;
int h = 800;

void mydisplay()
{
	// 하늘색을 배경으로 지정
	glClearColor(0.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// 다리 바닥
	glColor3f(0.4, 0.4, 0.4);
	rect(vector2D(-1.0, -0.7), vector2D(1.0, -1.0));

	//건물1
	//어두운 부분
	glColor3f(0.4, 0.4, 0.4);
	rect(vector2D(-0.8, 0.8), vector2D(-0.4, 0.0));
	//밝은 부분
	glColor3f(0.7, 0.7, 0.7);
	rect(vector2D(-0.7, 0.8), vector2D(-0.4, 0.0));
	//창문
	glColor3f(0.0, 0.4, 0.6);
	rect(vector2D(-0.7 , 0.75), vector2D(-0.4, 0.7));
	rect(vector2D(-0.7, 0.65), vector2D(-0.4, 0.6));
	rect(vector2D(-0.7, 0.55), vector2D(-0.4, 0.5));

	//건물2
	//어두운 부분
	glColor3f(0.4, 0.4, 0.4);
	rect(vector2D(0.1, 0.8), vector2D(0.5, 0.0));
	//밝은 부분
	glColor3f(0.7, 0.7, 0.7);
	rect(vector2D(0.2, 0.8), vector2D(0.5, 0.0));
	glColor3f(0.0, 0.4, 0.6);
	rect(vector2D(0.2, 0.75), vector2D(0.5, 0.7));
	rect(vector2D(0.2, 0.65), vector2D(0.5, 0.6));
	rect(vector2D(0.2, 0.55), vector2D(0.5, 0.5));

	//작은 건물(건물3)
	//어두운 부분
	glColor3f(0.2, 0.2, 0.2);
	rect(vector2D(-0.5, 0.75), vector2D(-0.1, 0.0));
	//밝은 부분
	glColor3f(0.5, 0.5, 0.5);
	rect(vector2D(-0.4, 0.75), vector2D(-0.1, 0.0));
	//창문
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

	//공원 길
	glColor3f(0.5, 0.2, 0.0);
	trapzoid(vector2D(-1.8, -0.7), vector2D(-0.2, -0.1));
	trapzoid(vector2D(0.2, -0.7), vector2D(1.8, -0.1));

	//공원 잔디밭
	glColor3f(0.0, 0.6, 0.1);
	trapzoid(vector2D(-2.2, -0.7), vector2D(-0.4, -0.1));
	trapzoid(vector2D(0.4, -0.7), vector2D(2.2, -0.1));

	//공원 경사면
	//좌
	glColor3f(0.0, 0.8, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(1.3, -0.7);
	glVertex2f(0.7, -0.1);
	glVertex2f(1.4, 0.2);
	glEnd();
	//우
	glBegin(GL_POLYGON);
	glVertex2f(-1.3, -0.7);
	glVertex2f(-0.7, -0.1);
	glVertex2f(-1.4, 0.2);
	glEnd();

	// 뒤쪽 다리
	//다리 하부
	glColor3f(0.55, 0.55, 0.55);
	rect(vector2D(-1.0, 0.1), vector2D(1.0, 0.0));

	//난간 윗 손잡이
	glColor3f(0.65, 0.65, 0.65);
	rect(vector2D(-1.0, 0.25), vector2D(1.0, 0.2));


	//난간 다리
	glColor3f(0.65, 0.65, 0.65);
	for (float f = 0.0; f < 2; f += 0.08) {
		rect(vector2D(-0.9 + f, 0.2), vector2D(-0.88 + f, 0.1));
	}
	//다리 하부 기둥
	glColor3f(0.4, 0.4, 0.4);
	for (float f = 0.0; f < 1.7; f += 0.25) {
		rect(vector2D(-0.8 + f, 0.0), vector2D(-0.73 + f, -0.2));
	}
	glColor3f(0.2, 0.2, 0.2);
	for (float f = 0.0; f < 1.7; f += 0.25) {
		rect(vector2D(-0.82 + f, -0.2), vector2D(-0.71 + f, -0.25));
	}

	//앞쪽 다리
	//난간 윗 손잡이
	glColor3f(0.7, 0.7, 0.7);
	rect(vector2D(-1.0, -0.3), vector2D(1.0, -0.4));

	//난간 다리
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