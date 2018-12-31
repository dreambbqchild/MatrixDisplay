#include "SnakeGameState.h"
//#include "ConsoleRenderingCanvas.h"
#include "MatrixRenderingCanvas.h"
#include "MatrixCanvas.h"

const char* noob = "Next Out of Bounds";
const char* soob = "Snake Out of Bounds";

SnakeGameState::SnakeGameState() 
	: currentMovement(Movement::None), currentButtonMask(Button::None), snake(field), currentPellet(field), field(&renderingCanvas), renderingCanvas(), isGameRunning(true), canvas(3, this), gameOverText("")
{

}

void SnakeGameState::Play()
{
	auto controller = renderingCanvas.GetCanvasController();
	controller->RegisterMovementChangedCallback([&](Movement movement)
	{
		if(movement == Movement::Up || movement == Movement::Down || movement == Movement::Left || movement == Movement::Right)
			currentMovement = movement; 
	});
	controller->RegisterButtonsChangedCallback([&](Button button) { currentButtonMask = button; });

	renderingCanvas.AddPanelsTo(canvas);

	canvas.BeginRenderLoop(&renderingCanvas);
	controller->Control();
	canvas.EndRenderLoop();
}

void SnakeGameState::BeginDraw()
{
	if (!isGameRunning)
	{
		Point pt;
		Color red(255, 0, 0);
		canvas.DrawText(pt, red, gameOverText);
		return;
	}

	auto drawMovement = currentMovement;
	auto buttonState = currentButtonMask;
	currentButtonMask = Button::None;

	auto nextPoint = snake.HeadPoint().Move(drawMovement, SNAKE_MOVEMENT);
	if (nextPoint.X < 0 || nextPoint.Y < 0 || nextPoint.X >= 64 || nextPoint.Y >= 32 * renderingCanvas.PanelCount())
	{
		gameOverText = noob;
		isGameRunning = false;
		return;
	}

	if ((buttonState & Button::A) == Button::A)
		snake.FlickTongue();

	if (currentPellet.GetUpperLeftPoint() == nextPoint)
	{
		snake.Eat(currentPellet);
		currentPellet = FoodPellet(field);
	}
	else if (!snake.MoveTo(drawMovement, nextPoint))
	{
		gameOverText = soob;
		isGameRunning = false;
		return;
	}

	currentPellet.Draw(canvas);
	snake.Draw(canvas, drawMovement);
}

SnakeGameState::~SnakeGameState()
{
}
