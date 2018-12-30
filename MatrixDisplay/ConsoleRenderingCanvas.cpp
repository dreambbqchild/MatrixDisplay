#include "ConsoleRenderingCanvas.h"
#include "MatrixCanvas.h"
#include "MatrixPanel.h"
#include <sstream>
#include <iostream>
#include <string.h>

using namespace std;

struct Cell 
{
	bool IsUpdated;
	bool WasVisited;
	char Char;
	Color color;
};

Cell matrix[32][64] = { 0 };

Point ConsoleRenderingCanvas::DefaultTransformer(Point& pt) { return pt; }

ConsoleRenderingCanvas::ConsoleRenderingCanvas() : controller()
{
	cout << "\033[2J";
	cout.flush();

	for (auto row = 0; row < 32; row++)
		cout << "\033[" << (row + 1) << ";64H\033[38;2;255;255;0m|\033[0m";

	cout << "\033[32;0H\033[38;2;255;255;0m----------------------------------------------------------------\033[0m";
}

void ConsoleRenderingCanvas::AddPanelsTo(MatrixCanvas& canvas)
{
	canvas.AddPanel(new MatrixPanel(this, ConsoleRenderingCanvas::DefaultTransformer));
}

void ConsoleRenderingCanvas::Clear()
{
	for (auto row = 0; row < 32; row++)
	for (auto col = 0; col < 64; col++)
	{
		matrix[row][col].WasVisited = false;
		matrix[row][col].IsUpdated = false;
	}
}

void ConsoleRenderingCanvas::Draw(Point& pt, Color& color)
{
	auto currentColor = matrix[pt.Y][pt.X].color;
	matrix[pt.Y][pt.X].IsUpdated = currentColor.R != color.R || currentColor.G != color.G || currentColor.B != color.B;
	matrix[pt.Y][pt.X].WasVisited = true;
	matrix[pt.Y][pt.X].color = color;
	matrix[pt.Y][pt.X].Char = '*';
}

void ConsoleRenderingCanvas::DrawText(Point& pt, Color& color, const char* text)
{
	auto length = strlen(text);
	for (auto i = 0; i < length; i++)
	{
		auto x = pt.X + i;
		auto currentColor = matrix[pt.Y][x].color;
		matrix[pt.Y][x].IsUpdated = currentColor.R != color.R || currentColor.G != color.G || currentColor.B != color.B;
		matrix[pt.Y][x].WasVisited = true;
		matrix[pt.Y][x].color = color;
		matrix[pt.Y][x].Char = text[i];
	}
}

void ConsoleRenderingCanvas::Refresh()
{
	for (auto row = 0; row < 32; row++)
	for (auto col = 0; col < 64; col++)
	{
		auto px = matrix[row][col].color;
		if(matrix[row][col].IsUpdated)
			cout << "\033[" << (row + 1) << ";" << (col + 1) << "H\033[38;2;" << (int16_t)px.R << ";" << (int16_t)px.G << ";" << (int16_t)px.B << "m" << matrix[row][col].Char << "\033[0m";

		if (!matrix[row][col].WasVisited && (px.R != 0 || px.G != 0 || px.B != 0))
		{
			cout << "\033[" << (row + 1) << ";" << (col + 1) << "H\033[38;2;0;0;0m \033[0m";
			matrix[row][col].color = Color();
		}
	}

	cout.flush();
}

ConsoleRenderingCanvas::~ConsoleRenderingCanvas()
{
	Clear();
}
