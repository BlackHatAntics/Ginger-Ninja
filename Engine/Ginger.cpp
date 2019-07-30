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

void Ginger::Movement(bool kbdD)
{
	if (MoveRight)
	{
		x += speed;
	}
	if (MoveLeft)
	{
		x -= speed;
	}
	if (kbdD)
	{
		y += speed;
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
	if (isFalling && !isJumping && !isWallJumpingY)
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

void Ginger::WallJump(bool UP)
{
	//Pretty much all the logic is inside HitWall. This is just the physical lift-off
	//if (isWallJumping)
	//{
	//	isJumping = false;
	//	jh = JumpHeight;
	//	if (HitWallLeft)
	//	{
	//		x += wjh;
	//	}
	//	else if (HitWallRight)
	//	{
	//		x -= wjh;
	//	}
	//	y -= wjh;
	//	wjh -= 2;
	//	if (wjh < 0)
	//	{
	//		wjh = WallJumpHeight;
	//		isWallJumping = false;
	//	}
	//}
}

void Ginger::WallJump2(bool UP)
{
	//ISSUES:
	//You can still clip through walls somehow if you spam that shit enough

	//Seeing if you moved off the wall or not, and disabling WallJump if you have
	if (HitWallRight)
	{
		if (x < TempWallValue)
		{
			WallJumpisReady = false; //This stops you from being able to jump if you move off the wall. If you succeed and do jump, this will still be disabled, as you are off the wall anyway.
		}
	}
	else if (HitWallLeft)
	{
		if (x > TempWallValue)
		{
			WallJumpisReady = false; //This stops you from being able to jump if you move off the wall. If you succeed and do jump, this will still be disabled, as you are off the wall anyway.
		}
	}

	//Seeing if you are ready to wall jump (used to be in HitWall)
//	if (UP == false && dy != y) //If you have released the w key, are not on the ground, and are against the wall, then you are ready to press the w key and jump off the wall
//	{
//		if (HitWallRight)
//		{
//			if (x >= TempWallValue)
//			{
//				WallJumpisReady = true;
//			}
//		}
//		else if (HitWallLeft)
//		{
//			if (x <= TempWallValue)
//			{
//				WallJumpisReady = true;
//			}
//		}
//	}
//	else if (dy == y) //You can't wall jump from the ground, idiot
//	{
//		WallJumpisReady = false;
//	}

	//Assuming we are still on the wall, we can proceed to the button push
	if (UP == true && WallJumpisReady)
	{
		wjhY = WallJumpHeight; //Making sure you jump at full height
		wjhX = WallJumpHeight; //Making sure you jump at full height
		isWallJumpingY = true; //Launching off
		isWallJumpingX = true; //Launching off
		x = TempWallValue; //Making sure you start from the wall, not from inside of it. (HitWall is after this in load order, so you gotta do the job yourself sometimes eh)

		isJumping = false; //Just so you don't get the added y values from both, creating a massive jump
		jh = JumpHeight; //And of course remembering to reset your jump height, because this isn't in the "HitGround" function for whatever reason...
		fh = 1; //Resetting gravity as well, so you can chain them without progressively heavier gravity
	}

	//Now for the actual jump
	//(I split this up into both Y and X, so if you hit a ceiling, your y will stop, but your x will keep going
	//This also helps you not bounce off walls, so you can chain wall jumps)
	if (isWallJumpingX)
	{
		if (HitWallLeft)
		{
			x += wjhX;
		}
		else if (HitWallRight)
		{
			x -= wjhX;
		}
		wjhX -= 2;

		//Ending the WallJump, if you make it this far
		if (wjhX == -1)
		{
			wjhX = 0;
		}
		if (wjhX == -2) // I added this extra frame tick of nothing, so gravity has to wait 1 more frame, and doesn't immediately subtract the final +1
		{
			isWallJumpingX = false;
		}
	}
	if (isWallJumpingY)
	{
		y -= wjhY;
		wjhY -= 2;

		//Ending the WallJump, if you make it this far
		if (wjhY == -1)
		{
			wjhY = 0;
		}
		if (wjhY == -2) // I added this extra frame tick of nothing, so gravity has to wait 1 more frame, and doesn't immediately subtract the final +1
		{
			isWallJumpingY = false;
		}
	}
}

void Ginger::HitWall2(int wx, bool UP)
{
	//Setting it up so WallJump knows which way to alter your x value
	if (x > wx)
	{
		HitWallRight = true;
		HitWallLeft = false;
	}
	else if (x < wx)
	{
		HitWallLeft = true;
		HitWallRight = false;
	}

	if (UP == false && dy != y) //If you have released the w key, are not on the ground, and are against the wall, then you are ready to press the w key and jump off the wall
	{
		WallJumpisReady = true;
	}
	else if (dy == y) //You can't wall jump from the ground, idiot
	{
		WallJumpisReady = false;
	}

	TempWallValue = wx; //This is now temporarily (until you hit another wall) the wall x value that will determine if you are still against the wall or not in WallJump()

	if (isWallJumpingX) //Making sure you don't bounce off a wall, because otherwise the above code just switches which direction your x is moving
	{
		isWallJumpingX = false;
	}

	x = wx; //Stopping you from going through the wall
}

void Ginger::HitWall(int wx, bool UP)
{
	//if (isWallJumping) //Resetting, so you don't just bounce off a wall, but rather set up for another wall jump
	//{
	//	isWallJumping = false; //Maybe this is a bad idea, because it stops all upward movement
	//	//wjh = WallJumpHeight;
	//}
	//
	////Setting it up so WallJump knows which way to alter your x value
	//if (x > wx)
	//{
	//	HitWallRight = true;
	//	HitWallLeft = false;
	//}
	//else if (x < wx)
	//{
	//	HitWallLeft = true;
	//	HitWallRight = false;
	//}
	//x = wx; //Stopping you from going through the wall
	//
	////Setting you up for WallJump
	//if (UP == false && y - JumpHeight * 2 < dy && y != dy) //If you are touching the wall (this is true because code is inside HitWall), and you have released the w key, and you are moving upwards, THEN you are ready to wall jump
	//{
	//	WallJumpisReady = true;
	//}
	//else if (y == dy) //Just making sure if you slide all the way down the wall to the ground, it will re-disable wall jump
	//{
	//	WallJumpisReady = false;
	//}
	//
	//if (UP == true && WallJumpisReady == true /*&& y < dy*/) //If you press w again, after having it off for at least 1 frame. (So you can't just hold w down, you have to time it)
	//{
	//	isWallJumping = true;
	//	fh = 1; //Resetting gravity
	//	WallJumpisReady = false;
	//
	//	wjh = WallJumpHeight; //Resetting it, so you can chain jumps along walls
	//}
}

void Ginger::HitCeiling(int py)
{
	//Stopping and resetting your current jump. The reason I don't 
	isJumping = false;
	jh = JumpHeight;
	isWallJumpingY = false; //Stops vertical movement, but keeps the X movement going
	//wjh = WallJumpHeight;

	y = py + 1; //Preventing you from going through the ceiling
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

