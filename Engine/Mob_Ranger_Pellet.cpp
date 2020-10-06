#include "Mob_Ranger_Pellet.h"

void Pellet::Draw(Graphics & gfx/*, int Rx, int Ry, int Rw*/)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= w; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, Colors::Brown1);
		}
	}
}

void Pellet::Spawning(int PelletSize, int & i)
{
	if (PelletStage == 10) //short delay before he starts firing
	{
		active = true; //this is saying: okay, now you can load up the pel.Shoot() function, and Pellet[PelletNumber] will be drawn in Game.cpp
	}

	if (PelletStage == 100)
	{
		PelletStage = 0;
		i++;

		if (i == PelletSize)
		{
			i = 0;
		}
	}

	PelletStage++;
}

void Pellet::ShootyShootyPowPow()
{
	//if ()
	x += 1; //obviously change this. I'm just testing out how to make it appear rn
	if (x > 770)
	{
		active = false;
		x = 0;
	}
}

//void Pellet::SetActive(bool Active)
//{
//	active = Active;
//}
bool Pellet::GetActive()
{
	return active;
}