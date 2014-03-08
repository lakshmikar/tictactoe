#include <windows.h>
#include "glut.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VERTICAL 0
#define HORIZONTAL 1

GLint xStart, yStart;
GLsizei winWidth = 400;
GLsizei winHeight = 400;

boolean matrix[3][3] = {};



int row[3];
int col[3];
int diagonal;
int anti_diagonal;

bool isWinner(int x, int y, int p)
{
	if (p == 1){
		row[x]++;
		col[y]++;
		if (x == y) diagonal++;
		if (x + y == 2) anti_diagonal++;
	}
	else{
		row[x]--;
		col[y]--;
		if (x == y) diagonal--;
		if (x + y == 2) anti_diagonal--;
	}

	
	return (abs(row[x]) == 3 || abs(col[y]) == 3 || abs(diagonal) == 3 || abs(anti_diagonal) == 3);
}
void wait(int limit)
{
	for (int i = 0; i<limit; i++);
	//glutTimerFunc(10000,wait,10);
}

/* Point plotting function */
void setPixel(GLint xCoord, GLint yCoord)
{
	//	printf("Plotting (%d, %d)\n", xCoord, yCoord);
	glBegin(GL_POINTS);
	glVertex2i(xCoord, yCoord);
	wait(100);
	glEnd();
	glFlush();
}

/* Vertical/Horizontal Span function */
void span(int x1, int y1, int width, int direction)
{


	if (direction == HORIZONTAL)
	{

		for (int i = 0; i < width; i++)
		{

			int ywidth1 = y1 + i;
			int ywidth2 = y1 - 1;
			int xwidth = x1;
			setPixel(xwidth, ywidth1);
			setPixel(xwidth, ywidth2);
			xwidth++;
		}

		// Compute positions of spanning pixels
		// Call setPixel for each position

	}
	else
	{
		for (int i = 0; i < width; i++)
		{
			int xwidth1 = x1 + i;
			int xwidth2 = x1 - 1;
			int ywidth = y1;
			setPixel(xwidth1, ywidth);
			setPixel(xwidth2, ywidth);
			ywidth++;
		}
		// Compute positions of spanning pixels
		// Call setPixel for each position
	}
}





void circlePoints(int xCenter, int yCenter, int x, int y, int width)
{

	setPixel(xCenter + x, yCenter + y);
	span(xCenter + x, yCenter + y, width, 1);
	setPixel(xCenter - x, yCenter + y);
	span(xCenter - x, yCenter + y, width, 1);
	setPixel(xCenter + x, yCenter - y);
	span(xCenter + x, yCenter - y, width, 1);
	setPixel(xCenter - x, yCenter - y);
	span(xCenter - x, yCenter - y, width, 1);
	setPixel(xCenter + y, yCenter + x);
	span(xCenter + y, yCenter + x, width, 0);
	setPixel(xCenter - y, yCenter + x);
	span(xCenter - y, yCenter + x, width, 0);
	setPixel(xCenter + y, yCenter - x);
	span(xCenter + y, yCenter - x, width, 0);
	setPixel(xCenter - y, yCenter - x);
	span(xCenter - y, yCenter - x, width, 0);

}
void drawCircle(int xCenter, int yCenter, int r, int width){

	int x = 0;

	int y = r;

	int p = 1 - r;

	circlePoints(xCenter, yCenter, x, y, width);

	while (x < y){

		x++;

		if (p < 0){


			p += 2 * x + 1;

		}
		else{

			y--;

			p += 2 * (x - y) + 1;

		}

		circlePoints(xCenter, yCenter, x, y, width);

	}

}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 300.0, 0.0, 300.0);
	for (int i = 0; i < 3; i++) {
		row[i] = 0;
		col[i] = 0;
	}
	diagonal = 0;
	anti_diagonal = 0;
}


/* Bresenham line-drawing */
void lineBres(int x0, int y0, int xEnd, int yEnd, int width)
{
	int dx, dy, p;
	int twoDyMinusDx, twoDy;
	int x, y;


	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
		yEnd = y0;
	}
	else {
		x = x0;
		y = y0;
	}
	dy = yEnd - y;
	dx = xEnd - x;
	twoDyMinusDx = 2 * (dy - dx);
	p = 2 * dy - dx;

	setPixel(x, y);
	while (x < xEnd) {
		x++;
		if (p < 0) {
			p += 2 * dy;
		}
		else {
			y++;
			p += twoDyMinusDx;
		}
		setPixel(x, y);
		span(x, y, width, 1);
	}
}
/* Bresenham line-drawing */
void lineBres1(int x0, int y0, int xEnd, int yEnd, int width)
{
	int dx, dy, p;
	int twoDyMinusDx;
	int x, y;


	if (y0 > yEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
		yEnd = y0;
	}
	else {
		x = x0;
		y = y0;
	}
	dy = yEnd - y;
	dx = xEnd - x;
	if (dx < 0)
		dx *= -1;
	twoDyMinusDx = 2 * (dx - dy);
	p = 2 * dx - dy;

	setPixel(x, y);
	while (y < yEnd) {
		y++;
		if (p < 0) {
			p += 2 * dx;
		}
		else {
			x--;
			p += 2 * (dx - dy);
		}
		setPixel(x, y);
		span(x, y, width, 0);
	}
}

