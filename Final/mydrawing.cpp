#include "cg.h"
#include "draw.h"

int w = 600;
int h = 600;
float tx = 0.0;

void ferrisWheel(vector2D a, vector2D b)
{	
	vector2D center = vector2D((b.x + a.x) / 2, (a.y - b.y) / 2+0.1);
	// 관람차 원
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.0);
	glRotatef(10.0 * tx, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.15, 0.0);
	glColor4f(0.6, 0.6, 0.6, 1.0);
	glBegin(GL_LINE_STRIP);
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 36.0) {
		float x, y;
		x = 0.4 * cos(f);
		y = 0.15 + 0.4 * sin(f);
		glVertex2f(x, y);
	}
	glEnd();

	// 빗살
	glColor3f(0.6, 0.6, 0.6);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	for (float f = 0.0; f < 2 * M_PI; f += 0.7) {
		glVertex2f(0, 0.15);
		float x, y;
		x = 0.4 * cos(f);
		y = (-0.4 + 0.5) / 2 + 0.1 + 0.4 * sin(f);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	// 기둥
	glColor4f(0.65, 0.65, 0.65, 1.0);
	float axb = a.x, ayb = a.y - 0.1, bxb = b.x - 0.05, byb = b.y + 0.1;
	triangle(vector2D(a.x, b.y), center, vector2D(a.x+0.1, b.y));
	triangle(vector2D(b.x-0.1, b.y), center, vector2D(b.x, b.y));
	glColor4f(0.45, 0.45, 0.45, 1.0);
	triangle(vector2D(a.x, b.y), center, vector2D(a.x + 0.05, b.y));
	triangle(vector2D(b.x-0.1, b.y), center, vector2D(b.x-0.06, b.y));

	glColor3f(0.4, 0.4, 0.4);
	circle(vector2D(0.0, 0.15), 0.1);
}

void ferrisCoach() {
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.0);
	glRotatef(10.0 * tx, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.15, 0.0);
	for (float f = 0.0; f < 2 * M_PI; f += 0.7) {
		glPushMatrix();
		glTranslatef(0.4 * cos(f), 0.15 + 0.4 * sin(f), 0.0);
		glRotatef(-(10.0 * tx), 0.0, 0.0, 1.0);
		glTranslatef(-(0.4 * cos(f)), -(0.15 + 0.4 * sin(f)), 0.0);
		float x, y;
		glColor3f(1.0, 0.5, 0.5);
		x = 0.4 * cos(f);
		y = 0.15 + 0.4 * sin(f);
		circle(vector2D(x, y), 0.09);
		glColor3f(0.3, 0.7, 1.0);
		ridge(vector2D(x, y), 0.07, 0.07);
		glPopMatrix();
	}
	glPopMatrix();
}

void rollerCoaster() {
	// 롤러코스터 기둥
	glColor3f(0.4, 0.4, 0.4);
	for (float i = -10.0; i <= 10.0; i += 1.2) {
		rect(vector2D(0.3 * i, 0.2 * sin(i - 0.3) + 0.55), vector2D(0.3 * i + 0.12, -0.3));
	}
	glColor3f(0.2, 0.2, 0.2);
	for (float i = -10.0; i <= 10.0; i += 1.2) {
		rect(vector2D(0.3 * i, 0.2 * sin(i - 0.3) + 0.55), vector2D(0.3 * i + 0.04, -0.3));
	}
	glColor3f(0.1, 0.1, 0.1);
	for (float i = -10.0; i <= 10.0; i += 1.2) {
		rect(vector2D(0.3 * i - 0.03, -0.25), vector2D(0.3 * i + 0.15, -0.3));
	}

	// 선로
	glLineWidth(50.0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.6, 0.6, 0.0);
	for (float i = -5.0; i <= 5.0; i += 0.01) {
		glVertex2f(0.3 * i, 0.2 * sin(i - 0.3)+0.55);
	}
	glEnd();

	glLineWidth(25.0);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.3, 0.3, 0.0);
	for (float i = -5.0; i <= 5.0; i += 0.01) {
		glVertex2f(0.3 * i, 0.2 * sin(i - 0.3)+0.5);
	}
	glEnd();
}

void rollerCar() {
	// 객차 6개
	glColor3f(0.0, 0.2, 0.6);
	glPushMatrix();
	glTranslatef(0.3 * (-2.0 + tx), 0.2 * sin((-2.0 + tx) - 0.3), 0.0);
	circle(vector2D(-1.82, 0.65), 0.11);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3 * (-2.5 + tx), 0.2 * sin((-2.5 + tx) - 0.3), 0.0);
	circle(vector2D(-1.82, 0.65), 0.11);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3 * (-3.0 + tx), 0.2 * sin((-3.0 + tx) - 0.3), 0.0);
	circle(vector2D(-1.82, 0.65), 0.11);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3 * (-3.5 + tx), 0.2 * sin((-3.5 + tx) - 0.3), 0.0);
	circle(vector2D(-1.82, 0.65), 0.11);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3 * (-4.0 + tx), 0.2 * sin((-4.0 + tx) - 0.3), 0.0);
	circle(vector2D(-1.82, 0.65), 0.11);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3 * (-4.5 + tx), 0.2 * sin((-4.5 + tx) - 0.3), 0.0);
	circle(vector2D(-1.82, 0.65), 0.11);
	glPopMatrix();
}

