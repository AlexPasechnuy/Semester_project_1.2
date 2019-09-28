#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <fstream>
#include "glut.h"
#include "Game.h"
#include "utils.h"
#include "Board.h"

using namespace GraphUtils;

namespace Tag
{

	Game::Game(float xSide, float zSide)
	{
		this->xSide = xSide;
		this->zSide = zSide;
		//доска
		shapes.push_back(new Board(0.0, 0.0, 0.0, N*xSide, 0.1, M * zSide, diffGray, ambiGray, specGray));
		shapes.push_back(new Board(xSide*1.5 + 0.1, 0.05, 0.0, 0.2, 0.2, M * zSide, diffGray, ambiGray, specGray)); 
		shapes.push_back(new Board(-(xSide*1.5 + 0.1), 0.05, 0.0, 0.2, 0.2, M * zSide, diffGray, ambiGray, specGray));
		shapes.push_back(new Board(0.0, 0.05, zSide*1.5 + 0.1, N * xSide + 0.4, 0.2, 0.2, diffGray, ambiGray, specGray));
		shapes.push_back(new Board(0.0, 0.05, -(zSide*1.5 + 0.1), N * xSide + 0.4, 0.2, 0.2, diffGray, ambiGray, specGray));
		//пятна
		shapes.push_back(new Board(allocX(1), 0.051, allocZ(0), xSide / 2, 0.0, zSide / 2, diffWhite, ambiWhite, specWhite));
		shapes.push_back(new Board(allocX(2), 0.051, allocZ(0), xSide / 2, 0.0, zSide / 2, diffBlue, ambiBlue, specBlue));
		shapes.push_back(new Board(allocX(0), 0.051, allocZ(1), xSide / 2, 0.0, zSide / 2, diffLightBlue, ambiLightBlue, specLightBlue));
		shapes.push_back(new Board(allocX(1), 0.051, allocZ(1), xSide / 2, 0.0, zSide  /2, diffRed, ambiRed, specRed));
		shapes.push_back(new Board(allocX(2), 0.051, allocZ(1), xSide / 2, 0.0, zSide / 2, diffYellow, ambiYellow, specYellow));
		shapes.push_back(new Board(allocX(0), 0.051, allocZ(2), xSide / 2, 0.0, zSide / 2, diffGreen, ambiGreen, specGreen));
		shapes.push_back(new Board(allocX(1), 0.051, allocZ(2), xSide / 2, 0.0, zSide / 2, diffOrange, ambiOrange, specOrange));
		shapes.push_back(new Board(allocX(2), 0.051, allocZ(2), xSide / 2, 0.0, zSide / 2, diffViolet, ambiViolet, specViolet));
		//for (int i = 0; i < M; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//	{
		//		shapes.push_back(tiles[i*M + j] = new Tile(allocX(i), 0.1, allocZ(j), xSide, 0.1, zSide, diffWhite, ambiWhite, specWhite, i*M + j + 1));
		//	}
		//}
		//плитки
		shapes.push_back(tiles[0] = new Tile(allocX(0), 0.1, allocZ(0), xSide, 0.1, zSide, diffWhite, ambiWhite, specWhite, 1));
		shapes.push_back(tiles[1] = new Tile(allocX(0), 0.1, allocZ(1), xSide, 0.1, zSide, diffBlue, ambiBlue, specBlue, 2));
		shapes.push_back(tiles[2] = new Tile(allocX(0), 0.1, allocZ(2), xSide, 0.1, zSide, diffLightBlue, ambiLightBlue, specLightBlue, 3));
		shapes.push_back(tiles[3] = new Tile(allocX(1), 0.1, allocZ(0), xSide, 0.1, zSide, diffRed, ambiRed, specRed, 4));
		shapes.push_back(tiles[4] = new Tile(allocX(1), 0.1, allocZ(1), xSide, 0.1, zSide, diffYellow, ambiYellow, specYellow, 5));
		shapes.push_back(tiles[5] = new Tile(allocX(1), 0.1, allocZ(2), xSide, 0.1, zSide, diffGreen, ambiGreen, specGreen, 6));
		shapes.push_back(tiles[6] = new Tile(allocX(2), 0.1, allocZ(0), xSide, 0.1, zSide, diffOrange, ambiOrange, specOrange, 7));
		shapes.push_back(tiles[7] = new Tile(allocX(2), 0.1, allocZ(1), xSide, 0.1, zSide, diffViolet, ambiViolet, specViolet , 8));
		initialize();
	}

	Game::~Game()
	{
		for (int i = 0; i < shapes.size(); i++)
		{
			delete shapes[i];
		}
	}

