//////////////////
// v. 0.0.0.1b
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
	// Запоминаем диапазон размеров поддерживаемых точек
	GLfloat sizes[2];
	// Запоминаем поддерживаемый инкремент размеров точек
	GLfloat step;
	// Записываем размер текущих точек
	GLfloat curSize;

	// Окно очищается текущим цветом очистки
	glClear(GL_COLOR_BUFFER_BIT);
	// Записываем состояние матрицы и выполняем поворот
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	// Получаем диапазон размеров поддерживаемых точек и размер шага
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	// Задаем исходный размер точки
	curSize = sizes[0];
	// Задаем начальную координату z
	z = -50.0f;
	// Циклический проход по окружности три раза
	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
	{
		// Расчет значений x и y точек окружности
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		// Задаем размер точки перед указанием примитива
		glPointSize(curSize);
		// Рисуем точку
		glBegin(GL_POINTS);
		glVertex3f(x, y, z);
		glEnd();
		// Увеличиваем значение z и размер точки
		z += 0.5f;
		curSize += step;
	}
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
///////////////////////////////////////////////////////
// Вызывается библиотекой GLUT в холостом состоянии (окно не
// меняет размера и не перемещается)


/*

void TimerFunction(int value)
{
	// Меняет направление на противоположное при подходе к левому 
	// или правому краю
	if (x1 > windowWidth - rsize || x1 < -windowWidth)
		xstep = -xstep;
	// Меняет направление на противоположное при подходе к верхнему
	// или нижнему краю
	if (y1 > windowHeight || y1 < -windowHeight + rsize)
		ystep = -ystep;
	// Перемещает квадрат
	x1 += xstep;
	y1 += ystep;
	// Проверка границ. Если окно меньше прямоугольника,
	// который прыгает внутри, и прямоугольник обнаруживает
	// себя вне нового объема отсечения
	if (x1 >(windowWidth - rsize + xstep))
		x1 = windowWidth - rsize - 1;
	else if (x1 < -(windowWidth + xstep))
		x1 = -windowWidth - 1;
	if (y1 >(windowHeight + ystep))
		y1 = windowHeight - 1;
	else if (y1 < -(windowHeight - rsize + ystep))
		y1 = -windowHeight + rsize - 1;
	// Перерисовывает сцену с новыми координатами
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

*/



//////////////////////////////////////////////////////
// Вызывается библиотекой GLUT при изменении размеров окна
void ChangeSize(GLsizei w, GLsizei h)
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
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	// Обновляется стек матриц проекции модели
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Точка входа основной программы
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