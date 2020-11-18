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

void Pellet::Spawning(int PelletSize, int & i, int Rx, int Ry, int Rw, int Rh, bool aggro, int Gx, int Gy, int Gw, int Gdx, int Gdy)
{
	if (PelletStage == 10 && active == false) //short delay before he starts firing
	{
		active = true; //this is saying: okay, now you can load up the pel.Shoot() function, and Pellet[PelletNumber] will be drawn in Game.cpp
		x = Rx + Rw / 2 - w / 2; //Spawning pellets in middle of his body
		y = Ry + Rh / 2 - w / 2; //Spawning pellets in middle of his body

		//Determining the flight path
		if (Gx + Gw / 2 > Rx + Rw / 2) //If Ginger is to the right of Ranger
		{
			Direction = 1; //Make pellets fly to the right
		}
		else
		{
			Direction = -1; //Make pellets fly to the left
		}



	}

	//resetting to next pellet
	if (PelletStage == 100)
	{
		PelletStage = 0;
		i++;

		if (i == PelletSize)
		{
			i = 0;
		}
	}

	if (aggro) //incrementing pellet stage, only if he's aggro / actually firing
	{
		PelletStage++;
	}
	else //making sure it doesn't start firing super quick next time if it was in middle of PelletStage counter
	{
		PelletStage = 0;
	}
}

void Pellet::ShootyShootyPowPow(/*int Rx, int Ry, int Rw, int Gx, int Gy, int Gw, int Gdx, int Gdy*/)
{
	x += SpeedX * Direction; //Moving the pellet along x value
	y += SpeedY/* + */; //Moving the pellet along y value
	SpeedY += 2; //Constant gravity
	if (x > 799 - w || x < 0 || y > 599 - w || y < 0) //borders
	{
		active = false;
		//x = 0;
		//y = 0;
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