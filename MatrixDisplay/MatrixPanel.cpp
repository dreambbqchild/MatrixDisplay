#include "MatrixPanel.h"

void MatrixPanel::Draw(Point& pt, Color& px)
{
	auto transformedPt = transform(pt);
	renderingCanvas->Draw(transformedPt, px);
}

void MatrixPanel::DrawText(Point& pt, Color& px, const char* text)
{
	auto transformedPt = transform(pt);
	renderingCanvas->DrawText(transformedPt, px, text);
}

MatrixPanel::~MatrixPanel()
{
}