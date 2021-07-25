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

	//ears/eyes
//	for (int loopx = 0; loopx <= 3; loopx++)
//	{
//		for (int loopy = 0; loopy <= 1; loopy++)
//		{ 
//			if (EyeDirection < 0)
//			{
//				//left
//				gfx.PutPixel(x /*+ 1*/ + loopx, y - 1 + loopy, Colors::Green2);
//			}
//			else if (EyeDirection > 0)
//			{
//				//right
//				gfx.PutPixel(x + w /*- 1*/ - 3 + loopx, y - 1 + loopy, Colors::Green2);
//			}
//			
//		}
//	}
}

void Jumper::Init(int in_x, int in_Px, int in_y, int in_Pw)
{
	x = in_x;
	y = in_y - w - 1;
	Px = in_Px;
	Pw = in_Pw;
}

void Jumper::Collision(int Gx, int Gy, int Gw, bool &Colliding)
{
	if ((Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + w + 1) && alive) //I know it only loads the function if it's alive so this seems redundant, but otherwise it's a frame late in deciding when you hit a mob, so sometimes you can take damage at the very end of your dash, even if you killed the mob.
	{
		Colliding = true;
	}
}

void Jumper::Death(int Gx, int Gy, int Gw, int Gds, int Gsp)
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
	RandStage = 0;
	isJumping = false;
	aggro = false;
}

void Jumper::Movement(int Gx, int Gw/*, int Gdx*/)
{
	//I removed aggro functionality, because it made it too fucking impossible. Even if you COULD manage to kill them, it was anti-fun

	//if (aggro && (!(isJumping)))
	//{
	//	JumpX = ((Gx + Gw / 2) - (x + w / 2) + (Gx - Gdx) * (sjh + 1)) / (sjh + 1); //(midpoint of Ginger - midpoint of Jumper + how much distance the ginger will move with his current velocity during Jumper's jump duration) / number of frames it will take Jumper to jump. This makes him land directly on the player's head. (unless he jukes and changes direction/velocity)
	//	isJumping = true;
	//
	//	//Preventing him from jumping super far.
	//	if (JumpX > 6)
	//	{
	//		JumpX = 6;
	//	}
	//	else if (JumpX < -6)
	//	{
	//		JumpX = -6;
	//	}
	//
	//	//Stopping him from going over the platform edge
	//	while (x + (JumpX * (sjh + 1)) < Px)
	//	{
	//		JumpX++;
	//	}
	//	while (x + w + (JumpX * (sjh + 1)) > Px + Pw)
	//	{
	//		JumpX--;
	//	}
	//
	//}
	//else
	//{
		//deciding when to jump
		if (!(isJumping))
		{
			RandStage++; //Delay before deciding whether or not to jump (otherwise looks erratic)
		}

		if (RandStage == 28 && isJumping == false) //Waiting for delay between jumps, and isn't currently jumping (so it doesn't change direction mid-jump)
		{	
			JumpX = rand() % 42 - 6; //Assigning the random value. The -6 is so it gives you a value between -6 and +6. (higher values will mean no movement) //Make this % value higher if you ever re-implement aggro

			//stopping it from going over the edge
			while (JumpX <= 6 && (x + (JumpX * (sjh + 1)) < Px || x + w + (JumpX * (sjh + 1)) > Px + Pw)) //<= 6 is making sure it's actually a jumpable variable (otherwise it will just constantly re-roll), and rest is making sure it won't go over left || right side.
			{
				JumpX = rand() % 65 - 6; //if it's going to go over the edge, just re-roll
			}

			if (JumpX <= 6)
			{
				isJumping = true;
				//EyeDirection = JumpX;
			}
			RandStage = 0;
		}
	//}

	if (isJumping)
	{
		//vertical jump
		y = y - jh;
		jh = jh - 2;

		//lateral jump movement (right)
		//x = x + sjh / 1.5;
		x = x + JumpX;
	}

	//resetting the jump height at end of jump
	if (jh == -sjh - 2)
	{
		jh = sjh;
		isJumping = false;
	}
}

//void Jumper::Aggro(int Gx, int Gy, int Gw, int Gog)
//{
	//I removed aggro functionality, because it made it too fucking impossible. Even if you COULD manage to kill them, it was anti-fun
//	if (Gx < x + w + 1 + 160 && Gx + Gw + 1 > x - 160 && Gy <= y + w && Gy + Gw >= y + w - 81 && !(Gog && Gy + Gw <= y + w - 50)) //If Ginger is within _ pixels on either side, and at the same basic height level, and not on another platform too high up, then the mob will be aggro'd
//	{
// 		aggro = true;
//		//speed = 2;
//	}
//	else if (Gx > x + w + 1 + 160 + 100 || Gx + Gw + 1 < x - 160 - 100 || (Gog && Gy + Gw < y + w - 70) || Gy + Gw >= y + w + 50) //once you are aggro'd, you don't lose aggro unless you move a certain distance away. The reason I don't include his height, but rather only the height of him while on ground, is so you can't go onto a small platform, then lose aggro just by jumping (or just wall jumping). You only lose aggro when you're properly on a higher platform.
//	{
//		//That 70 is a very critical number. That is the cutoff point between platforms taking you out of aggro, and leaving you in
//		//The 50 also dictactes how much lower you need to be
//		aggro = false;
//		//speed = 1;
//	}
//}

bool Jumper::GetAlive()
{
	return alive;
}
