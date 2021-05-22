/*
   INTERACTIVE DRAWING
*/

#include "cg.h"
#include "draw.h"

int w = 600;
int h = 600;

struct polytype {
	vector2D a, b;
	int pmode;// 1: line, 2: triangle, 3:circle, 4:rectangle
	vector3D color;
	bool on = false;
	bool isPeople = false;
};

polytype polygon[100];
int index = 0, selectedIndex;
bool isLeftButton = false, isSelected = false, isFirst = true, wasScaling = false, isMiddleButton=false;
int mode = 1;
vector3D color = vector3D(0.9, 0.9, 0.8);

void deletePolygon(bool deleteAll) {
	if (deleteAll) {
		index = 0;
		printf("current number of polygons : %d\n", index);
		glClear(GL_COLOR_BUFFER_BIT);
		glutPostRedisplay();
	}
	else if (isSelected) {
		polygon[selectedIndex].on = false; isSelected = false;
		if (index > 0) {
			if (selectedIndex == index) {
				index--;
				if (index == 0) isFirst = true;
			}
			else {
				for (int i = selectedIndex; i < index; i++) {
					polygon[i] = polygon[i + 1];
				}
				index--;
				if (index == 0) isFirst = true;
			}
			printf("current number of polygons : %d\n", index);
			glClear(GL_COLOR_BUFFER_BIT);
			glutPostRedisplay();
		}
	}
}

void showIndex(polytype polygon[]) {
	for (int i = index; i >= 0; i--) {
		printf("polygon #%d; ax: %f, ay: %f, bx: %f, by: %f; ", i, polygon[i].a.x, polygon[i].a.y, polygon[i].b.x, polygon[i].b.y);
		printf(polygon[i].on ? "true\n" : "false\n");
	}
}

void showStatus() {
	printf(isLeftButton ? "isLeftButton : true\n" : "isLeftButton : false\n");
	printf(isSelected ? "isSelected : true\n" : "isSelected : false\n");
	printf(isFirst ? " isFirst : true\n" : "isFirst : false\n");
	printf(wasScaling ? "wasScaling : true\n" : "wasScaling : false\n");
	printf(isMiddleButton ? "isMiddleButton : true\n" : "isMiddleButton : false\n");

}

void mydisplay()
{
	vector2D a, b;
	vector3D color = vector3D(0.9, 0.0, 0.9);
	int mode = 1;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 1; i <= index; i++) {
		if (polygon[i].on == true) {

			a = polygon[i].a;
			b = polygon[i].b;
			color = polygon[i].color;
			mode = polygon[i].pmode;

			glColor3f(color.x, color.y, color.z);
			if (mode == 1) line(a, b);
			else if (mode == 2) triangle(vector2D(a.x, b.y), vector2D((b.x + a.x) / 2, a.y), b);
			else if (mode == 3)	ellipse(vector2D((b.x + a.x) / 2, (b.y + a.y) / 2), b.x - a.x, a.y - b.y);
			else if (mode == 4) rect(a, b);
			else if (mode == 5) circle(vector2D((b.x + a.x) / 2, (b.y + a.y) / 2), abs((b.x - a.x) / 2));
			else if (mode == 6) cross(a, b);
			else if (mode == 7) ridge(vector2D((b.x + a.x) / 2, (b.y + a.y) / 2), b.x - a.x, a.y - b.y);
			else if (mode == 8) trapzoid(a, b);
			else if (mode == 9) arrow(a, b);
			else if (mode == 10) people(a, b);
		}
		if (polygon[i].isPeople) {
			for (int i = 0; i < index; i++) {
				if (polygon[i].isPeople == true) {
					printf("polygon #%d is people", i);
					for (float f = 0.0; f < 1.5; f += 0.0001) {
						polygon[i].a.x += f;
						polygon[i].b.x += f;
					}
				}
			}
		}
		glutPostRedisplay();
	}
	glutSwapBuffers();
}

void mymouse(int button, int state, int x, int y)
{
	float px, py;
	px = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	py = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		isLeftButton = true; isMiddleButton = false; isSelected = false;
		printf("left button clicked; px : %f, py : %f\n", px, py);
		if (polygon[index].on == true || isFirst) {
			index++;
			polygon[index].a = vector2D(px, py);
			polygon[index].color = color;
			polygon[index].pmode = mode;
			isFirst = false;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		isLeftButton = false; isMiddleButton = false;
		printf("right button clicked; px : %f, py : %f\n", px, py);
		for (int i = index; i > 0; i--) {
			if ((px >= polygon[i].a.x && px <= polygon[i].b.x) && (py >= polygon[i].b.y && py <= polygon[i].a.y)) {
				isSelected = true;
				selectedIndex = i;
				break;
			}
			else {
				printf("No polygon on clicked area");
				isSelected = false;
				selectedIndex = 0;
				printf(isSelected ? " true\n" : " false\n");
			}
		}
		printf("selected polygon index : %d", selectedIndex);
		printf(isSelected ? " true\n" : " false\n");
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		isLeftButton = false; isMiddleButton = true;
	}
}

