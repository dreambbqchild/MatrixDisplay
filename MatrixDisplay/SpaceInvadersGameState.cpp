#include "SpaceInvadersGameState.h"

using namespace std;

SpaceInvadersGameState::SpaceInvadersGameState() : animationSteps(24), animationStepCounter(24), currentMovement(Movement::None), currentButtonMask(Button::None), renderingCanvas(), canvas(24, this), tank()
{
	string invaderImages[ALIEN_ROWS] = { "invader0", "invader0", "invader1", "invader1", "invader2" };
	Color invaderColors[ALIEN_ROWS] = { Color(0, 255, 0), Color(0, 0, 255), Color(204, 51, 255), Color(255, 255, 0), Color(255, 165, 0) };
	for (auto row = 0; row < ALIEN_ROWS; row++)
	{
		for (auto col = 0; col < ALIEN_COLUMNS; col++)
			invadingForce[row][col] = new Alien(invaderImages[row], row, col, invaderColors[row]);
	}

	for (auto index = 0; index < 4; index++)
		bunkers[index] = new Bunker(index);
}

void SpaceInvadersGameState::Play()
{
	auto controller = renderingCanvas.GetCanvasController();
	controller->RegisterMovementChangedCallback([&](Movement movement)
	{
		if (movement == Movement::Left || movement == Movement::Right || movement == Movement::None)
			currentMovement = movement;
	});
	controller->RegisterButtonsChangedCallback([&](Button button) { /*currentButtonMask = button;*/ });

	renderingCanvas.AddPanelsTo(canvas);

	canvas.BeginRenderLoop(&renderingCanvas);
	controller->Control();
	canvas.EndRenderLoop();
}

void SpaceInvadersGameState::BeginDraw()
{
	//take care of any firing.
	if ((currentButtonMask & Button::A) != Button::None)
	{
		tank.Fire();
		currentButtonMask = (currentButtonMask & ~Button::A);
	}

	auto animate = --animationStepCounter == 0;
	if (animate)
		animationStepCounter = animationSteps;

	for (auto row = 0; row < ALIEN_ROWS; row++)
	{
		for (auto col = 0; col < ALIEN_COLUMNS; col++)
		{
			if (invadingForce[row][col] != nullptr) 
			{
				if (animate)
					invadingForce[row][col]->NextAnimationFrame();

				invadingForce[row][col]->Draw(canvas);
			}
		}
	}

	for (auto index = 0; index < 4; index++)
		bunkers[index]->Draw(canvas);

	tank.Move(currentMovement);
	tank.Draw(canvas);
}

SpaceInvadersGameState::~SpaceInvadersGameState()
{
	for (auto row = 0; row < ALIEN_ROWS; row++)
	{
		for (auto col = 0; col < ALIEN_COLUMNS; col++)
		{
			if (invadingForce[row][col])
			{
				delete invadingForce[row][col];
				invadingForce[row][col] = nullptr;
			}
		}
	}

	for (auto index = 0; index < 4; index++)
	{
		delete bunkers[index];
		bunkers[index] = nullptr;
	}
}