	void Game::on_paint(void)
	{
		char text[128]; // Масив символів
		char text1[128];
		char text2[128];
		char text3[128];
	// Заповнення масиву символів відповідно до стану гри:
		if (finish)
		{
			sprintf(text, "Game over.   Time: %d sec.	 %d turns.   F2 - Restart game    Esc - Exit", time, turns);
			sprintf(text1, "Time record: %d.		Turns record: %d", fileTime, fileTurns);
			sprintf(text2, "Best time!");
			sprintf(text3, "Best turns!");
		}
		else
		{
			sprintf(text, "F2 - Restart game   Esc - Exit     Time: %d sec.    %d turns.", time, turns);
		}
		// Встановлюємо область перегляду таку, щоб вона вміщувала все вікно:
		glViewport(0, 0, width, height);

		// Ініціалізуємо параметри матеріалів і джерела світла:
		float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // колір фонового освітлення 
		float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // колір дифузного освітлення 
		float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// колір дзеркального відображення
		float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };// розташування джерела світла

		// Встановлюємо параметри джерела світла:
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		// Визначаємо блакитний колір для очищення:
		if (finish)
		{
			glClearColor(0, 0.7, 0.7, 0);
		}
		else
		{
			glClearColor(0, 0.5, 0.5, 0);
		}

