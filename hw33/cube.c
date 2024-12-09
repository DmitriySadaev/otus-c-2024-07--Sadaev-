/**
 * \file cube.c
 * \brief Домашнее задание Куб
 * \author Садаев  
 *
 * Программа отображает вращающийся куб, при нажатии на кнопку ESC происходит выход
 *
 * Для компиляции в Linux набрать в коммандной строке gcc cube.c  -lGL -lGLU -lglut -Wall -Wextra -Wpedantic -std=c11
 *
 */

#include <stdio.h>
#include <GL/glut.h>

#define ESC_KEY									27
#define ROTATION_TIMER_SET_MS 					40
#define CUBE_SIZE 								0.3
#define CUBE_COLOUR_WHITE 						1.0,1.0,1.0 
#define CUBE_COLOUR_BLUE 						0.0,0.0,1.0 
#define CUBE_COLOUR_VIOLET 						1.0,0.0,1.0 
#define CUBE_COLOUR_GREEN 						0.0,1.0,0.0 
#define CUBE_COLOUR_RED 						1.0,0.0,0.0 
#define CUBE_COLOUR_YELLOW 						1.0,1.0,0.0 
#define MAX_ANGLE_GRAD 							359
#define BACKGROUND_COLOUR 						0.89,0.99,0.99,0
#define VIEWING_TRANSFORMATION 					3,3,7,0,0,0,0,1,0
#define ORTHOGHRAPHIC_MATRIX_TRANSFORMATION 	-1,1,-1,1,0,10
#define WINDOW_NAME								"Графические интерфейсы ДЗ"

int window_width = 640; 
int window_height = 640;
int alpha_grad = 0;

/**
 * \fn void process_esc_key(unsigned char key, int x, int y)
 * \brief Функция обработки нажатия кнопки ESC
 *
 * \param key код нажатой клавиши
 * \param x положение указателя мыши по оси Х
 * \param y положение указателя мыши по оси Y
 */
void process_esc_key(unsigned char key, int x, int y) 
{
	if ((key == ESC_KEY) && (x != 0) && (y != 0)) //без обработки x и y компилятор ругается.
	{
		exit(0);
	}	
}

/**
 * \fn void reshape(int width, int height) 
 * \brief Функция обработки изменения пользователем размера окна
 *
 * \param width ширина окна просмотра
 * \param height высота окна просмотра
 */
void reshape(int width, int height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(ORTHOGHRAPHIC_MATRIX_TRANSFORMATION);
	window_width = width;
	window_height = height;
}

/**
 * \fn void process_alpha(void)
 * \brief Функция инкремента угла поворота
 *
 */
void process_alpha(void)
{
	alpha_grad++;
	if (alpha_grad > MAX_ANGLE_GRAD) 
	{
		alpha_grad = 0;
	}
}

/**
 * \fn void cube_draw_back(void)
 * \brief Функция рисования задней стороны куба
 *
 */
void cube_draw_back(void)
{
	glBegin(GL_POLYGON);
	glColor3f(CUBE_COLOUR_WHITE);
	glVertex3f(  CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE );
	glVertex3f(  CUBE_SIZE,  CUBE_SIZE, CUBE_SIZE );
	glVertex3f( -CUBE_SIZE,  CUBE_SIZE, CUBE_SIZE );
	glVertex3f( -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE );
	glEnd();
}

/**
 * \fn void cube_draw_bottom(void)
 * \brief Функция рисования нижней стороны куба
 *
 */
void cube_draw_bottom(void)
{
	glBegin(GL_POLYGON);
	glColor3f(CUBE_COLOUR_RED);
	glVertex3f(  CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE );
	glVertex3f(  CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE );
	glVertex3f( -CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE );
	glVertex3f( -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE );
	glEnd();	
}

/**
 * \fn void cube_draw_right(void)
 * \brief Функция рисования правой стороны куба
 *
 */
void cube_draw_right(void)
{
	glBegin(GL_POLYGON);
	glColor3f(CUBE_COLOUR_VIOLET);
	glVertex3f( CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE );
	glVertex3f( CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE );
	glVertex3f( CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE );
	glVertex3f( CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE );
	glEnd();	
}

