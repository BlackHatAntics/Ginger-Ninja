#include "Mob_Charger.h"

void Charger::Draw(Graphics& gfx)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= w; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, Colors::White1);
		}
	}

	//Eye
	if (MoveLeft)
	{
		eye = 2;
		Ed = -1;
	}
	else if (MoveRight)
	{
		eye = w - 2 - 3;
		Ed = 1;
	}

	if (aggro)
	{
		int EyeOffset = 0;
		if (Ed == -1)
		{
			EyeOffset = 3;
		}
		for (int loopy = 0; loopy <= 3; loopy++)
		{
			for (int loopx = 0; loopx <= loopy; loopx++)
			{
				gfx.PutPixel(x + eye + (loopx * Ed) + EyeOffset, y + 5 + loopy, Colors::Black2);
			}
		}
	}
	else
	{
		for (int loopx = 0; loopx <= 3; loopx++)
		{
			for (int loopy = 0; loopy <= 3; loopy++)
			{
				gfx.PutPixel(x + eye + loopx, y + 5 + loopy, Colors::Black);
			}
		}
	}
}

void Charger::Init(int in_x, int in_Px, int in_y, int in_Pw, int in_roam)
{
	x = in_x;
	y = in_y - w - 1;
	Px = in_Px;
	Pw = in_Pw;
	InitX = in_x;
	roam = in_roam;
}

void Charger::Collision(int Gx, int Gy, int Gw, bool &Colliding)
{
	if ((Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + w + 1) && alive) //I know it only loads the function if it's alive so this seems redundant, but otherwise it's a frame late in deciding when you hit a mob, so sometimes you can take damage at the very end of your dash, even if you killed the mob.
	{
		Colliding = true;
	}
}

void Charger::Death(int Gx, int Gy, int Gw, int Gds, int Gsp)
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

void Charger::Movement(int Gx, int Gw)
{
	//Copy-pasted most of this shit from Mob_Basic and it's honestly coded like shit, but I am a lazy-ass and I'm just tryin'a finish quick.
	if (aggro /*|| ChargeStage > 0*/)
	{
		if (ChargeStage <= 20)
		{
			speed = -1;

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

			//making sure you don't back-up over the edge
			if (x + w + 1 - speed > Px + Pw)
			{
				x = Px + Pw - 1 - w + speed;
			}
			else if (x - 1 + speed < Px)
			{
				x = Px + 1 - speed;
			}
		}
		else if (ChargeStage <= 25) //acceleration
		{
			speed += 5;
		}
		else if (ChargeStage <= 45) //top speed
		{

		}
		else if (ChargeStage <= 48) //mini slow-down
		{
			speed -= 3;
		}
		else //when it's done
		{
			ChargeStage = -1; //Will be raised to 0 at bottom
			speed = 1;
		}
		
	//	isCharging = true;
		
		//Making sure they don't Charge off the ledge
		if (x + w + 1 + speed > Px + Pw) // + 1 to account for your proper width, and + 1 to stop you from being at the value of the wall, but rather 1 frame before it. 
		{
			MoveRight = false;
			x = Px + Pw - 1 - w;
		}
		else if (x - 1 - speed < Px) //(I'm lazy, and will gladly sacrifice the extra 1 pixel to make sure I never clip walls without need for any additional code)
		{
			MoveLeft = false;
			x = Px + 1;
		}

		ChargeStage++;
	}
	//else if (isCharging)
	//{
	//
	//}
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

void Charger::Aggro(int Gx, int Gy, int Gw, int Gog)
{
	if (Gx < x + w + 1 + 350 && Gx + Gw + 1 > x - 350 && Gy <= y + w && Gy + Gw >= y /*- 81*/ && !(Gog && Gy + Gw <= y + w - 50)) //If Ginger is within _ pixels on either side, and at the same basic height level, and not on another platform too high up, then the mob will be aggro'd
	{
		aggro = true;
		//speed = 2;
	}
	else if (Gx > x + w + 1 + 350 + 130 || Gx + Gw + 1 < x - 350 - 130 || (Gog && Gy + Gw < y + w - 70) || Gy >= y + w + 20) //once you are aggro'd, you don't lose aggro unless you move a certain distance away. The reason I don't include his height, but rather only the hieight of him while on ground, is so you can't go onto a small platform, then lose aggro just by jumping (or just wall jumping). You only lose aggro when you're properly on a higher platform.
	{
		//That 70 is a very critical number. That is the cutoff point between platforms taking you out of aggro, and leaving you in
		//The 20 also dictactes how much lower you need to be
		aggro = false;
		speed = 1;
		ChargeStage = 0; //Just doing a proper reset, so it can't Charge right when u land or anything
	}
}

//void Charger::EyeLogic()
//{
//}

void Charger::StartPoint()
{
	StartPointX = x;
	StartPointY = y;
}

void Charger::Respawn()
{
	alive = true;
	x = StartPointX;
	y = StartPointY;
	ChargeStage = 0;
	RandStage = 0;
	aggro = false;
	speed = 1;
}

bool Charger::GetAlive()
{
	return alive;
}
