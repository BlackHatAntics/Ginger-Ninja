#include "Froggy.h"

//This was one of the first things I coded so many years ago. 
//Don't mind the shitty code; I just copy-pasted it directly into this game out of laziness.

void Froggy::Draw(Graphics& gfx)
{
	//initialising rectangle
	int Lx = 0;
	int Ly = 0;

	//drawing rectangle
	while (Lx <= w && Ly <= h)
	{
		gfx.PutPixel(x + Lx, y + Ly, 54, 205, 13);
		Lx++;
		if (Lx > w)
		{
			Lx = 0;
			Ly++;
		}
	}

	//Drawing eye
	if (d == 1)
	{
		e = 4;
	}
	if (d == 2)
	{
		e = 1;
	}

	gfx.PutPixel(x + e + 0, y + 1 + 0, 0, 0, 0);
	gfx.PutPixel(x + e + 1, y + 1 + 0, 0, 0, 0);
	gfx.PutPixel(x + e + 2, y + 1 + 0, 0, 0, 0);
	gfx.PutPixel(x + e + 0, y + 1 + 1, 0, 0, 0);
	gfx.PutPixel(x + e + 1, y + 1 + 1, 0, 0, 0);
	gfx.PutPixel(x + e + 2, y + 1 + 1, 0, 0, 0);
	gfx.PutPixel(x + e + 0, y + 1 + 2, 0, 0, 0);
	gfx.PutPixel(x + e + 1, y + 1 + 2, 0, 0, 0);
	gfx.PutPixel(x + e + 2, y + 1 + 2, 0, 0, 0);
}

void Froggy::InRange(int Gx, int Gw, int Gy)
{
	if (Gx + Gw >= x && Gx <= x + w && Gy + Gw == y + h)
	{
		isInRange = true;
	}
	else
	{
		isInRange = false;
	}
}

void Froggy::Move()
{
	//Seeing whether or not it will jump
	if (isFrogJumping == false)
	{
		RandstageFrog++;
	}
	if (RandstageFrog == 30)
	{
		r1Frog = rand() % 100 + 1;

		if (r1Frog > 75)
		{
			isFrogJumping = true;
		}
		else
		{
			isFrogJumping = false;
		}

		if (isFrogJumping) //Picking the direction it moves
		{
			r2Frog = rand() % 4 + 1;
		}

		//resetting variables
		RandstageFrog = 0;
		r1Frog = 0;
	}

	if (isFrogJumping)
	{
		if (isFrogReady) //Must have FrogReady check, so that it can't change directions mid flight when it passes a range border
		{
			//Moving frog in specified direction. Need to use the "FrogMoveRight/Left" so you can lock out frog from picking new direction mid-flight.
			if (x < 159/*70*/)
			{
				FrogMoveRight = true;
				FrogMoveLeft = false;
				d = 1;
			}
			else if (x + w > 664/*738*/)
			{
				FrogMoveLeft = true;
				FrogMoveRight = false;
				d = 2;
			}
			else if (x < 324/*250*/)
			{
				if (r2Frog >= 2)
				{
					FrogMoveRight = true;
					FrogMoveLeft = false;
					d = 1;
				}
				else if (r2Frog == 1)
				{
					FrogMoveLeft = true;
					FrogMoveRight = false;
					d = 2;
				}
			}
			else if (x + w > 475/*549*/)
			{
				if (r2Frog == 1)
				{
					FrogMoveRight = true;
					FrogMoveLeft = false;
					d = 1;
				}
				else if (r2Frog >= 2)
				{
					FrogMoveLeft = true;
					FrogMoveRight = false;
					d = 2;
				}
			}
			else
			{
				//The un-biased one
				if (r2Frog <= 2)
				{
					FrogMoveRight = true;
					FrogMoveLeft = false;
					d = 1;
				}
				else if (r2Frog >= 3)
				{
					FrogMoveLeft = true;
					FrogMoveRight = false;
					d = 2;
				}
			}

			isFrogReady = false;
		}

		//Moving it left and right
		if (FrogMoveRight)
		{
			x += 4;
		}
		else if (FrogMoveLeft)
		{
			x -= 4;
		}

		//Making it jump
		y -= JumpHeight;
		JumpHeight -= 2;
	}

	//landing
	if (y >= 584 - h)
	{
		y = 584 - h;
		isFrogJumping = false;
		JumpHeight = 9;
		isFrogReady = true;
		isFrogOnHead = false;
		isFrogReady2 = true;
	}
}

void Froggy::PickUp(int Gx, int Gy, bool S)
{
	if (isFrogJumping == false)
	{
		if (S && isInRange)
		{
			isFrogOnHead = true;
		}
		if (isFrogOnHead == true)
		{
			y = Gy - h; //Placing it on head
			if (isFrogReady2 == true)
			{
				FrogTempX = x - Gx; //assigning value, so that frog stays in same place on head relative to where it was when picked up
				isFrogReady2 = false;
			}
			x = Gx + FrogTempX; //Staying on head when dude moves
		}
	}
}
