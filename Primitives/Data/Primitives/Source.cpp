//////////////////
// v. 0.0.0.1b
// code by rm -rf
//////////////////

#include "../../Common/OpenGLSB.h"
#include <math.h>

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// ������������ ��������� �� ��������� pi
#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

////////////////////////////////////////////////////////
// ���������� ��������� ��������� �����
void RenderScene(void)
{
	// ����� �������� ���������� � ����
	GLfloat x, y, z, angle;
	// ���������� �������� �������� �������������� �����
	GLfloat sizes[2];
	// ���������� �������������� ��������� �������� �����
	GLfloat step;
	// ���������� ������ ������� �����
	GLfloat curSize;

	// ���� ��������� ������� ������ �������
	glClear(GL_COLOR_BUFFER_BIT);
	// ���������� ��������� ������� � ��������� �������
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	// �������� �������� �������� �������������� ����� � ������ ����
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	// ������ �������� ������ �����
	curSize = sizes[0];
	// ������ ��������� ���������� z
	z = -50.0f;
	// ����������� ������ �� ���������� ��� ����
	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
	{
		// ������ �������� x � y ����� ����������
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		// ������ ������ ����� ����� ��������� ���������
		glPointSize(curSize);
		// ������ �����
		glBegin(GL_POINTS);
		glVertex3f(x, y, z);
		glEnd();
		// ����������� �������� z � ������ �����
		z += 0.5f;
		curSize += step;
	}
	// ��������������� ��������������
	glPopMatrix();
	// ������� ���� ������ ��������� � ������� �����
	glutSwapBuffers();
}

///////////////////////////////////////////////////////
// ��������������� ��������� ������������
void SetupRC()
{
	// ������������� � �������� ����� ������� ������
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// ���� ��������� ���������� �������
	glColor3f(0.0f, 1.0f, 0.0f);
}

///////////////////////////////////////////////////////////
// ���������� "�������"
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}
///////////////////////////////////////////////////////
// ���������� ����������� GLUT � �������� ��������� (���� ��
// ������ ������� � �� ������������)


/*

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
	if (x1 >(windowWidth - rsize + xstep))
		x1 = windowWidth - rsize - 1;
	else if (x1 < -(windowWidth + xstep))
		x1 = -windowWidth - 1;
	if (y1 >(windowHeight + ystep))
		y1 = windowHeight - 1;
	else if (y1 < -(windowHeight - rsize + ystep))
		y1 = -windowHeight + rsize - 1;
	// �������������� ����� � ������ ������������
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

*/



//////////////////////////////////////////////////////
// ���������� ����������� GLUT ��� ��������� �������� ����
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;
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
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	// ����������� ���� ������ �������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// ����� ����� �������� ���������
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("GAME v.0.0.0.1d");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}