void mymousemotion(int x, int y)
{
	float px, py;
	px = (float)x / (float)w * 2.0 - 1.0;
	py = -(float)y / (float)h * 2.0 + 1.0;
	float polyWidth = abs(polygon[selectedIndex].b.x - polygon[selectedIndex].a.x);
	float polyHeight = abs(polygon[selectedIndex].a.y - polygon[selectedIndex].b.y);
	float ratio = polyWidth / polyHeight;
	if (isLeftButton && !isSelected && !isMiddleButton) {
		printf("this polygon is ");
		printf(polygon[index].on ? "shown\n" : "not shown\n");
		polygon[index].b = vector2D(px, py);
		polygon[index].on = true;
		wasScaling = false;
		glutPostRedisplay();
	}
	else if (!isLeftButton && isSelected && !isMiddleButton) {
		if ((polygon[selectedIndex].a.x <= px && px <= polygon[selectedIndex].b.x) &&
			(polygon[selectedIndex].b.y <= py && py <= polygon[selectedIndex].a.y))
		{
			polygon[selectedIndex].a.x += 0.01;
			polygon[selectedIndex].a.y -= 0.01;
			polygon[selectedIndex].b.x -= 0.01;
			polygon[selectedIndex].b.y += 0.01;
			glutPostRedisplay();
		}
		else if ((polygon[selectedIndex].a.x > px || px > polygon[selectedIndex].b.x) ||
			(polygon[selectedIndex].b.y > py || py > polygon[selectedIndex].a.y))
		{
			polygon[selectedIndex].a.x -= 0.01;
			polygon[selectedIndex].a.y += 0.01;
			polygon[selectedIndex].b.x += 0.01;
			polygon[selectedIndex].b.y -= 0.01;
			glutPostRedisplay();
		}
		wasScaling = true;
	}
	else if (isMiddleButton && isSelected) {
		polygon[selectedIndex].a.x = px - polyWidth / 2;
		polygon[selectedIndex].a.y = py + polyHeight / 2;
		polygon[selectedIndex].b.x = px + polyWidth / 2;
		polygon[selectedIndex].b.y = py - polyHeight / 2;
		glutPostRedisplay();
	}
}

void mykey(unsigned char key, int x, int y)
{
	printf("%d\n", key);
	if ((key == 'Q') | (key == 'q')) exit(0);
	else if (key == '1') mode = 1; // line
	else if (key == '2') mode = 2;
	else if (key == '3') mode = 3;
	else if (key == '4') mode = 4;
	else if (key == '5') mode = 5;
	else if (key == '6') mode = 6;
	else if (key == '7') mode = 7;
	else if (key == '8') mode = 8;
	else if (key == '9') mode = 9;
	else if (key == 127) deletePolygon(false);
	else if (key == 27) deletePolygon(true);
	else if (key == 91) glClearColor(0.0, 0.0, 0.0, 0.0);
	else if (key == 93) glClearColor(1.0, 1.0, 1.0, 0.0);
	else if (key == 47) polygon[selectedIndex].isPeople = true;
	else if (key == 'i') mode = 10;
	else if (key == 'l') system("cls");
	else if (key == 'h') showIndex(polygon);
	else if (key == 'z') showStatus();
	else if (key == 'r') {
		if (isSelected) {
			polygon[selectedIndex].color = vector3D(1.0, 0.0, 0.0);
		}
		else color = vector3D(1.0, 0.0, 0.0);
	}
	else if (key == 'y') {
		if (isSelected) {
			polygon[selectedIndex].color = vector3D(1.0, 1.0, 0.0);
		}
		else color = vector3D(1.0, 1.0, 0.0);
	}
	else if (key == 'g') {
		if (isSelected) {
			polygon[selectedIndex].color = vector3D(0.0, 1.0, 0.0);
		}
		else color = vector3D(0.0, 1.0, 0.0);
	}
	else if (key == 'b') {
		if (isSelected) {
			polygon[selectedIndex].color = vector3D(0.0, 0.0, 1.0);
		}
		else color = vector3D(0.0, 0.0, 1.0);
	}
	else if (key == 'c') {
		if (isSelected) {
			polygon[selectedIndex].color = vector3D(0.0, 0.7, 0.7);
		}
		else color = vector3D(0.0, 0.7, 0.7);
	}
	else if (key == 'm') {
		if (isSelected) {
			polygon[selectedIndex].color = vector3D(0.7, 0.0, 0.7);
		}
		else color = vector3D(0.7, 0.0, 0.7);
	}
	else if (key == 'w') {
		if (isSelected) {
			polygon[selectedIndex].color = vector3D(1.0, 1.0, 1.0);
		}
		else color = vector3D(1.0, 1.0, 1.0);
	}
	else if (key == 'k') {
		if (isSelected) {
			polygon[selectedIndex].color = vector3D(0.0, 0.0, 0.0);
		}
		else color = vector3D(0.0, 0.0, 0.0);
	}
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
	glutKeyboardFunc(mykey);
	glutMouseFunc(mymouse);
	glutMotionFunc(mymousemotion);

	glutIdleFunc(mydisplay);

	glutMainLoop();
}