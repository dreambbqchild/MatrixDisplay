#pragma once
#include "Interfaces.h"
#include <unordered_set>

class SnakeGameField
{
private:
	std::unordered_set<uint32_t> positions;

public:
	SnakeGameField(IRenderingCanvas* renderingCanvas);

	Point GetRandomOpenPoint();
	bool RemovePointFromPlay(Point& pt);
	void ReturnPointToPlay(Point& pt);

	virtual ~SnakeGameField();
};