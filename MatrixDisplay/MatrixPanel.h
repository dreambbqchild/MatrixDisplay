#pragma once
#include "Interfaces.h"
#include <functional>

class MatrixPanel
{
private:
	std::function<Point(Point& pt)> transform;
	IRenderingCanvas* renderingCanvas;

public:
	MatrixPanel(IRenderingCanvas* renderingCanvas, std::function<Point(Point& pt)> transform) : transform(transform), renderingCanvas(renderingCanvas) {}
	void Draw(Point& pt, Color& color);
	void DrawText(Point& pt, Color& color, const char* text);
	~MatrixPanel();
};

