#include "Ginger.h"

void Ginger::Init(int in_x, int in_y, int in_speed)
{
	x = in_x;
	y = in_y;
	speed = in_speed;
}

void Ginger::Draw(Graphics& gfx, Color h, Color b)
{
	//hair
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy < 6; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, h);
		}
	}
	//body
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= 14; loopy++)
		{
			gfx.PutPixel(x + loopx, y + 6 + loopy, b);
		}
	}

	//Eye
	for (int loopx = 0; loopx <= 4; loopx++)
	{
		for (int loopy = 0; loopy <= 4; loopy++)
		{
			gfx.PutPixel(x + eye + loopx, y + (6 + 1) + loopy, Colors::Blue2);
		}
	}
}

void Ginger::EyeLogic()
{
	//Maybe just put this inside Movement
	if (MoveRight && !MoveLeft)
	{
		eye = 15;
	}
	if (MoveLeft && !MoveRight)
	{
		eye = 1;
	}
}

void Ginger::Movement()
{
	if (MoveRight)
	{
		x += speed;
	}
	if (MoveLeft)
	{
		x -= speed;
	}
}

void Ginger::Jump()
{
	if (isJumping)
	{
		JumpLock = true; //Find a way to not call this every time?

		y -= jh;
		jh -= 2;

		if (jh == -1)
		{
			jh = 0;
//			isFalling = true;
		}
		if (jh == -2) // I added this extra frame tick of nothing, so gravity has to wait 1 more frame, and doesn't immediately subtract the +1
		{
			jh = JumpHeight;
			isJumping = false;
		}

	}


}

void Ginger::Gravity()
{
	//Maybe keep this last in load order?
	if (!isJumping && isFalling)
	{
		y += fh;
		fh += 2;
	}
	else
	{
		isFalling = true; //Setting it up, so it needs to pass a new round of checks to make it not fall next frame
	}
}

void Ginger::HitGround(int py)
{
	isFalling = false;
	fh = 1;
	y = py - w - 1;
}

void Ginger::Delta()
{
	//Just keeping track of previous y position, so you can land on platforms if you were above them in the previous frame
	//X pos is so you can tell which side you're hitting the wall from
	dy = y;
	dx = x;
}

void Ginger::HitWall(int wx)
{
	x = wx;
}

void Ginger::HitCeiling(int py)
{
	isJumping = false;
	jh = JumpHeight;
	y = py + 1;
}

void Ginger::SetMoveRight(bool z)
{
	MoveRight = z;
}
void Ginger::SetMoveLeft(bool z)
{
	MoveLeft = z;
}
void Ginger::SetJumping(bool z)
{
	isJumping = z;
}
void Ginger::SetFalling(bool z)
{
	isFalling = z;
}
void Ginger::SetJumpLock(bool z)
{
	JumpLock = z;
}

bool Ginger::GetJumpLock()
{
	return JumpLock;
}
int Ginger::GetW()
{
	return w;
}
//bool Ginger::GetMoveRight()
//{
//	return MoveRight;
//}
//bool Ginger::GetMoveLeft()
//{
//	return MoveLeft;
//}
//int Ginger::GetSpeed()
//{
//	return speed;
//}
int Ginger::GetX()
{
	return x;
}
int Ginger::GetY()
{
	return y;
}
int Ginger::GetDX()
{
	return dx;
}
int Ginger::GetDY()
{
	return dy;
}

