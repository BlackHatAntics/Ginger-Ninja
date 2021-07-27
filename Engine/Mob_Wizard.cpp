#include "Mob_Wizard.h"

void Wizard::Draw(Graphics & gfx)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= h; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, Colors::Blue1);
		}
	}
}

void Wizard::Init(int in_x, int in_Px, int in_y, int in_Pw, int in_roam)
{
	x = in_x;
	y = in_y - h - 1;
	Px = in_Px;
	Pw = in_Pw;
	InitX = in_x;
	roam = in_roam;
}

void Wizard::Collision(int Gx, int Gy, int Gw, bool & Colliding)
{
	if ((Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + h + 1) && alive)
	{
		Colliding = true;
	}
}

void Wizard::Death(int Gx, int Gy, int Gw, int Gds, int Gsp)
{
	if (Gds > 0 && Gds <= 4) //If dashing
	{
		//if (((Gsp < x && Gx + Gw / 2 >= x + w) || (Gsp > x + w && Gx + Gw / 2 <= x)) //If you started from left and are now on their right, or started on right and are now to the left
		//	&& Gy + Gw > y && Gy < y + h) //Gotta be at the same height level
		if (((Gsp - (Gw / 2 - 1) <= x && Gx + Gw >= x + w) || (Gsp + (Gw / 2 - 1) >= x + w && Gx <= x))
			&& Gy + Gw >= y && Gy <= y + h)
		{
			alive = false;
		}
	}
}

void Wizard::StartPoint()
{
	StartPointX = x;
	StartPointY = y;
}

void Wizard::Respawn()
{
	alive = true;
	x = StartPointX;
	y = StartPointY;
	aggro = false;
	//speed = 1;
	RandStage = 0;
}

void Wizard::Movement(int Gx, int Gw)
{
	//Change the movement, I don't want it to be the same as Basic Mob
	if (aggro)
	{
		if (x + w / 2 > Gx + Gw / 2) //if midpoint of mob is to the right of midpoint of ginger, move right (away from ginger)
		{
			MoveRight = true;
			MoveLeft = false;
		}
		else if (x + w / 2 < Gx + Gw / 2)
		{
			MoveLeft = true;
			MoveRight = false;
		}

		//Making sure they don't walk off the ledge
		if (x + w + 3 > Px + Pw) //have to do +3 because it still adds 2 each frame at the bottom of the function. Too lazy to re-code it.
		{
			x = Px + Pw - w - 3;
		}
		else if (x - 3 < Px)
		{
			x = Px + 3;
		}
	}
	else
	{
		RandStage++;
		int test0 = 69; //Just initializing it to a stupid number you can't use (compiler doesn't like if you leave it empty)
		//Randomly generate the movement
		if (RandStage == 4) //Making it so it only picks a possible value every _ number of frames. Stops it from looking so jittery
		{
			test0 = rand() % 10; //Deciding whether you will change the movement, or stay on the current path
			RandStage = 0;
		}
		if (test0 == 0) //If you have passed the test, and you will move, you will now decide in which direction
		{
			int test1 = rand() % 8 + 1;
			if (test1 == 1)
			{
				MoveRight = true;
				MoveLeft = false;
			}
			else if (test1 == 2)
			{
				MoveLeft = true;
				MoveRight = false;
			}
			else if (test1 >= 3)
			{
				MoveRight = false;
				MoveLeft = false;
			}
		}

		//Making sure they don't walk off the edge (if aggro'd it just stops movement. If here in idle it makes them move back the other way)
		if (x + w + 2 > Px + Pw || x > InitX + roam) // + 1 to account for your proper width, and + 1 to stop you from being at the value of the wall, but rather 1 frame before it. 
		{
			MoveLeft = true;
			MoveRight = false;
			RandStage = 0; //Stopping any potential jittery bullshit where you turn around the very next frame.
		}
		else if (x - 2 < Px || x < InitX - roam) //(I'm lazy, and will gladly sacrifice the extra 1 pixel to make sure I never clip walls without need for any additional code)
		{
			MoveRight = true;
			MoveLeft = false;
			RandStage = 0; //I'm super lazy and will gladly call this every frame, lol
		}
	}

	//Actually moving the mob
	if (MoveRight)
	{
		x += speed;
	}
	else if (MoveLeft)
	{
		x -= speed;
	}
}

void Wizard::Aggro(int Gx, int Gy, int Gw, int Gog)
{
	if (Gx < x + w + 1 + 160 && Gx + Gw + 1 > x - 160 && Gy <= y + h && Gy + Gw >= y - 42 && !(Gog && Gy + Gw <= y + h - 50)) //If Ginger is within _ pixels on either side, and at the same basic height level, and not on another platform too high up, then the mob will be aggro'd
	{
		aggro = true;
		speed = 2;
	}
	else if (Gx > x + w + 1 + 160 + 100 || Gx + Gw + 1 < x - 160 - 100 || (Gog && Gy + Gw < y + h - 70) || Gy + Gw >= y + h + 50) //once you are aggro'd, you don't lose aggro unless you move a certain distance away. The reason I don't include his height, but rather only the hieight of him while on ground, is so you can't go onto a small platform, then lose aggro just by jumping (or just wall jumping). You only lose aggro when you're properly on a higher platform.
	{
		//That 70 is a very critical number. That is the cutoff point between platforms taking you out of aggro, and leaving you in
		//The 50 also dictactes how much lower you need to be
		aggro = false;
		speed = 1;
	}
}

//void Wizard::Shoot(int Gx, int Gy, int Gw)
//{
//	if (aggro)
//	{
//		//if (PelletStage == 10) //short delay before he starts firing
//		//{
//		//	pel[PelletNumber].SetActive(true); //this is saying: okay, now you can load up the pel.Shoot() function, and Pellet[PelletNumber] will be drawn in Game.cpp
//		//}
//		//
//		//if (PelletStage == 100)
//		//{
//		//	PelletNumber++;
//		//	PelletStage = 0;
//		//
//		//	if (PelletNumber > PelletSize)
//		//	{
//		//		PelletNumber = 0;
//		//	}
//		//}
//		//
//		//PelletStage++;
//	}
//}

bool Wizard::GetAlive()
{
	return alive;
}

bool Wizard::GetAggro()
{
	return aggro;
}

int Wizard::GetX()
{
	return x;
}
int Wizard::GetY()
{
	return y;
}
int Wizard::GetW()
{
	return w;
}
int Wizard::GetH()
{
	return h;
}

//int Wizard::GetPelletSize()
//{
//	return PelletSize;
//}
