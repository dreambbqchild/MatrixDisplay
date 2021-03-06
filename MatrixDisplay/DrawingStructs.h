#pragma once
#include <stdint.h>

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
	int X, Y;
	Point() : X(0), Y(0) {}
	Point(const uint32_t& value) : X(value >> 16), Y(value & 0xFFFF) {}
	Point(int x, int y) : X(x), Y(y) {}

	Point Move(Movement movement, int8_t movementAmount = 1)
	{
		Point result = *this;
		switch (movement)
		{
		case Movement::Up: result.Y -= movementAmount; break;
		case Movement::Down: result.Y += movementAmount; break;
		case Movement::Left: result.X -= movementAmount; break;
		case Movement::Right: result.X += movementAmount; break;
		case Movement::None: break;
		}
		return result;
	}

	operator uint32_t() const { return (X << 16) + Y; }
	bool operator ==(const Point& right) { return X == right.X && Y == right.Y; }
};

struct Size
{
	int Width, Height;
	Size() : Width(0), Height(0) {}
	Size(int width, int height) : Width(width), Height(height) {}
};

struct Rect 
{
	::Point Point;
	::Size Size;
	Rect() : Point(), Size() {}
	Rect(::Point point, ::Size size) : Point(point), Size(size) {}
	
	bool IsEmpty() { return Size.Height == 0 && Size.Width == 0; }

	::Point UpperLeft() { return Point; }
	::Point UpperRight() { return ::Point(Point.X + Size.Width, Point.Y); }
	::Point LowerLeft() { return ::Point(Point.X, Point.Y + Size.Height); }
	::Point LowerRight() { return ::Point(Point.X + Size.Width, Point.Y + Size.Height); }

	virtual bool PointIntersects(::Point pt) 
	{
		return pt.X >= Point.X && pt.X < Point.X + Size.Width
			&& pt.Y >= Point.Y && pt.Y < Point.Y + Size.Height; 
	}
};

struct Color
{
	uint8_t R, G, B;
	Color() : R(0), G(0), B(0) {}
	Color(int r, int g, int b) : R(static_cast<uint8_t>(r)), G(static_cast<uint8_t>(g)), B(static_cast<uint8_t>(b)) {}

	bool operator !=(const Color& right) { return R != right.R || G != right.G || B != right.B; }
};