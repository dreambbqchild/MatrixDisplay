#include "Alien.h"

#define LEFT_FOR_64_COL_MATRIX_WITH_6_ALIENS 5

Alien::Alien(std::string fileName, int rowFromTop, int colFromLeft, Color alienColor) 
	: AnimatedSprite<2>(Rect(Point(LEFT_FOR_64_COL_MATRIX_WITH_6_ALIENS + colFromLeft * 9, (4 - rowFromTop) * 10), Size(7, 8))), alienColor(alienColor)
{
	SetFrame(0, fileName + "_0.png");
	SetFrame(1, fileName + "_1.png");
}

Color Alien::TransformColor(Color color)
{
	if (color.R != 0)
		return alienColor;

	return color;
}

Alien::~Alien()
{
}
