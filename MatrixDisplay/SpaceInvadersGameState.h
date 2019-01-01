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
	MatrixRenderingCanvas renderingCanvas;
	//ConsoleRenderingCanvas renderingCanvas;
	MatrixCanvas canvas;

	Alien* invadingForce[ALIEN_ROWS][ALIEN_COLUMNS];
	Bunker* bunkers[4];
	Tank tank;

public:
	SpaceInvadersGameState();
	void BeginDraw();
	void Play();
	virtual ~SpaceInvadersGameState();
};

