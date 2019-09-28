#ifndef Tile_h
#define Tile_h

#include "Shape.h"

namespace Tag
{
	class Tile : public Shape
	{
	private:
		int number;
	public:
		Tile(float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize,
			float *diffColor, float *ambiColor, float *specColor, int number)
			: Shape(xCenter, yCenter, zCenter, xSize, ySize, zSize,
				diffColor, ambiColor, specColor) {	this->number = number;	}
		void setNumber(int number) { this->number = number; }
		int getNumber() const { return number; }
		virtual void draw();
	};
}

#endif