void gradient() {
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0, -1.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(1.0, -0.3);
	glVertex2f(-1.0, -0.3);
	glEnd();
}

void candyShop() {
	// 오른쪽 가게
	glColor3f(1.0, 0.45, 0.8);
	rect(vector2D(0.45, -0.05), vector2D(1.05, -0.55));
	glColor3f(0.3, 0.7, 1.0);
	rect(vector2D(0.55, -0.15), vector2D(1.0, -0.35));
	glColor3f(0.4, 0.25, 0.0);
	rect(vector2D(0.5, -0.3), vector2D(1.0, -0.35));
	glColor3f(1.0, 0.25, 0.6);
	trapzoid(vector2D(0.4, 0.1), vector2D(1.3,-0.1));

	// 왼쪽 가게
	glColor3f(0.7, 0.55, 0.6);
	rect(vector2D(-1.45, -0.05), vector2D(-0.7, -0.55));
	glColor3f(0.3, 0.7, 1.0);
	rect(vector2D(-1.45, -0.15), vector2D(-0.75, -0.35));
	glColor3f(0.4, 0.25, 0.0);
	rect(vector2D(-1.5, -0.3), vector2D(-0.72, -0.35));
	glColor3f(0.8, 0.55, 0.6);
	trapzoid(vector2D(-1.4, 0.1), vector2D(-0.6, -0.1));
}

void star() {
	// 별 꼬리
	glPushMatrix();
	glColor4f(1.0, 1.0, 0.0, 0.6);
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(0.4*tx, -0.4*tx, 0.0);
	glTranslatef(-0.3, 1.2, 0.0);
	glLineWidth(5.0);
	line(vector2D(-0.8, 0.8), vector2D(-0.5, 0.6));
	line(vector2D(-0.7, 0.8), vector2D(-0.4, 0.6));

	// 별
	glTranslatef(0.1, 0.1, 0.0);
	glScalef(0.8, 0.8, 0.0);
	glColor4f(1.0, 1.0, 0.0, 1.0);
	triangle(vector2D(-0.67,0.3), vector2D(-0.52, 0.6), vector2D(-0.45, 0.4));
	triangle(vector2D(-0.67,0.5), vector2D(-0.35, 0.5), vector2D(-0.55, 0.37));
	triangle(vector2D(-0.52, 0.6), vector2D(-0.6, 0.4), vector2D(-0.38, 0.3));
	glPopMatrix();
}

void mountain() {
	glColor3f(0.0, 0.2, 0.0);
	ridge(vector2D(-0.5, -0.3), 1.0, 0.7);
	glColor3f(0.0, 0.4, 0.0);
	ridge(vector2D(0.5, -0.3), 1.0, 0.5);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 하늘 색으로 초기화
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// 별똥별
	star();
	// 산 두개
	mountain();
	// 객차
	rollerCar();
	// 롤러코스터
	rollerCoaster();
	// 지면 그라데이션
	gradient();
	// 관람차
	ferrisWheel(vector2D(-0.3, -0.4), vector2D(0.3, -0.5));
	// 캡슐
	ferrisCoach();
	// 가게 뒤편을 지나가는 사람들
	glPushMatrix();
	glTranslatef(0.2*tx, 0.0, 0.0);
	glColor3f(0.7, 0.7, 0.7);
	people(vector2D(-3.0, -0.2), vector2D(-2.75, -0.5));
	people(vector2D(-2.9, -0.2), vector2D(-2.65, -0.5));
	glPopMatrix();

	// 가게
	candyShop();
	
	// 오른쪽 가게에 서있는 사람들
	glColor3f(0.9, 0.9, 0.9);
	people(vector2D(0.45, -0.3), vector2D(0.7, -0.6));
	people(vector2D(0.6, -0.4), vector2D(0.8, -0.6));
	people(vector2D(0.7, -0.3), vector2D(0.95, -0.6));
	
	// 왼쪽 가게에 서있는 사람들
	glColor3f(0.9, 0.9, 0.9);
	people(vector2D(-0.95, -0.3), vector2D(-0.6, -0.6));
	people(vector2D(-0.65, -0.4), vector2D(-0.45, -0.6));

	// 가운데 서있는 사람들
	glColor3f(0.9, 0.9, 0.9);
	people(vector2D(-0.1, -0.5), vector2D(0.1, -0.8));
	people(vector2D(0.0, -0.5), vector2D(0.3, -0.8));

	// 오른쪽에서 오는 가족
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.2 * tx, 0.0, 0.0);
	people(vector2D(1.75, -0.6), vector2D(2.0, -0.9));
	people(vector2D(1.9, -0.7), vector2D(2.1, -0.9));
	people(vector2D(2.0, -0.6), vector2D(2.25, -0.9));
	glPopMatrix();

	glutSwapBuffers();
}

void idle()
{
	// tx가 20에 도달 할 경우 
	if (tx >= 20.0) { tx = 0.0; }
	else { tx += 0.001; }
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("Final");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
}