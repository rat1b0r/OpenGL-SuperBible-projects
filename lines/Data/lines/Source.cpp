//////////////////
// v. 0.0.0.1e
// code by rm -rf
//////////////////

#include "../../Common/OpenGLSB.h"
#include <math.h>

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// Определяется константа со значением pi
#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

////////////////////////////////////////////////////////
// Вызывается процедура рисования сцены
void RenderScene(void)
{
	// Здесь хранятся координаты и углы
	GLfloat x, y, z, angle;
	// Окно очищается текущим цветом очистки
	glClear(GL_COLOR_BUFFER_BIT);
	// Записываем состояние матрицы и выполняем поворот
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);
	z = 0.0f;
	for (angle = 0.0f; angle <= GL_PI; angle += (GL_PI / 20.0f))
	{
		// Верхняя половина окружности
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		glVertex3f(x, y, z);
		// Нижняя половина окружности
		x = 50.0f*sin(angle + GL_PI);
		y = 50.0f*cos(angle + GL_PI);
		glVertex3f(x, y, z);
	}
	glEnd();
	// Восстанавливаем преобразования
	glPopMatrix();
	// Очищаем стек команд рисования и свапаем буфер
	glutSwapBuffers();
}

///////////////////////////////////////////////////////
// Устанавливается состояние визуализации
void SetupRC()
{
	// Устанавливаем в качестве цвета очистки черный
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Цвет рисования выбирается зеленым
	glColor3f(0.0f, 1.0f, 0.0f);
}

///////////////////////////////////////////////////////////
// Подключаем "стрелки"
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

//////////////////////////////////////////////////////
// Вызывается библиотекой GLUT при изменении размеров окна
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	// Предотвращает деление на ноль
	if (h == 0)
		h = 1;
	// Устанавливает поле просмотра с размерами окна
	glViewport(0, 0, w, h);
	// Обновляет систему координат (обновляет стек матрицы проектирования)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// С помощью плоскостей отсечения (левая, правая, нижняя, верхняя,
	// ближняя, дальняя) устанавливает объем отсечения
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	// Обновляется стек матриц проекции модели
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Точка входа основной программы
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GAME v.0.0.0.1e");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}