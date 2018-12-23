#include "Snake.h"
#include <Magick++.h>
#include <random>

using namespace std;

random_device seed;
default_random_engine generator(seed());
uniform_int_distribution<size_t> distribution(0, 6);

const uint8_t BOTTOM_MIDDLE = 7;
const uint8_t CENTER_MIDDLE = 4;
const uint8_t TOP_MIDDLE = 1;
const uint8_t TOP_LEFT = 0;
const uint8_t TOP_RIGHT = 2;

const Magick::Quantum TONGUE_RED = ScaleToQuantum(200);
bool Snake::Tongue::Draw(MatrixCanvas& canvas, Movement movement, Point upperLeft)
{
	movement = movement == Movement::None ? Movement::Up : movement;
	Magick::Image image("3x3", "black");
	auto pixels = image.getPixels(0, 0, 3, 3);
	auto pt = upperLeft.Move(movement);
	
	pixels[BOTTOM_MIDDLE].red = TONGUE_RED;
	if (step >= 1 && step <= 8)
		pixels[CENTER_MIDDLE].red = TONGUE_RED;

	if (step == 2 || step == 7)
		pixels[TOP_MIDDLE].red = TONGUE_RED;

	if (step == 3)
		pixels[TOP_LEFT].red = TONGUE_RED;

	if (step == 4 || step == 6)
		pixels[TOP_MIDDLE].red = TONGUE_RED;

	if (step == 5)
		pixels[TOP_RIGHT].red = TONGUE_RED;

	switch (movement)
	{
	case Movement::Down: image.rotate(180); break;
	case Movement::Left: image.rotate(-90);  break;
	case Movement::Right: image.rotate(90);  break;
	}
	image.syncPixels();
	pixels = image.getPixels(0, 0, 3, 3);

	auto index = 0;
	for (auto row = 0; row < 3; row++)
	{
		Point current = pt.Y + row;
		for (auto col = 0; col < 3; col++)
		{
			Color color(ScaleQuantumToChar(pixels[index++].red), 0, 0);
			current.X = pt.X + col;
			canvas.Draw(current, color);
		}
	}
	return ++step == 10;
}

Color Snake::bodyColor(0, 100, 0);
Color Snake::eyeColor(255, 255, 0);

Snake::Snake(SnakeGameField& field) : field(&field), tongue(nullptr)
{
	head = tail = new SnakeSegment();
	head->UpperLeft = this->field->GetRandomOpenPoint();
}

void Snake::ForAllSegments(std::function<void(SnakeSegment*)> callback)
{
	auto current = head;
	while (current)
	{
		auto next = current->Next;
		callback(current);
		current = next;
	}
}

void Snake::ForEachSegmentUntilFalse(std::function<bool(SnakeSegment*)> callback)
{
	auto current = head;
	while (current)
	{
		auto next = current->Next;
		if (!callback(current))
			break;

		current = next;
	}
}

void Snake::Eat(FoodPellet& foodPellet)
{
	auto segment = new SnakeSegment();
	segment->Next = head;
	head->Previous = segment;
	segment->UpperLeft = foodPellet.GetUpperLeftPoint();

	head = segment;
}

bool Snake::MoveTo(Movement movement, Point& pt)
{
	if (movement == Movement::None)
		return true;

	if (tail != head)
	{
		auto working = tail;
		tail = tail->Previous;
		tail->Next = nullptr;
		field->ReturnPointToPlay(working->UpperLeft);
		delete working;

		working = new SnakeSegment();
		working->UpperLeft = pt;
		working->Next = head;
		head->Previous = working;

		head = working;
	}
	else
	{
		field->ReturnPointToPlay(head->UpperLeft);
		head->UpperLeft = pt;
	}

	if (!field->RemovePointFromPlay(pt))
		return false;

	return true;
}

void Snake::Draw(MatrixCanvas& canvas, Movement movement)
{
	if (tongue && tongue->Draw(canvas, movement, head->UpperLeft))
	{
		delete tongue;
		tongue = nullptr;
	}

	auto eyesOpen = distribution(generator) != 5;

	ForAllSegments([&](SnakeSegment* segment)
	{
		Color colors[9] = { bodyColor, bodyColor, bodyColor, bodyColor, bodyColor, bodyColor, bodyColor, bodyColor, bodyColor };
		if (segment == head && eyesOpen)
		{
			if (movement == Movement::None || movement == Movement::Up || movement == Movement::Left)
				colors[0] = eyeColor;

			if (movement == Movement::None || movement == Movement::Up || movement == Movement::Right)
				colors[2] = eyeColor;

			if (movement == Movement::Right || movement == Movement::Down)
				colors[8] = eyeColor;

			if (movement == Movement::Down || movement == Movement::Left)
				colors[6] = eyeColor;
		}

		auto index = 0;
		auto pt = segment->UpperLeft;
		for (auto row = 0; row < 3; row++)
		{
			Point current = pt.Y + row;
			for (auto col = 0; col < 3; col++)
			{
				current.X = pt.X + col;
				canvas.Draw(current, colors[index++]);
			}
		}
	});
}

Snake::~Snake()
{
	ForAllSegments([&](SnakeSegment* current)
	{
		delete current;
	});

	if (tongue)
	{
		delete tongue;
		tongue = nullptr;
	}
}
