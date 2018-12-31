#include "Alien.h"

Alien::Alien(std::string fileName, Point upperLeft, Color alienColor) 
	: AnimatedSprite<2>(Rect(upperLeft, Size(7, 8))), alienColor(alienColor)
{
	SetFrame(0, fileName + "_0");
	SetFrame(1, fileName + "_1");
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
