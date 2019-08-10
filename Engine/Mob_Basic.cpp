#include "Mob_Basic.h"

void Mob::Draw(Graphics& gfx)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= w; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, Colors::Red2);
		}
	}
}

void Mob::Collision(int Gx, int Gy, int Gw, bool &Colliding)
{
	if (Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + w + 1)
	{
		Colliding = true;
	}
}
