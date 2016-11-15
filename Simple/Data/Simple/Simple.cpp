//////////////////
// v. 0.0.0.1b
// code by rm -rf
//////////////////

#include "../../Common/OpenGLSB.h"

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// Исходное положение и размер прямоугольника
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;
// Величина шага прямоугольника по осям в пикселях
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// Отслеживание изменений ширины и высоты окна
GLfloat windowWidth;
GLfloat windowHeight;

////////////////////////////////////////////////////////
// Вызывается процедура рисования сцены
void RenderScene(void)
{
	// Окно очищается текущим цветом очистки
	glClear(GL_COLOR_BUFFER_BIT);
	// В качестве текущего цвета рисования задается красный
	glColor3f(1.0f, 0.0f, 0.0f);
	// Рисует прямоугольник, закрашенный текущим цветом
	glRectf(x1, y1, x1+rsize, y1-rsize);
	// Очищает очередь текущих команд и переключает буферы
	glutSwapBuffers();
}

///////////////////////////////////////////////////////
// Вызывается библиотекой GLUT в холостом состоянии (окно не
// меняет размера и не перемещается)
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
	if (x1 > (windowWidth - rsize + xstep))
		x1 = windowWidth - rsize - 1;
	else if (x1 < -(windowWidth + xstep))
		x1 = -windowWidth-1;
	if (y1 > (windowHeight + ystep))
		y1 = windowHeight - 1;
	else if (y1 < -(windowHeight - rsize + ystep))
		y1 = -windowHeight + rsize -1;
	// Перерисовывает сцену с новыми координатами
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

///////////////////////////////////////////////////////
// Устанавливается состояние визуализации
void SetupRC(void)
{
	// Устанавливаем в качестве цвета очистки синий
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

//////////////////////////////////////////////////////
// Вызывается библиотекой GLUT при изменении размеров окна
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
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

// Точка входа основной программы
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