/*
   INTERACTIVE DRAWING
*/

#include "cg.h"
#include "draw.h"

int w = 800;
int h = 800;

struct polytype {
	vector2D a, b;
	int pmode;// 1: line, 2: triangle, 3:circle, 4:rectangle
	vector3D color;
	bool on = false;
};

polytype polygon[100];
int index = 0, selectedIndex;
// 좌클릭/우클릭 여부, 도형 선택 여부, 첫번째 도형 여부, 드래그 크기조절 여부, 가운데 버튼 클릭 여부
bool isLeftButton = false, isSelected = false, isFirst = true, wasScaling = false, isMiddleButton=false;
int mode = 1;
vector3D color = vector3D(0.9, 0.9, 0.8);

// 도형 삭제 함수
void deletePolygon(bool deleteAll) {
	// 전부 삭제 기능 (ESC)
	if (deleteAll) {
		index = 0;
		glClear(GL_COLOR_BUFFER_BIT);
		glutPostRedisplay();
	}
	//선택한 도형 삭제
	else if (isSelected) {
		//삭제할 시 삭제될 폴리곤의 표시 속성 off, isSelected 신호 off
		polygon[selectedIndex].on = false; isSelected = false;
		// 그려진 도형이 하나 이상일 시
		if (index > 0) {
			//가장 마지막에 그려진 도형이면 인덱스만 하나 줄여서 새 도형이 덮어 쓰여지도록 함
			if (selectedIndex == index) {
				index--;
				if (index == 0) isFirst = true;
			}
			//순서가 중간에 있는 도형이면 가장 마지막에 그려진 도형부터 거슬러 올라가며 찾는다.
			else {
				for (int i = selectedIndex; i < index; i++) {
					polygon[i] = polygon[i + 1];
				}
				index--;
				if (index == 0) isFirst = true;
			}
			glClear(GL_COLOR_BUFFER_BIT);
			glutPostRedisplay();
		}
	}
}
// 그리기 함수
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
			// 삼각형, 타원, 사각형, 원, 십자, 반원, 사다리꼴, 화살표 도형과 사람 그림이 가능
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
	}
	glutSwapBuffers();
}
// 마우스 버튼 함수
void mymouse(int button, int state, int x, int y)
{
	float px, py;
	px = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	py = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));

	// 좌클릭 시
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// 좌클릭만 수행됨을 알 수 있도록 좌클릭 신호를 제외한 신호는 모두 false
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
	// 우클릭 시
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		// 마찬가지로 우클릭을 제외한 모든 신호는 false
		isLeftButton = false; isMiddleButton = false;
		// 가장 마지막 도형부터 a, b 두점으로 형성된 영역에 들어 갔는지 찾아 올라감
		for (int i = index; i > 0; i--) {
			if ((px >= polygon[i].a.x && px <= polygon[i].b.x) && (py >= polygon[i].b.y && py <= polygon[i].a.y)) {
				isSelected = true;
				selectedIndex = i;
				break;
			}
			// 해당하는 도형이 없을 시 선택된 것이 없다는 의미로 false 설정과 선택 인덱스도 0으로 설정
			else {
				isSelected = false;
				selectedIndex = 0;
			}
		}
	}
	// 가운데 버튼을 제외한 모든 버튼 false
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		isLeftButton = false; isMiddleButton = true;
	}
}
// 마우스 동작 함수
void mymousemotion(int x, int y)
{
	float px, py;
	px = (float)x / (float)w * 2.0 - 1.0;
	py = -(float)y / (float)h * 2.0 + 1.0;
	//도형의 폭과 높이 저장
	float polyWidth = abs(polygon[selectedIndex].b.x - polygon[selectedIndex].a.x);
	float polyHeight = abs(polygon[selectedIndex].a.y - polygon[selectedIndex].b.y);
	// 좌클릭만 해당할 시(선택된 것 X)
	if (isLeftButton && !isSelected && !isMiddleButton) {
		polygon[index].b = vector2D(px, py);
		polygon[index].on = true;
		// 크기 조절 중이 아니었음을 명시
		wasScaling = false;
		glutPostRedisplay();
	}
	// 도형이 선택되고 우클릭시
	else if (!isLeftButton && isSelected && !isMiddleButton) {
		// 기존 도형의 안쪽에서 드래그 시 크기 감소
		if ((polygon[selectedIndex].a.x <= px && px <= polygon[selectedIndex].b.x) &&
			(polygon[selectedIndex].b.y <= py && py <= polygon[selectedIndex].a.y))
		{
			polygon[selectedIndex].a.x += 0.01;
			polygon[selectedIndex].a.y -= 0.01;
			polygon[selectedIndex].b.x -= 0.01;
			polygon[selectedIndex].b.y += 0.01;
			glutPostRedisplay();
		}
		// 바깥쪽으로 드래그시 크기 증가
		else if ((polygon[selectedIndex].a.x > px || px > polygon[selectedIndex].b.x) ||
			(polygon[selectedIndex].b.y > py || py > polygon[selectedIndex].a.y))
		{
			polygon[selectedIndex].a.x -= 0.01;
			polygon[selectedIndex].a.y += 0.01;
			polygon[selectedIndex].b.x += 0.01;
			polygon[selectedIndex].b.y -= 0.01;
			glutPostRedisplay();
		}
		// 드래그 했음을 명시
		wasScaling = true;
	}
	// 도형이 선택되었고 가운데 버튼으로 드래그 시 이동
	else if (isMiddleButton && isSelected) {
		polygon[selectedIndex].a.x = px - polyWidth / 2;
		polygon[selectedIndex].a.y = py + polyHeight / 2;
		polygon[selectedIndex].b.x = px + polyWidth / 2;
		polygon[selectedIndex].b.y = py - polyHeight / 2;
		glutPostRedisplay();
	}
}
// 키보드 감지 함수
void mykey(unsigned char key, int x, int y)
{
	// Q는 종료, 0~9 까지
	// 삼각형, 타원, 사각형, 원, 십자, 반원, 사다리꼴, 화살표 도형과 사람 그림
	// ESC / Delete는 각각 전체 삭제, 선택 도형 삭제
	// [ , ] 는 배경 검은색, 흰색으로 변경
	// r, g, b, c, y, m, w(흰색), k(검은색)
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
	else if (key == '0') mode = 10;
	else if (key == 127) deletePolygon(false);
	else if (key == 27) deletePolygon(true);
	else if (key == 91) glClearColor(0.0, 0.0, 0.0, 0.0);
	else if (key == 93) glClearColor(1.0, 1.0, 1.0, 0.0);
	// 도형이 선택 되었다면 그 도형의 색상 변경
	// 아니라면 새로 그릴 도형의 색깔을 지정
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
// 창 크기 조절 함수
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
	glutCreateWindow("Project 2");
	glutReshapeFunc(reshape);
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykey);
	glutMouseFunc(mymouse);
	glutMotionFunc(mymousemotion);
	glutIdleFunc(mydisplay);
	glutMainLoop();
}