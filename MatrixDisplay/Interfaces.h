#pragma once
#include "DrawingStructs.h"
#include <functional>

class IController
{
public:
	virtual void RegisterMovementChangedCallback(std::function<void(Movement movement)> callback) = 0;
	virtual void RegisterButtonsChangedCallback(std::function<void(Button button)> callback) = 0;
	virtual void Control() = 0;
};

class IRenderingCanvas
{
public:
	virtual IController* GetCanvasController() = 0;
	virtual uint8_t MaxPanels() = 0;
	//Add the panel registry fns.
	virtual void Clear() = 0;
	virtual void Draw(Point& pt, Color& color) = 0;
	virtual void DrawText(Point& pt, Color& color, const char* text) = 0;
	virtual void Refresh() = 0;
};

class IRootRenderable 
{
public:
	virtual void BeginDraw() = 0;
};

class IGameState : public IRootRenderable
{
public:
	virtual void Play() = 0;
};