#pragma once
#include "Sprite.h"
#include "LaserBeam.h"
#include <vector>

class Tank : public Sprite
{
private:
	LaserBeam shots[3];

public:
	Tank();
	void Draw(MatrixCanvas& canvas);
	void Move(Movement movement);
	void Fire();
	void AddLiveShotsTo(std::vector<LaserBeam*>& activeShots);
	virtual ~Tank();
};

