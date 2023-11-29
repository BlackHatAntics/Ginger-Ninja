#include "Mob_Basic.h"

void Basic::Draw(Graphics& gfx)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= w; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, Colors::Red2);
		}
	}
}

void Basic::Init(int in_x, int in_Px, int in_y, int in_Pw, int in_roam)
{
	x = in_x;
	y = in_y - w - 1; //so he properly sits ontop of the platform without having to type extra bs. Saves me time. I can just copy-paste values from the Ground() function that he's being placed on
	Px = in_Px;
	Pw = in_Pw;
	InitX = in_x;
	roam = in_roam;
}

void Basic::Collision(int Gx, int Gy, int Gw, bool &Colliding)
{
	if ((Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + w + 1) && alive) //I know it only loads the function if it's alive so this seems redundant, but otherwise it's a frame late in deciding when you hit a mob, so sometimes you can take damage at the very end of your dash, even if you killed the mob.
	{
		Colliding = true;
	}
}

void Basic::Death(int Gx, int Gy, int Gw, int Gds, int Gsp)
{
	if (Gds > 0 && Gds <= 4) //If dashing
	{
		//if (((Gsp < x && Gx + Gw / 2 >= x + w) || (Gsp > x + w && Gx + Gw / 2 <= x)) //If you started from left and are now on their right, or started on right and are now to the left
		//	&& Gy + Gw > y && Gy < y + w) //Gotta be at the same height level
		if (((Gsp - (Gw / 2 - 1) <= x && Gx + Gw >= x + w) || (Gsp + (Gw / 2 - 1) >= x + w && Gx <= x))
			&& Gy + Gw >= y && Gy <= y + w)
		{
			alive = false;
		}
	}
}

void Basic::Movement(int Gx, int Gw)
{
	if (aggro)
	{
		if (x + w / 2 > Gx + Gw / 2) //if midpoint of mob is to the right of midpoint of ginger, move left (in direction of ginger)
		{
			//MoveLeft = true;
			//MoveRight = false;
			speed -= 0.5; //so they don't turn around IMMEDIATELY, and jumping over them is successful
		}
		else if (x + w / 2 < Gx + Gw / 2) //if to the left, move right
		{
			//MoveRight = true;
			//MoveLeft = false;
			speed += 0.5;
		}
		//else //if he's not to the left or to the right, but directly under/above, stand still
		//{
		//	MoveRight = false;
		//	MoveLeft = false;
		//}

		//So mob never moves faster than 2 pixels per frame
		if (speed > 2 || speed < -2)
		{
			speed = speed / 1.25; //this will make it always either 2 or -2. (The math works cause if it's ever over 2 it will always be 2.5)
		}


		//Making sure they don't walk off the ledge
		if (x + w + 3 > Px + Pw) // + 1 to account for your proper width, and + 1 to stop you from being at the value of the wall, but rather 1 frame before it. and +1 because it goes by 2 when aggro'd so sometimes clips wall by 1 pixel. too lazy to re-code it, I'll just take the 1 pixel loss
		{
			x = (Px + Pw) - w - 3;
		}
		else if (x - 3 < Px) //(I'm lazy, and will gladly sacrifice the extra 1 pixel to make sure I never clip walls without need for any additional code)
		{
			x = Px + 3;
		}
	}
	else
	{
		//I could totally take 10m to code this all better, and have everything set speed instead of MoveLeft & MoveRight, but I honestly don't care.

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
		//|| making sure they don't walk further than their roam distance; whichever comes first.
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
			RandStage = 0;
		}
	}

	//Actually moving the mob
	if (aggro)
	{
		x += speed;
	}
	else
	{
		if (MoveRight)
		{
			x += speed;
		}
		else if (MoveLeft)
		{
			x -= speed;
		}
	}
}

void Basic::Aggro(int Gx, int Gy, int Gw, int Gog)
{
	if (Gx < x + w + 1 + 160 && Gx + Gw + 1 > x - 160 && Gy <= y + w && Gy + Gw >= y - 42 && !(Gog && Gy + Gw <= y + w - 50)) //If Ginger is within _ pixels on either side, and at the same basic height level, and not on another platform too high up, then the mob will be aggro'd
	{
		aggro = true;
		//speed = 2;
	}
	else if (Gx > x + w + 1 + 160 + 100 || Gx + Gw + 1 < x - 160 - 100 || (Gog && Gy + Gw < y + w - 70) || Gy + Gw >= y + w + 50) //once you are aggro'd, you don't lose aggro unless you move a certain distance away. The reason I don't include his height, but rather only the hieight of him while on ground, is so you can't go onto a small platform, then lose aggro just by jumping (or just wall jumping). You only lose aggro when you're properly on a higher platform.
	{
		//That 70 is a very critical number. That is the cutoff point between platforms taking you out of aggro, and leaving you in
		//The 50 also dictactes how much lower you need to be
		aggro = false;
		speed = 1;
	}
}

void Basic::DeathAnimation(Graphics & gfx)
{
	int fade = DeathStage + 1 * (w / 3); //one third of the body height will dissapear from the top each frame.
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= (w - fade); loopy++)
		{
			gfx.PutPixel(x + loopx, y + fade + loopy, Colors::Red2);
		}
	}
	DeathStage++;
}

void Basic::StartPoint()
{
	StartPointX = x;
	StartPointY = y;
}

void Basic::Respawn()
{
	alive = true;
	x = StartPointX;
	y = StartPointY;
	aggro = false;
	DeathStage = 0;
}

int Basic::GetStartPointX()
{
	return StartPointX;
}
int Basic::GetStartPointY()
{
	return StartPointY;
}
bool Basic::GetAlive()
{
	return alive;
}

int Basic::GetDeathStage()
{
	return DeathStage;
}
