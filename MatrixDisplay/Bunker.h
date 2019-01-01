#pragma once
#include "Sprite.h"
#include <vector>

class Bunker : public Sprite
{
protected:
	bool CountPixelHit(Point pxPoint);

public:
	Bunker(int index);
	virtual ~Bunker();
};