void displayCall(char c) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	if (c == 'O') {
		drawCircle(150, 210, 30, 5);
		lineBres(65, 0, 85, 65, 10);

		lineBres1(60, 150, 60, 0, 10);
		
		lineBres1(85, 25, 110, 0, 10);
		lineBres1(110, 0, 110, 150, 10);
		lineBres1(130, 0, 130, 150, 10);
		lineBres1(160, 0, 160, 150, 10);
		lineBres1(160, 150, 200, 0, 10);
		lineBres1(200, 0, 200, 150, 10);
	}
	else if (c == 'X') {
		
		lineBres(120, 170, 180, 230, 10);
		lineBres1(180, 170, 120, 230, 10);

		
		lineBres(65, 0, 85, 65, 10);

		lineBres1(60, 150, 60, 0, 10);

		lineBres1(85, 25, 110, 0, 10);
		lineBres1(110, 0, 110, 150, 10);
		lineBres1(130, 0, 130, 150, 10);
		lineBres1(160, 0, 160, 150, 10);
		lineBres1(160, 150, 200, 0, 10);
		lineBres1(200, 0, 200, 150, 10);
	}
	else {
		drawCircle(150, 250, 30, 4);
		glLineWidth(3);

		glBegin(GL_LINE_STRIP);
		glVertex2i(140, 220);
		glVertex2i(160, 220);
		glVertex2i(150, 210);
		glVertex2i(140, 220);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2i(135, 80);
		glVertex2i(150, 60);
		glVertex2i(165, 80);
		glVertex2i(150, 210);
		glVertex2i(135, 80);

		glEnd();
		
		glBegin(GL_LINE_STRIP);
		glVertex2i(145, 207);
		glVertex2i(125, 150);
		glVertex2i(125, 145);
		glVertex2i(130, 145);
		glVertex2i(141, 190);
		glVertex2i(145, 207);

		glEnd();

		glFlush();

	}
}
void mousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if (action == GLUT_DOWN)
	{
		// Insert actions to take on mouse click
		xStart = xMouse;
		yStart = yMouse;
	}
	if (action == GLUT_UP)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			// Insert actions to take on left mouse release
			glColor3f(1.0, 0.0, 0.0);

			for (int x = 0; x <= 200; x += 100)
			{
				for (int y = 0; y <= 200; y += 100)
				{
					if ((xStart >= x) && (xStart <= (x + 100)) &&

						(yStart >= y) && (yStart <= (y + 100)) && matrix[x / 100][y / 100] == false)
						{
							lineBres1(x, 300 - y, x + 100, 200 - y, 5);
							lineBres(x, 200 - y, x + 100, 300 - y, 5);

							matrix[x / 100][y / 100] = true;
							if (isWinner(x / 100, y / 100, 1)) {
								displayCall('X');
							}
							else {
								boolean flag = false;
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < 3; j++) {
										if (!matrix[i][j])
											flag = true;
									}
								}
								if (!flag) {
									displayCall('T');
								}
							}

					}
				}
			}



		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			// Insert actions to take on right mouse release
			glColor3f(0.0, 0.0, 1.0);
			for (int x = 0; x <= 200; x += 100)
			{
				for (int y = 0; y <= 200; y += 100)
				{
					if ((xStart >= x) && (xStart <= (x + 100)) &&

						(yStart >= y) && (yStart <= (y + 100)) && matrix[x / 100][y / 100] == false)
					{

						drawCircle(x + 50, 250 - y, 30, 5);
						matrix[x / 100][y / 100] = true;
						if (isWinner(x / 100, y / 100, 0)) {
							displayCall('O');
						}
						else {
							boolean flag = false;
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 3; j++) {
									if (!matrix[i][j])
										flag = true;
								}
							}
							if (!flag) {
								displayCall('T');
							}
						}
					}
				}
			}
		}
	}

	glFlush();
}

void drawShape(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	//lineBres(50, 50, 250, 250,  5);
	//lineBres1(50, 250, 50, 50, 5);
	lineBres(0, 100, 300, 100, 5);
	lineBres1(100, 0, 100, 300, 5);
	lineBres(0, 200, 300, 200, 5);
	lineBres1(200, 0, 200, 300, 5);
	//drawCircle(50, 150, 30,5);
	//horizontal(75, 175, 350, 175, 10);
	//horizontal(75, 275, 350, 275, 10);

	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(300, 300);
	glutCreateWindow("Bresenhams algorithm");
	init();
	glutDisplayFunc(drawShape);
	glutMouseFunc(mousePlot);
	glutMainLoop();
}