		// Очищуємо буфери:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Для відображення тексту, краще використовувати ортографічну проекцію:
		glOrtho(0, 1, 0, 1, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1, 1, 0); // жовтий текст
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
		if (finish)
		{
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, text1, 0.01, 0.9);
			if (time < fileTime)
				drawString(GLUT_BITMAP_TIMES_ROMAN_24, text2, 0.01, 0.85);
			if (turns < fileTurns)
				drawString(GLUT_BITMAP_TIMES_ROMAN_24, text3, 0.21, 0.85);
			fileWrite();
		}
		glPopMatrix();

		// Включаємо режим роботи з матрицею проекцій:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Задаємо усічений конус видимості в лівосторонній системі координат, 
		// 60 - кут видимості в градусах по осі у,
		// width/height - кут видимості уздовж осі x,
		// 1 и 100 - відстань від спостерігача до площин відсікання по глибині:
		gluPerspective(60, width / height, 1, 100);

		// Включаємо режим роботи з видовою матрицею:
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0, distZ);	// камера з початку координат зсувається на distZ, 

		glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // потім повертається по осі Oy
		glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // потім повертається по осі Ox
		glEnable(GL_DEPTH_TEST);	// включаємо буфер глибини (для відсікання невидимих частин зображення)

		// Включаємо режим для установки освітлення:
		glEnable(GL_LIGHTING);

		// Додаємо джерело світла № 0 (їх може бути до 8), зараз воно світить з "очей":
		glEnable(GL_LIGHT0);

		// Малюємо усі фігури:
		for (int i = 0; i < shapes.size(); i++)
		{
			shapes[i]->draw();
		}

		// Вимикаємо все, що включили:
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glFlush();
		// показуємо вікно:
		glutSwapBuffers(); // перемикання буферів
	}

	void Game::on_size(int width, int height)
	{
		this->width = width;
		if (height == 0)
			height = 1;
		this->height = height;
	}

	void Game::on_mouse(int button, int state, int x, int y)
	{
		// Зберігаємо поточні координати миші:
		mouseX = x;
		mouseY = y;
		if ((state == GLUT_UP)) // кнопка віджата
		{
			finish = isFinish();
			this->button = -1;  // ніяка кнопка не натиснута
			return;
		}
		this->button = button;  // зберігаємо інформацію про кнопки
		if (finish)
		{
			return;
		}
	}

	void Game::on_motion(int x, int y)
	{
		switch (button)
		{
		case 0: // ліва кнопка - пересування диску
			if (finish)
				break;
			if (findNearest(x, y, xTo, zTo))
			{
				moveTiles(xFrom, zFrom, xTo, zTo);
				xFrom = xTo;
				zFrom = zTo;
			}
			break;
		case 2: // права кнопка - обертання сцени
			angleX += x - mouseX;
			angleY += y - mouseY;
			mouseX = x;
			mouseY = y;
			break;
		}
	}

	void Game::on_special(int key, int x, int y)
	{

		switch (key) {
		case GLUT_KEY_UP:   // наближення
			if (distZ > -1.7)
			{
				break;
			}
			distZ += 0.1;
			break;
		case GLUT_KEY_DOWN: // віддалення
			distZ -= 0.1;
			break;
		case GLUT_KEY_F2:   // нова гра
			initialize();
			break;
		}
	}

	int tick = 0;

	void Game::on_timer(int value)
	{
		tick++;
		if (tick >= 40) // нарахували наступну секунду
		{
			if (!finish)// секунди нарощуються, якщо гру не закінчено
			{
				time++;
			}
			tick = 0;   // скинули лічильник
		}
		on_paint();     // здійснюємо перемалювання вікна
	}

	void Game::initialize()
	{
		fileRead();
		resetArr();      // початкове заповнення масиву fields
		// "Тасування" масиву. Оскільки двовимірний масив у C++ зберігається як 
		// одновимірний, здійснюємо його приведення до типу одновимірного масиву:
		GraphUtils::shuffle((int *)fields, M * N);

		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (fields[i][j] == 0)
				{
					zEmpty = i;
					xEmpty = j;
				}
			}

		allocateTiles(); // розташування дисків відповідно до масиву fields
		// Ініціалізація елементів даних:
		distZ = -2;
		angleX = -10;
		angleY = 30;
		time = 0;
		turns = 0;
		finish = false;
	}

	void Game::allocateTiles()
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (fields[i][j] > 0)
				{
					tiles[fields[i][j] - 1]->setCoords(allocX(j), 0.1, allocZ(i));
				}
			}
		}
	}

	bool Game::moveTiles(int xFrom, int zFrom, int xTo, int zTo)
	{
		// Перевірка можливості переміщення:
		if (fields[zFrom][xFrom] == 0)
			return false;
		if (fields[zTo][xTo] != 0)
			return false;
		if (abs(xFrom - xTo) + abs(zFrom - zTo) > 1)
			return false;

		// Переміщення:
		tiles[fields[zFrom][xFrom] - 1]->setXCenter(allocX(xTo));
		tiles[fields[zFrom][xFrom] - 1]->setZCenter(allocZ(zTo));

		// Внесення змін в дані масиву fields:
		fields[zTo][xTo] = fields[zFrom][xFrom];
		fields[zFrom][xFrom] = 0;
		zEmpty = zFrom;
		xEmpty = xFrom;
		turns++;
		return true;
	}

	bool Game::findNearest(int x, int y, int& x1, int& z1)
	{
		int viewport[4];
		int iMin = -1, jMin = -1;
		double mvMatrix[16], projMatrix[16];
		double minDist = 2000;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{

				// Світові x, y, z поточного стрижня:
				double wx = allocX(j);
				double wy = 0.1;
				double wz = allocZ(i);

				// Заповнюємо масив viewport поточною областю перегляду:
				glGetIntegerv(GL_VIEWPORT, viewport);

				// Заповнюємо масиви поточними матрицями:
				glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
				glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

				// Світові x, y, z координати, що повертаються:
				double dx, dy, dz;

				// Отримуємо координати точки, на яку спроектовано поточний стрижень:
				gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
				dy = viewport[3] - dy - 1; // dy необхідно перерахувати
				double d = (x - dx) * (x - dx) + (y - dy) * (y - dy); // квадрат відстані
				if (d < minDist) // знайшли ближчий стрижень
				{
					minDist = d;
					iMin = i;
					jMin = j;
				}
			}
		}
		if (minDist < 1000) // знайшли найближчий стрижень
		{
			x1 = jMin;
			z1 = iMin;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Game::resetArr()
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				fields[i][j] = i * 3 + j;
			}
		}
	}

	// Перерахування індексу масиву fields в координату x
	float Game::allocX(int i)
	{
		return  xSide * i - (N - 1) * xSide / 2;
	}

	// Перерахування індексу масиву fields в координату z
	float Game::allocZ(int i)
	{
		return  zSide * i - (M - 1) * zSide / 2;
	}

	void Game::fileRead()
	{
		std::ifstream fin;
		fin.open("highscore.txt");
		fin >> fileTime >> fileTurns;
		fin.close();
	}

	 void Game::fileWrite()
	{
		std::ofstream fout;
		fout.open("highscore.txt", std::ios_base::trunc);
		if (time > fileTime)
			fout << fileTime << ' ';
		else
			fout << time << ' ';

		if (turns > fileTurns)
			fout << fileTurns;
		else
			fout << turns;
		fout.close();
	}

	 bool Game::isFinish()
	 {
		 int check = 0;
		 for (int i = 0; i < M; i++)
		 {
			 for (int j = 0; j < N; j++)
			 {
				 if (fields[i][j] != (M * i + j))
				 {
					 return false;
				 }
			 }
		 }
			 return true;
	 }
}