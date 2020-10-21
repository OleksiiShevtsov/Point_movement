#include <glut.h>
#include <cstdlib>
#include <math.h>

using namespace std;

int L = 1360;
int H = 680;

int a = 20;

double Fx = 50;
double Fy = 50;
double f = 0.1;
double m = 10;
double t = 0;

const double time = 0.2;
const double g = 9.81;

int dir = 0;
bool sensor_1 = true, sensor_2 = true, sensor_3 = true, sensor_4 = true, sensor_0 = true;

double ax = Fx / m;
double ay = Fy / m;
double fg = f * g;

double alternatingPlus(double num) {
	if (num < 0) {
		num = -num;
		return num;
	}
	return num;
}

double alternatingMinus(double num) {
	if (num > 0) {
		num = -num;
		return num;
	}
	return num;
}

class Point {
public:
	const double R = 30;
	double r = R * 0.8;

	double x;
	double y;

	double Vx;
	double Vy;

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void drawPoint() {

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);

		double yc = 0;
		for (double xc = x - R; xc < x + R; xc = xc + 0.01) {
			yc = sqrt(-pow(x - xc, 2) + pow(R, 2)) + y;
			glVertex2f(xc, yc);
		}
		for (double xc = x - R; xc < x + R; xc = xc + 0.01) {
			yc = -sqrt(-pow(x - xc, 2) + pow(R, 2)) + y;
			glVertex2f(xc, yc);
		}
		glEnd();

		glColor3f(0.8, 0.7, 0.1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);

		yc = 0;
		for (double xc = x - r; xc < x + r; xc = xc + 0.01) {
			yc = sqrt(-pow(x - xc, 2) + pow(r, 2)) + y;
			glVertex2f(xc, yc);
		}
		for (double xc = x - r; xc < x + r; xc = xc + 0.01) {
			yc = -sqrt(-pow(x - xc, 2) + pow(r, 2)) + y;
			glVertex2f(xc, yc);
		}
		glEnd();
	}
};

Point point(L / 2, H / 2);
double Ax = ax, Ay = ay, Vx0 = 0, Vy0 = 0, X0 = point.x, Y0 = point.y, FGx, FGy;

void frictionForceX(const Point &point, double &FGx) {
	if (point.Vx < 0) {
		FGx = alternatingPlus(fg);
	}
	else if (point.Vx > 0) {
		FGx = alternatingMinus(fg);
	}
	else {
		FGx = 0;
	}
}
void frictionForceY(const Point &point, double &FGy) {
	if (point.Vy < 0) {
		FGy = alternatingPlus(fg);
	}
	else if (point.Vy > 0) {
		FGy = alternatingMinus(fg);
	}
	else {
		FGy = 0;
	}
}

void sensorTrue() {
	sensor_2 = true;
	sensor_4 = true;
	sensor_0 = true;
	sensor_3 = true;
	sensor_1 = true;
}

void direction() {
	//задание направления ускрения
	switch (dir) {
	case 1:
		if (sensor_1) {
			t = 0;
			X0 = point.x;
			Y0 = point.y;
			Vx0 = point.Vx;
			Vy0 = point.Vy;;

			sensor_2 = true;
			sensor_4 = true;
			sensor_0 = true;
			sensor_3 = true;
			sensor_1 = false;
		}
		t = t + time;

		Ax = alternatingPlus(ax);
		Ay = 0;

		point.Vx = (Ax + FGx) * t + Vx0;
		point.Vy = (Ay + FGy) * t + Vy0;
		frictionForceX(point, FGx);
		frictionForceY(point, FGy);
		break;
	case 2:
		if (sensor_2) {
			t = 0;
			X0 = point.x;
			Y0 = point.y;
			Vx0 = point.Vx;
			Vy0 = point.Vy;

			sensor_1 = true;
			sensor_4 = true;
			sensor_0 = true;
			sensor_3 = true;
			sensor_2 = false;
		}
		t = t + time;

		Ay = alternatingPlus(ay);
		Ax = 0;

		point.Vx = (Ax + FGx) * t + Vx0;
		point.Vy = (Ay + FGy) * t + Vy0;
		frictionForceX(point, FGx);
		frictionForceY(point, FGy);
		break;
	case 4:
		if (sensor_4) {
			t = 0;
			X0 = point.x;
			Y0 = point.y;
			Vx0 = point.Vx;
			Vy0 = point.Vy;

			sensor_1 = true;
			sensor_2 = true;
			sensor_0 = true;
			sensor_3 = true;
			sensor_4 = false;
		}
		t = t + time;

		Ay = alternatingMinus(ay);
		Ax = 0;

		point.Vx = (Ax + FGx) * t + Vx0;
		point.Vy = (Ay + FGy) * t + Vy0;
		frictionForceX(point, FGx);
		frictionForceY(point, FGy);
		break;
	case 3:
		if (sensor_3) {
			t = 0;
			X0 = point.x;
			Y0 = point.y;
			Vx0 = point.Vx;
			Vy0 = point.Vy;

			sensor_4 = true;
			sensor_2 = true;
			sensor_0 = true;
			sensor_3 = false;
			sensor_1 = true;
		}
		t = t + time;

		Ax = alternatingMinus(ax);
		Ay = 0;

		point.Vx = (Ax + FGx) * t + Vx0;
		point.Vy = (Ay + FGy) * t + Vy0;
		frictionForceX(point, FGx);
		frictionForceY(point, FGy);
		break;
	case 0:
		if (t == 0) {
			break;
		}
		if (sensor_0) {
			t = 0;
			X0 = point.x;
			Y0 = point.y;
			Vx0 = point.Vx;
			Vy0 = point.Vy;

			sensor_0 = false;
			sensor_3 = true;
			sensor_1 = true;
			sensor_4 = true;
			sensor_2 = true;
		}
		t = t + time;

		Ax = 0;
		Ay = 0;

		point.Vx = (Ax + FGx) * t + Vx0;
		point.Vy = (Ay + FGy) * t + Vy0;
		frictionForceX(point, FGx);
		frictionForceY(point, FGy);
		break;
	}
}

