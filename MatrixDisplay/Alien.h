#pragma once
#include "DrawingStructs.h"
#include "Sprite.h"
#include "LaserBeam.h"

class Alien : public AnimatedSprite<2>
{
private:
	bool isOnFrontLine;
	Color alienColor;
	LaserBeam shot;
	
public:
	Alien(std::string fileName, int rowFromTop, int colFromLeft, Color alienColor);
	Color TransformColor(Color color);
	
	void Draw(MatrixCanvas& canvas);

	void SetIsOnFrontLine() { isOnFrontLine = true; }
	bool GetIsOnFrontLine() { return isOnFrontLine; };
	
	void TryAttack();

	virtual ~Alien();
};

