#include "glut.h"
#include "Game.h"
#include "utils.h"
#include "Tile.h"

using namespace Tag;
using namespace GraphUtils;

Game *game; // �������� �� ���� Scene

void on_paint()
{
	// ��������� �������� ������� ����� Scene:
	game->on_paint();
}

void on_size(int width, int height)
{
	// ��������� �������� ������� ����� Scene:
	game->on_size(width, height);
}

void on_mouse(int button, int state, int x, int y)
{
	// ��������� �������� ������� ����� Scene:
	game->on_mouse(button, state, x, y);
}

void on_motion(int x, int y)
{
	// ��������� �������� ������� ����� Scene:
	game->on_motion(x, y);
}

void on_special(int key, int x, int y)
{
	// ��������� �������� ������� ����� Scene:
	game->on_special(key, x, y);
}

void on_keyboard(unsigned char key, int x, int y)
{
	// ������� ���� �� ���������:
	if (key == 27)
		exit(1);
	exit(0);
}

void on_timer(int value)
{
	// ������� ��䳿 �� �������
	game->on_timer(value);
	glutTimerFunc(25, on_timer, 0); // �a 25 �� ����������� �� �������
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);         // ���������� GLUT
	game = new Game(0.4, 0.4);   // ��������� ��'��� "�����"
	glutInitWindowSize(800, 600);  // ������������ ������ ����
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);// ���������� ������ �����������
	glutCreateWindow("Tags");     // ��������� ����
	glutDisplayFunc(on_paint);     // �������� ������� �����������
	glutReshapeFunc(on_size);      // �������� ������� ������� ���� ������ ����
	glutMotionFunc(on_motion);     // �������� �������, ��� ������� �� ���������� ���� � ���������� �������
	glutMouseFunc(on_mouse);       // �������� �������, ��� ������� �� ���������� �� ������ ����
	glutKeyboardFunc(on_keyboard); // �������� �������, ��� ������� �� ���������� �����
	glutSpecialFunc(on_special);   // �������� �������, ��� ������� �� ���������� ����������� �����
	glutTimerFunc(25, on_timer, 0);// ���� 25 �� ����������� �� �������
	glutMainLoop();                // �������� �������� ���� ������� ����
	delete game;                  // ��������� ��'��� "�����"
	return(0);
}