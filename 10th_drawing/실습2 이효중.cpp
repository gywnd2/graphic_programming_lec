#include "cg.h"
#include <stdlib.h>
#include "vec.h"
float red = 1.0, green = 1.0, blue = 1.0;
int w = 512, h = 512, count;
bool isAnim = false;
vector3D points[100];

void reshape(int rw, int rh) {
	w = rw;
	h = rh;
	glViewport(0, 0, w, h);
}

void idle() {
	if (isAnim) {
		for (int i = 0; i < count; i++)
			points[i].x += 0.0001;
		glutPostRedisplay();
	}
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.8, 0.8, 0.8, 1.0);

	glColor3f(red, green, blue);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < count; i++) {
		glVertex3f(points[i].x, points[i].y, 0.0);
	}
	glEnd();

	glutSwapBuffers();
}

void detectMouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) exit(0);
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		isAnim = !isAnim;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		points[count].x = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
		points[count].y = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
		count++;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("Simple Interactive application");
	count = 0;
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMouseFunc(detectMouse);
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}
