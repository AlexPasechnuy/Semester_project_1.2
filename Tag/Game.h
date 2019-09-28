#ifndef Scene_h
#define Scene_h 

#include<vector>

#include "Shape.h"
#include "Tile.h"

namespace Tag
{
	const int M = 3, N = 3;

	class Game
	{
		std::vector<Shape*> shapes;
		int button;
		float angleX, angleY;
		float mouseX, mouseY;
		float width, height;
		float distZ;
		float xSide, zSide;
		bool finish;
		Tile *tiles[M*N - 1];
		int time, turns;
		int fileTime, fileTurns;
		int fields[M][N];
		int xFrom, zFrom;
		int xTo, zTo;
		int xEmpty, zEmpty;
	public:
		Game(float xSide, float zSide);
		~Game();
		void on_paint();
		void on_size(int width, int height);
		void on_mouse(int button, int state, int x, int y);
		void on_motion(int x, int y);
		void on_special(int key, int x, int y);
		void on_timer(int value);
	private:
		void initialize();
		void allocateTiles();
		bool moveTiles(int xFrom, int zFrom, int xTo, int zTo);
		bool findNearest(int x, int z, int& x1, int& z1);
		void resetArr();
		float allocX(int i);
		float allocZ(int i);
		void fileRead();
		void fileWrite();
		bool isFinish();
	};

}

#endif