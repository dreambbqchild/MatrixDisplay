#pragma once
#include "Interfaces.h"
//#include "ConsoleRenderingCanvas.h"
#include "MatrixRenderingCanvas.h"
#include "Alien.h"
#include "Bunker.h"
#include "Tank.h"

#define ALIEN_ROWS 5
#define ALIEN_COLUMNS 6

class SpaceInvadersGameState : public IGameState
{
private:
	int animationSteps, animationStepCounter;
	Movement alienMovement;
	Movement currentMovement;
	Button currentButtonMask;
	MatrixRenderingCanvas renderingCanvas;
	//ConsoleRenderingCanvas renderingCanvas;
	MatrixCanvas canvas;

	Alien* upperLeftAlien, *bottomRightAlien;
	Alien* invadingForce[ALIEN_ROWS][ALIEN_COLUMNS];
	Bunker* bunkers[4];
	Tank tank;

	Alien* FindBoundingAlien(int startingColumn, int offset);
	void DrawAliens(std::vector<LaserBeam*> tankShotsAtOutset, std::vector<LaserBeam*>& activeShots);
	void MoveAliens();

public:
	SpaceInvadersGameState();
	void BeginDraw();
	void Play();
	virtual ~SpaceInvadersGameState();
};

