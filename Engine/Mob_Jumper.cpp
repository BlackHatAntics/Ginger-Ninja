#include "Mob_Jumper.h"

void Jumper::Draw(Graphics& gfx)
{
	//body
	for (int loopx = 0; loopx <= w - 2; loopx++)
	{
		for (int loopy = 0; loopy <= w - 2; loopy++)
		{
			gfx.PutPixel(x + 1 + loopx, y + 1 + loopy, Colors::Green2);
		}
	}
	//perimeter top
	for (int loopx = 0; loopx <= w; loopx++)
	{
		gfx.PutPixel(x + loopx, y, Colors::Green3);
	}
	//perimeter bottom
	for (int loopx = 0; loopx <= w; loopx++)
	{
		gfx.PutPixel(x + loopx, y + w, Colors::Green3);
	}
	//perimeter left
	for (int loopy = 0; loopy <= w; loopy++)
	{
		gfx.PutPixel(x, y + loopy, Colors::Green3);
	}
	//perimeter right
	for (int loopy = 0; loopy <= w; loopy++)
	{
		gfx.PutPixel(x + w, y + loopy, Colors::Green3);
	}
}

void Jumper::Init(int in_x, int in_y, int in_Px, int in_Pw)
{
	x = in_x;
	y = in_y;
	Px = in_Px;
	Pw = in_Pw;
}

void Jumper::Collision(int Gx, int Gy, int Gw, bool &Colliding)
{
	if (Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + w + 1)
	{
		Colliding = true;
	}
}

void Jumper::Death(int Gx, int Gy, int Gw, int Gds, int Gsp)
{
	if (Gds > 0 && Gds <= 4) //If dashing
	{
		if (((Gsp < x && Gx + Gw / 2 >= x + w) || (Gsp > x + w && Gx + Gw / 2 <= x)) //If you started from left and are now on their right, or started on right and are now to the left
			&& Gy + Gw > y && Gy < y + w) //Gotta be at the same height level
		{
			alive = false;
		}
	}
}

void Jumper::StartPoint()
{
	StartPointX = x;
	StartPointY = y;
}

void Jumper::Respawn()
{
	alive = true;
	x = StartPointX;
	y = StartPointY;
	jh = sjh;
}

void Jumper::Movement(int Gx, int Gw)
{
	//deciding when to jump
	if (!(isJumping))
	{
		RandStage++;
	}
	
	if (RandStage == 28 && isJumping == false)
	{
		test0 = rand() % 65 - 6;

		//stopping it from going over the edge
		while (test0 <= 6 && (x + (test0 * (sjh + 1)) < Px || x + w + (test0 * (sjh + 1)) > Px + Pw)) //<= 6 is making sure it's actually a jumpable variable (otherwise it will just constantly re-roll), and rest is making sure it won't go over left || right side.
		{
			test0 = rand() % 65 - 6; //if it's going to go over the edge, just re-roll
		}

		if (test0 <= 6)
		{
			isJumping = true;
		}
		RandStage = 0;
	}

	if (isJumping)
	{
		//vertical jump
		y = y - jh;
		jh = jh - 2;

		//lateral jump movement (right)
		//x = x + sjh / 1.5;
		x = x + test0;
	}

	// aggro jump
	//y = y - jh;
	//jh = jh - 2;
	////lateral jump movement
	//x = x + sjh/1.5;

	//resetting the jump height at end of jump
	if (jh == -sjh - 2)
	{
		jh = sjh;
		isJumping = false;
	}
}

bool Jumper::GetAlive()
{
	return alive;
}
