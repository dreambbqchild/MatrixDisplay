#pragma once
#include "MatrixCanvas.h"
#include "SnakeGameField.h"
#include "FoodPellet.h"
#include <functional>

class Snake
{
private:
	class Tongue
	{
	private:
		uint8_t step;

	public:
		Tongue() : step(0) {}
		bool Draw(MatrixCanvas& canvas, Movement movement, Point upperLeft);
	};

	class SnakeSegment
	{
	public:
		SnakeSegment* Previous;
		SnakeSegment* Next;
		Point UpperLeft;

		SnakeSegment() : Previous(nullptr), Next(nullptr), UpperLeft() {}
	};

	static Color bodyColor;
	static Color eyeColor;
	SnakeGameField* field;
	SnakeSegment* head;
	SnakeSegment* tail;
	Tongue* tongue;

	void ForAllSegments(std::function<void(SnakeSegment*)> callback);
	void ForEachSegmentUntilFalse(std::function<bool(SnakeSegment*)> callback);
	bool PointForMovement(Movement movement, Point& pt);

public:
	Snake(SnakeGameField& field);

	void Eat(FoodPellet& foodPellet);
	bool MoveTo(Movement movement, Point& pt);
	void Draw(MatrixCanvas& canvas, Movement movement);
	void FlickTongue() { if(!tongue) tongue = new Tongue(); }

	Point HeadPoint() { return head->UpperLeft; }

	virtual ~Snake();
};