/**
 * \fn void cube_draw_left(void)
 * \brief Функция рисования левой стороны куба
 *
 */
void cube_draw_left(void)
{
	glBegin(GL_POLYGON);
	glColor3f(CUBE_COLOUR_GREEN);
	glVertex3f( -CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE );
	glVertex3f( -CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE );
	glVertex3f( -CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE );
	glVertex3f( -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE );
	glEnd();	
}

/**
 * \fn void cube_draw_front(void)
 * \brief Функция рисования передней стороны куба
 *
 */
void cube_draw_front(void)
{
	glBegin(GL_POLYGON);
	glColor3f(CUBE_COLOUR_YELLOW);   
	glVertex3f(  CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE );      
	glVertex3f(  CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE );      
	glVertex3f( -CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE );      
	glVertex3f( -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE ); 
	glEnd();	
}

/**
 * \fn void cube_draw_top(void)
 * \brief Функция рисования верхней стороны куба
 *
 */
void cube_draw_top(void)
{
	glBegin(GL_POLYGON);
	glColor3f(CUBE_COLOUR_BLUE);
	glVertex3f(  CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE );
	glVertex3f(  CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE );
	glVertex3f( -CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE );
	glVertex3f( -CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE );
	glEnd();
}

/**
 * \fn void draw_cube(void) 
 * \brief Функция рисования куба
 *
 * Проблематика в том, что в зависимости от угла поворота грани начинают накладываться друг на друга, 
 * приходится перерисовывать их в разном порядке в зависимости от угла поворота куба.
 */
void draw_cube(void) 
{
	if ((alpha_grad >= 120) && (alpha_grad < 240))
	{
		cube_draw_back();	
		cube_draw_bottom();
		cube_draw_right();
		cube_draw_left();
		cube_draw_front();	
		cube_draw_top();
	}
	if ((alpha_grad >= 240) && (alpha_grad < 300))
	{
		cube_draw_left();
		cube_draw_bottom();
		cube_draw_back();
		cube_draw_front();
		cube_draw_right();
		cube_draw_top();
	}
		if ((alpha_grad >= 300) && (alpha_grad < 360))
	{
		cube_draw_left();
		cube_draw_bottom();
		cube_draw_front();	
		cube_draw_back();
		cube_draw_right();		
		cube_draw_top();
	}
	if ((alpha_grad >= 0) && (alpha_grad < 60))
	{
		cube_draw_bottom();
		cube_draw_front();
		cube_draw_left();
		cube_draw_right();
		cube_draw_back();	
		cube_draw_top();
	}
		if ((alpha_grad >= 60) && (alpha_grad < 120))
	{
		cube_draw_bottom();			
		cube_draw_right();	
		cube_draw_front();
		cube_draw_back();
		cube_draw_left();	
		cube_draw_top();
	}
}

/**
 * \fn void draw_scene(void) 
 * \brief Функция отрисовки сцены
 *
 */
void draw_scene(void) 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(VIEWING_TRANSFORMATION);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(alpha_grad, 0.0f, 0.1f, 0.0f);
	process_alpha();
	draw_cube();
		
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

/**
 * \fn void set_timer(int timer_id) 
 * \brief Функция установки таймера
 *
 * \param timer_id идентификатор запущенного таймера
 */
void set_timer(int timer_id) 
{
  glutPostRedisplay();  
  glutTimerFunc(ROTATION_TIMER_SET_MS, set_timer, timer_id);
}

/**
 * \fn int main(int argc, char *argv[]) 
 * \brief Основная функция - точка входа в программу
 *
 * \param argc счетчик числа аргументов командной строки
 * \param argv указатель на массив одно- или многобайтовых строк
 */
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(window_width, window_height);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow(WINDOW_NAME);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glutReshapeFunc(reshape); 
  glutDisplayFunc(draw_scene);
  glutTimerFunc(ROTATION_TIMER_SET_MS, set_timer, 0);
  glClearColor(BACKGROUND_COLOUR);

  glutKeyboardFunc(process_esc_key);

  glutMainLoop();

  return 0;
}
