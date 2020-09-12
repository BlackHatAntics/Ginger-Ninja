#include "Mob_Jumper.h"

void Jumper::Draw(Graphics& gfx)
{
	//body
	for (int loopx = 0; loopx <= w - 2; loopx++)
	{
		for (int loopy = 0; loopy <= w - 2; loopy++)
		{
			gfx.PutPixel(x + 1 + loopx, y + 1 + loopy, Colors::Green2);
		}
	}
	//perimeter top
	for (int loopx = 0; loopx <= w; loopx++)
	{
		gfx.PutPixel(x + loopx, y, Colors::Green3);
	}
	//perimeter bottom
	for (int loopx = 0; loopx <= w; loopx++)
	{
		gfx.PutPixel(x + loopx, y + w, Colors::Green3);
	}
	//perimeter left
	for (int loopy = 0; loopy <= w; loopy++)
	{
		gfx.PutPixel(x, y + loopy, Colors::Green3);
	}
	//perimeter right
	for (int loopy = 0; loopy <= w; loopy++)
	{
		gfx.PutPixel(x + w, y + loopy, Colors::Green3);
	}
}

void Jumper::Init(int in_x, int in_y)
{
	x = in_x;
	y = in_y;
}

void Jumper::StartPoint()
{
	StartPointX = x;
	StartPointY = y;
}
