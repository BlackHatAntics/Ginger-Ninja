#include "Ginger.h"

void Ginger::Draw(Graphics& gfx, Color h, Color b)
{
	//hair
	for (int loopx = 0; loopx <= 20; loopx++)
	{
		for (int loopy = 0; loopy <= 6; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, h);
		}
	}
	//body
	for (int loopx = 0; loopx <= 20; loopx++)
	{
		for (int loopy = 0; loopy <= 14; loopy++)
		{
			gfx.PutPixel(x + loopx, y + (6 + 1) + loopy, b);
		}
	}

	//Eye
	for (int loopx = 0; loopx <= 4; loopx++)
	{
		for (int loopy = 0; loopy <= 4; loopy++)
		{
			gfx.PutPixel(x + 1 + loopx, y + (6 + 2) + loopy, Colors::Blue2);
		}
	}
}

void Ginger::EyeLogic()
{

}

void Ginger::Movement()
{
	if (MoveRight)
	{
		x++;
	}
	if (MoveLeft)
	{
		x--;
	}
}

void Ginger::SetMoveRight(bool z)
{
	MoveRight = z;
}
void Ginger::SetMoveLeft(bool z)
{
	MoveLeft = z;
}


