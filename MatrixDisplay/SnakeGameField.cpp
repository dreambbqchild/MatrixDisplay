#include "SnakeGameField.h"
#include <random>

using namespace std;

SnakeGameField::SnakeGameField(IRenderingCanvas* renderingCanvas)
{
	auto verticalPixels = 32 * renderingCanvas->PanelCount();
	for (auto row = 0; row + SNAKE_MOVEMENT < verticalPixels; row += SNAKE_MOVEMENT)
		for (auto col = 0; col + SNAKE_MOVEMENT < 64; col += SNAKE_MOVEMENT)
			positions.insert(Point(col, row));
}

Point SnakeGameField::GetRandomOpenPoint()
{
	random_device seed;
	default_random_engine generator(seed());
	uniform_int_distribution<size_t> distribution(0, positions.size());
	auto index = distribution(generator);

	auto itr = positions.begin();
	for (size_t i = 0; i < index; i++)
		itr++;

	Point pt = *itr;
	positions.erase(*itr);
	return pt;
}

bool SnakeGameField::RemovePointFromPlay(Point& pt)
{
	if (positions.find(pt) == positions.end())
		return false;

	positions.erase(pt);
	return true;
}

void SnakeGameField::ReturnPointToPlay(Point& pt)
{
	positions.insert(pt);
}

SnakeGameField::~SnakeGameField()
{
}
