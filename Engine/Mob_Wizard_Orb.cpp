#include "Mob_Wizard_Orb.h"

void Orb::Draw(Graphics & gfx/*, int Rx, int Ry, int Rw*/)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= w; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, Colors::Blue2);
		}
	}
}

void Orb::Spawning(int Rx, int Ry, int Rw, int Rh)
{
	if (OrbStage == 50 && active == false) //delay before he releases orb
	{
		active = true; //this is saying: okay, now you can load up the orb.Shoot() function, and Orb[OrbNumber] will be drawn in Game.cpp
		x = Rx + Rw / 2 - w / 2; //Spawning orbs in middle of his body
		y = Ry + Rh / 2 - w / 2; //Spawning orbs in middle of his body





//		//Determining the flight path
//		if (Gx + Gw / 2 > Rx + Rw / 2) //If Ginger is to the right of Wizard
//		{
//			Direction = 1; //Make orbs fly to the right
//		}
//		else
//		{
//			Direction = -1; //Make orbs fly to the left
//		}


//		SpeedY = -24;
//		//SpeedX = PotentialSpeed + SpeedY * 1.5;
//		//int NumberOfFrames = (-1 * (SpeedY / 2) + 1);
//		//SpeedX = PotentialSpeed/4;
//		int NumberOfFrames = (-1 * SpeedY) + 1; //Number of frames it takes for orb to travel up, and back down to original y value
//		int Height = (-1 * SpeedY) * ((-1 * SpeedY) * 0.25 + 0.5); //How high the peak of parabola is
//	//	int XFactor = 4 * 
//		SpeedX = Height * 4/*XFactor*/ / NumberOfFrames; //* 4 = exactly 45 degrees. Should be maximal distance. Need to adjust the multiplier based off the percentage that SpeedY is of PotentialSpeed........... Nah nevermind. Fuck it, I'll keep it simple. Always shoot in 45 degrees





	}

	//resetting to next orb
//	if (OrbStage == 300)
//	{
//		OrbStage = 0;
//		i++;
//
//		if (i == OrbSize)
//		{
//			i = 0;
//		}
//	}


	if (OrbStage < 50) //incrementing orb stage, only if it hasn't shot yet
	{
		OrbStage++;
	}
	else //making sure it doesn't start firing super quick next time if it was in middle of OrbStage counter
	{
		OrbStage = 0;
	}
}

void Orb::ShootyShootyPowPow(/*int Wx, int Wy, int Ww,*/ int Gx, int Gy, int Gw/*, int Gdx, int Gdy*/)
{
	if (OrbSeakingCounter == 10) //Giving it a delay in changing direction
	{
		if (Gx + Gw / 2 < x + w / 2)
		{
			LeftValue--;
			RightValue--;
		}
		if (Gx + Gw / 2 > x + w / 2)
		{
			RightValue++;
			LeftValue++;
		}
		if (Gy + Gw / 2 < y + w / 2)
		{
			UpValue--;
			DownValue--;
		}
		if (Gy + Gw / 2 > y + w / 2)
		{
			DownValue++;
			UpValue++;
		}

		OrbSeakingCounter = -1;
	}
	OrbSeakingCounter++;


	//Stopping it from moving too quickly
	if (LeftValue < -4)
	{
		LeftValue = -4;
	}
	else if (LeftValue > 0)
	{
		LeftValue = 0;
	}
	if (RightValue > 4)
	{
		RightValue = 4;
	}
	else if (RightValue < 0)
	{
		RightValue = 0;
	}
	if (UpValue < -4)
	{
		UpValue = -4;
	}
	else if (UpValue > 0)
	{
		UpValue = 0;
	}
	if (DownValue > 4)
	{
		DownValue = 4;
	}
	else if (DownValue < 0)
	{
		DownValue = 0;
	}	
	

	x += LeftValue + RightValue; //Moving the orb along x value
	y += UpValue + DownValue; //Moving the orb along y value
}

//void Orb::SetActive(bool Active)
//{
//	active = Active;
//}
bool Orb::GetActive()
{
	return active;
}
int Orb::GetX()
{
	return x;
}
int Orb::GetY()
{
	return y;
}
int Orb::GetW()
{
	return w;
}
