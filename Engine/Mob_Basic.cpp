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

void Mob::Init(int in_x, int in_y, int in_Px, int in_Pw)
{
	x = in_x;
	y = in_y;
	Px = in_Px;
	Pw = in_Pw;
}

void Mob::Collision(int Gx, int Gy, int Gw, bool &Colliding)
{
	if (Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + w + 1)
	{
		Colliding = true;
	}
}

void Mob::Movement(int Gx, int Gw)
{
	if (aggro)
	{
		if (x + w / 2 > Gx + Gw / 2) //if midpoint of mob is to the right of midpoint of ginger, move left (in direction of ginger)
		{
			MoveLeft = true;
			MoveRight = false;
		}
		else if (x + w / 2 < Gx + Gw / 2)
		{
			MoveRight = true;
			MoveLeft = false;
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

		//Making sure you don't walk off the edge
		if (x + w + 2 > Px + Pw) // + 1 to account for your proper width, and + 1 to stop you from being at the value of the wall, but rather 1 frame before it. 
		{
			MoveLeft = true;
			MoveRight = false;
			RandStage = 0; //Stopping any potential jittery bullshit where you turn around the very next frame.
		}
		else if (x - 2 < Px) //(I'm lazy, and will gladly sacrifice the extra 1 pixel to make sure I never clip walls without need for any additional code)
		{
			MoveRight = true;
			MoveLeft = false;
			RandStage = 0;
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

void Mob::Aggro()
{
	//Remember to set the speed here inside Aggro
}
