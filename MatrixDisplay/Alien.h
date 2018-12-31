#pragma once
#include "DrawingStructs.h"
#include "Sprite.h"

class Alien : public AnimatedSprite<2>
{
private:
	Color alienColor;

public:
	Alien(std::string fileName, Point upperLeft, Color alienColor);
	Color TransformColor(Color color);
	virtual ~Alien();
};

