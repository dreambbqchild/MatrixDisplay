#pragma once
#include "ConsoleRenderingCanvas.h"
#include "Snake.h"

class SnakeGameState : public IGameState
{
private:
	const char* gameOverText;
	bool isGameRunning;
	Movement currentMovement;
	Button currentButtonMask;

	ConsoleRenderingCanvas renderingCanvas;
	MatrixCanvas canvas;
	SnakeGameField field;
	Snake snake;
	FoodPellet currentPellet;

public:
	SnakeGameState();
	void Play();
	void BeginDraw();
	virtual ~SnakeGameState();
};