void Tick() {

	if (point.Vx > 0) {
		if (point.Vx < (-(Ax + FGx) * (time + 0.01)) && dir == 3) {
			sensor_3 = true;
		}
		if (point.Vx < (-FGx * (time + 0.01))) {
			point.Vx = 0;
			sensorTrue();
		}
		else {
			point.x = (((Ax + FGx) * (t * t)) / 2) + Vx0 * t + X0;
		}
	}
	else if (point.Vx < 0) {
		if (point.Vx > (-(Ax + FGx) * (time + 0.01)) && dir == 1) {
			sensor_1 = true;
		}
		if (point.Vx > (-FGx * (time + 0.01))) {
			point.Vx = 0;
			sensorTrue();
		}
		else {
			point.x = (((Ax + FGx) * (t * t)) / 2) + Vx0 * t + X0;
		}
	}

	if (point.Vy > 0) {
		if (point.Vy < (-(Ay + FGy) * (time + 0.01)) && dir == 4) {
			sensor_4 = true;
		}
		if (point.Vy < (-FGy * (time + 0.01))) {
			point.Vy = 0;
			sensorTrue();
		}
		else {
			point.y = (((Ay + FGy) * (t * t)) / 2) + Vy0 * t + Y0;
		}
	}
	else if (point.Vy < 0) {
		if (point.Vy < (-(Ay + FGy) * (time + 0.01)) && dir == 2) {
			sensor_2 = true;
		}
		if (point.Vy > (-FGy * (time + 0.01))) {
			point.Vy = 0;
			sensorTrue();
		}
		else {
			point.y = (((Ay + FGy) * (t * t)) / 2) + Vy0 * t + Y0;
		}
	}

	if (point.x < point.R + a) {
		point.Vx = alternatingPlus(point.Vx);
		sensorTrue();
	}
	if (point.x > L - point.R - a) {
		point.Vx = alternatingMinus(point.Vx);
		sensorTrue();
	}
	if (point.y < point.R + a) {
		point.Vy = alternatingPlus(point.Vy);
		sensorTrue();
	}
	if (point.y > H - point.R - a) {
		point.Vy = alternatingMinus(point.Vy);
		sensorTrue();
	}

	dir = 0;
}

//Движение
void MyKeyboard(unsigned char key, int a, int b) {

	//задание граничных условий
	if (key == 'a') {
		dir = 3;
	}
	if (key == 'd') {
		dir = 1;
	}
	if (key == 'w') {
		dir = 2;
	}
	if (key == 's') {
		dir = 4;
	}
}

void box() {
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	glVertex2f(a, a);
	glVertex2f(a, H - a);
	glVertex2f(0 , H);
	glEnd();

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, H);
	glVertex2f(a, H - a);;
	glVertex2f(L - a, H - a);
	glVertex2f(L, H);
	glEnd();

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(L, H);
	glVertex2f(L - a, H - a);
	glVertex2f(L - a, a);
	glVertex2f(L, 0);
	glEnd();

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(L, 0);
	glVertex2f(0, 0);
	glVertex2f(a, a);
	glVertex2f(L - a, a);
	glEnd();
}

//поле
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	box();
	
	point.drawPoint();

	glFlush();
}

//цыкл программы
void timer(int = 0) {
	display();

	direction();
	Tick();

	glutTimerFunc(50, timer, 0);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(L, H);
	glutCreateWindow("Snake");
	glClearColor(0.1, 0.1, 0.1, 0.0);//закрасить поле
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, L, 0, H);

	//функция цыкл времени
	glutTimerFunc(50, timer, 0);
	//функция воода клавиш(не нужно реализовывать)
	glutKeyboardFunc(MyKeyboard);
	//функция дисплей
	glutDisplayFunc(display);
	glutMainLoop();
}