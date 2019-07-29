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
	void HitGround(int py);
	void HitWall(int wx, bool UP);
	void HitCeiling(int py);
	void Delta();
	void WallJump(bool UP);

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
	int wjh = WallJumpHeight;
	int fh = 1; //fall height?
	int dy; //Delta Y
	int dx; //Delta X
	bool MoveRight = false;
	bool MoveLeft = false;
	bool isJumping = false;
	bool isFalling = false;
	bool JumpLock = false;
	bool WallJumpLock = true;
	bool isWallJumping = false;
	bool HitWallLeft = false;
	bool HitWallRight = false;
//	bool OnWall = false;
};