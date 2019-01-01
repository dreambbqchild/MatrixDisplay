#pragma once
#include "Sprite.h"
#include "LaserBeam.h"

class Tank : public Sprite
{
private:
	LaserBeam shots[3];

public:
	Tank();
	void Draw(MatrixCanvas& canvas);
	void Move(Movement movement);
	bool Fire();
	virtual ~Tank();
};

