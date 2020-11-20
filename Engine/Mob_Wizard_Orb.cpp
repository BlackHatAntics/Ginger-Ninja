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

void Orb::Collision(int Gx, int Gy, int Gw, bool & Colliding)
{
	if (Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + w + 1)
	{
		Colliding = true;
	}
}

void Orb::Death(int Gx, int Gy, int Gw, int Gds, int Gsp)
{
	if (Gds > 0 && Gds <= 4) //If dashing
	{
		if (((Gsp < x && Gx + Gw / 2 >= x + w) || (Gsp > x + w && Gx + Gw / 2 <= x)) //If you started from left and are now on their right, or started on right and are now to the left
			&& Gy + Gw > y && Gy < y + w) //Gotta be at the same height level
		{
			active = false; //Killing the orb
			OrbStage = 0; //Making it so it can spawn again
		}
	}
}

void Orb::Spawning(int Rx, int Ry, int Rw, int Rh)
{
	if (OrbStage == 300 && active == false) //delay before he releases orb
	{
		active = true; //this is saying: okay, now you can load up the orb.Shoot() function, and Orb[OrbNumber] will be drawn in Game.cpp
		x = Rx + Rw / 2 - w / 2; //Spawning orbs in middle of his body
		y = Ry + Rh / 2 - w / 2; //Spawning orbs in middle of his body
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


	if (OrbStage < 300) //incrementing orb stage, only if it hasn't shot yet
	{
		OrbStage++;
	}
//	else //making sure it doesn't start firing super quick next time if it was in middle of OrbStage counter
//	{
//		OrbStage = 0;
//	}
}

void Orb::ShootyShootyPowPow(/*int Wx, int Wy, int Ww,*/ int Gx, int Gy, int Gw/*, int Gdx, int Gdy*/)
{
	//if (OrbTrackingCounter == 6) //This is here to make the orb react slowly. It works well when the values adjust by 1, but when it's adjusted by 0.12 it looks terrible. It's not a perfect system anyway, so 0.12 increments are better. They just make the "45 degree travel path" super apparent. So now I gotta fix it.
	//{
		if (Gx + Gw / 2 < x + w / 2)
		{
			LeftValue -= 0.125; //it is 0.125 so it reacts slowly, and has a slow "tracking" effect. Makes it wavy and whatnot as well. 0.125 is 1/8. Don't really have any other numbers that go in nicely. 0.2 is too much, 0.1 is too little
			if (LeftValue < -4) //Only start adding speed from RightValue if LeftValue is at max speed
			{
				RightValue -= 0.125;
			}
		}
		if (Gx + Gw / 2 > x + w / 2)
		{
			RightValue += 0.125;
			if (RightValue > 4) //Only start adding speed from LeftValue if RightValue is at max speed
			{
				LeftValue += 0.125;
			}
		}
		if (Gy + Gw / 2 < y + w / 2)
		{
			UpValue -= 0.125;
			if (UpValue < -4) //Only start adding speed from DownValue if UpValue is at max speed
			{
				DownValue -= 0.125;
			}
		}
		if (Gy + Gw / 2 > y + w / 2)
		{
			DownValue += 0.125;
			if (DownValue > 4) //Only start adding speed from UpValue if DownValue is at max speed
			{
				UpValue += 0.125;
			}
		}
	//	OrbTrackingCounter = -1;
	//}
	//OrbTrackingCounter++;


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
