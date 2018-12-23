#pragma once
#include <stdint.h>

#ifndef MOVEMENT_AMOUNT
#define MOVEMENT_AMOUNT 3
#endif // !MOVEMENT_AMOUNT

enum class Movement { None = 0, Up = (1 << 0), Down = (1 << 1), Left = (1 << 2), Right = (1 << 3)};
Movement operator |(Movement left, Movement right);
Movement operator &(Movement left, Movement right);
Movement operator ~(Movement m);

enum class Button { None = 0, Start = (1 << 0), A = (1 << 1), B = (1 << 2) };
Button operator |(Button left, Button right);
Button operator &(Button left, Button right);
Button operator ~(Button m);

struct Point
{
	int16_t X, Y;
	Point() : X(0), Y(0) {}
	Point(const uint32_t& value) : X(value >> 16), Y(value & 0xFFFF) {}
	Point(int16_t X, int16_t Y) : X(X), Y(Y) {}

	Point Move(Movement movement)
	{
		Point result = *this;
		switch (movement)
		{
		case Movement::Up: result.Y -= MOVEMENT_AMOUNT; break;
		case Movement::Down: result.Y += MOVEMENT_AMOUNT; break;
		case Movement::Left: result.X -= MOVEMENT_AMOUNT; break;
		case Movement::Right: result.X += MOVEMENT_AMOUNT; break;
		}
		return result;
	}

	operator uint32_t() const { return (X << 16) + Y; }
	bool operator ==(const Point& right) { return X == right.X && Y == right.Y; }
};

struct Color
{
	uint8_t R, G, B;
	Color() : R(0), G(0), B(0) {}
	Color(uint8_t R, uint8_t G, uint8_t B) : R(R), G(G), B(B) {}
};