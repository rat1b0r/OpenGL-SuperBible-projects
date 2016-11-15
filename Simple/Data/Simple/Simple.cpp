//////////////////
// v. 0.0.0.1b
// code by rm -rf
//////////////////

#include "../../Common/OpenGLSB.h"

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// �������� ��������� � ������ ��������������
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;
// �������� ���� �������������� �� ���� � ��������
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// ������������ ��������� ������ � ������ ����
GLfloat windowWidth;
GLfloat windowHeight;

////////////////////////////////////////////////////////
// ���������� ��������� ��������� �����
void RenderScene(void)
{
	// ���� ��������� ������� ������ �������
	glClear(GL_COLOR_BUFFER_BIT);
	// � �������� �������� ����� ��������� �������� �������
	glColor3f(1.0f, 0.0f, 0.0f);
	// ������ �������������, ����������� ������� ������
	glRectf(x1, y1, x1+rsize, y1-rsize);
	// ������� ������� ������� ������ � ����������� ������
	glutSwapBuffers();
}

///////////////////////////////////////////////////////
// ���������� ����������� GLUT � �������� ��������� (���� ��
// ������ ������� � �� ������������)
void TimerFunction(int value)
{
	// ������ ����������� �� ��������������� ��� ������� � ������ 
	// ��� ������� ����
	if (x1 > windowWidth - rsize || x1 < -windowWidth)
		xstep = -xstep;
	// ������ ����������� �� ��������������� ��� ������� � ��������
	// ��� ������� ����
	if (y1 > windowHeight || y1 < -windowHeight + rsize)
		ystep = -ystep;
	// ���������� �������
	x1 += xstep;
	y1 += ystep;
	// �������� ������. ���� ���� ������ ��������������,
	// ������� ������� ������, � ������������� ������������
	// ���� ��� ������ ������ ���������
	if (x1 > (windowWidth - rsize + xstep))
		x1 = windowWidth - rsize - 1;
	else if (x1 < -(windowWidth + xstep))
		x1 = -windowWidth-1;
	if (y1 > (windowHeight + ystep))
		y1 = windowHeight - 1;
	else if (y1 < -(windowHeight - rsize + ystep))
		y1 = -windowHeight + rsize -1;
	// �������������� ����� � ������ ������������
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

///////////////////////////////////////////////////////
// ��������������� ��������� ������������
void SetupRC(void)
{
	// ������������� � �������� ����� ������� �����
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

//////////////////////////////////////////////////////
// ���������� ����������� GLUT ��� ��������� �������� ����
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	// ������������� ������� �� ����
	if (h == 0)
		h = 1;
	// ������������� ���� ��������� � ��������� ����
	glViewport(0, 0, w, h);
	// ��������� ������� ��������� (��������� ���� ������� ��������������)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// � ������� ���������� ��������� (�����, ������, ������, �������,
	// �������, �������) ������������� ����� ���������
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
	{
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
		glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
	}
	else
	{
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
		glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// ����� ����� �������� ���������
void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("GAME v.0.0.0.1c ***** Physics test");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}