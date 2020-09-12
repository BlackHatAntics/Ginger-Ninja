#pragma once
#include "Graphics.h"

class Jumper
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_y);
	void StartPoint();

private:
	int StartPointX;
	int StartPointY;
	int x = StartPointX;
	int y = StartPointY;
	int w = 11;
};