#include "glut.h"
#include "Game.h"
#include "utils.h"
#include "Tile.h"

using namespace Tag;
using namespace GraphUtils;

Game *game; // вказівник на клас Scene

void on_paint()
{
	// Викликаємо відповідну функцію класу Scene:
	game->on_paint();
}

void on_size(int width, int height)
{
	// Викликаємо відповідну функцію класу Scene:
	game->on_size(width, height);
}

void on_mouse(int button, int state, int x, int y)
{
	// Викликаємо відповідну функцію класу Scene:
	game->on_mouse(button, state, x, y);
}

void on_motion(int x, int y)
{
	// Викликаємо відповідну функцію класу Scene:
	game->on_motion(x, y);
}

void on_special(int key, int x, int y)
{
	// Викликаємо відповідну функцію класу Scene:
	game->on_special(key, x, y);
}

void on_keyboard(unsigned char key, int x, int y)
{
	// Обробка подій від клавіатури:
	if (key == 27)
		exit(1);
	exit(0);
}

void on_timer(int value)
{
	// Обробка події від таймера
	game->on_timer(value);
	glutTimerFunc(25, on_timer, 0); // зa 25 мс викличеться ця функція
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);         // ініціалізуємо GLUT
	game = new Game(0.4, 0.4);   // створюємо об'єкт "сцена"
	glutInitWindowSize(800, 600);  // встановлюємо розміри вікна
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);// ініціалізуємо режими відображення
	glutCreateWindow("Tags");     // створюємо вікно
	glutDisplayFunc(on_paint);     // реєструємо функцію відображення
	glutReshapeFunc(on_size);      // реєструємо функцію обробки зміни розмірів вікна
	glutMotionFunc(on_motion);     // реєструємо функцію, яка відповідає за переміщення миші з натиснутою кнопкою
	glutMouseFunc(on_mouse);       // реєструємо функцію, яка відповідає за натискання на кнопку миші
	glutKeyboardFunc(on_keyboard); // реєструємо функцію, яка відповідає за натискання клавіш
	glutSpecialFunc(on_special);   // реєструємо функцію, яка відповідає за натискання спеціальних клавіш
	glutTimerFunc(25, on_timer, 0);// кожні 25 мс викликається ця функція
	glutMainLoop();                // стартуємо основний цикл обробки подій
	delete game;                  // видаляємо об'єкт "сцена"
	return(0);
}