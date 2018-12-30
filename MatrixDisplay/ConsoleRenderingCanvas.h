#pragma once
#include "Interfaces.h"
//#include "KeyboardController.h"
#include "ArcadeController.h"

class ConsoleRenderingCanvas : public IRenderingCanvas
{
private:
	//KeyboardController* controller;
	ArcadeController controller;

public:
	static Point DefaultTransformer(Point& pt);

	ConsoleRenderingCanvas();
	uint8_t PanelCount() { return 1; }
	void AddPanelsTo(MatrixCanvas& canvas);
	IController* GetCanvasController() { return &controller; }
	void Clear();
	void Draw(Point& pt, Color& color);
	void DrawText(Point& pt, Color& color, const char* text);
	void Refresh();
	~ConsoleRenderingCanvas();
};

