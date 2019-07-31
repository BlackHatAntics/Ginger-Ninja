#pragma once
#include "Graphics.h"
#include "MainWindow.h"
#include "Keyboard.h"

class Ginger
{
public:
//	Ginger(int in_x, int in_y, int in_speed)
//	{
//		x = in_x;
//		y = in_y;
//		speed = in_speed;
//	}
	void Init(int in_x, int in_y, int in_speed);
	void Draw(Graphics& gfx, Color h, Color b);
	void EyeLogic();
	void Movement(bool kbdD);
	void Jump();
	void Gravity();
	void HitGround(int px, int py, int pw);
	void HitWall(int wx, bool UP);
	void HitCeiling(int py);
	void Delta();
	void WallJump(bool UP);
	void WallJump2(bool UP);
	void HitWall2(int wx, int wy, int wh, bool UP);
	bool OnGround();
	bool OnWall();

	void SetMoveRight(bool z);
	void SetMoveLeft(bool z);
	void SetJumping(bool z);
	void SetFalling(bool z);
	void SetJumpLock(bool z);
	bool GetJumpLock();
	int GetW();
	//bool GetMoveRight();
	//bool GetMoveLeft();
	//int GetSpeed();
	int GetX();
	int GetY();
	int GetDX();
	int GetDY();
private:
	int x;
	int y;
	const int w = 20;
	int speed;
	int eye = 15;
	const int JumpHeight = 17;
	int jh = JumpHeight; //jump height
	const int WallJumpHeight = JumpHeight /*/ 1.5*/; //Remember to make sure this works out to be an odd number
	int wjhY = WallJumpHeight;
	int wjhX = WallJumpHeight;
	int fh = 1; //fall height?
	int dy; //Delta Y
	int dx; //Delta X
	bool MoveRight = false;
	bool MoveLeft = false;
	bool isJumping = false;
	bool isFalling = false;
	bool JumpLock = false;
//	bool JumpisReady = false;
	bool WallJumpisReady = false;
	bool isWallJumpingY = false; //The reason I split these into 2, is so if you hit a ceiling, your y will stop, but your x will keep going. ...
	bool isWallJumpingX = false; //This also helps you not bounce off walls, so you can chain wall jumps
	bool HitWallLeft = false; //The last wall you made contact with, you hit on the left
	bool HitWallRight = false; //The last wall you made contact with, you hit on your right side
//	bool OnGround = false;
	int TempWallValueX = 0;
	int TempWallValueY = 0;
	int TempWallValueH = 0;
	int TempGroundValueX = 8; //Just initializing so everything doesn't brake at compile time.
	int TempGroundValueY = 8;
	int TempGroundValueW = 8;
};