#pragma once
#include "Graphics.h"
#include "MainWindow.h"
#include "Keyboard.h"
#include "Colors.h"

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
	void Draw(Graphics& gfx/*, Color h, Color b*/);
	void EyeLogic();
	void Movement(bool SHIFT);
	void Jump();
	void Gravity();
	void HitGround(int px, int py, int pw);
	//void HitWallOld(int wx, bool UP);
	void HitCeiling(int py);
	void Delta();
	//void Direction();
	void TheoreticalValueReset(); //So you are checking which walls/ground you've hit THIS FRAME, not previous frames.
	//void WallJumpOld(bool UP);
	void WallJump2(bool UP);
	void HitWall2(int wx, int wy, int wh, bool UP);
	void HitGroundPre(int py);
	void HitWallPre(int wx);
	void HitCeilingPre(int py);
	bool OnGround();
	bool OnWall();
	void Cheating(bool UP, bool DOWN, bool LEFT, bool RIGHT, bool C, bool CTRL);
	void ClearTempWall();
	void ScreenSwitch();
	void Dash(bool SPACE);
	void DrawDash(Graphics& gfx);
	void Respawn(int X, int Y);
	void DeathAnimation(Graphics& gfx);

	void SetMoveRight(bool z);
	void SetMoveLeft(bool z);
	void SetJumping(bool z);
	void SetFalling(bool z);
	void SetJumpisReady(bool z);
	bool GetJumpisReady();
	int GetW();
	//bool GetMoveRight();
	//bool GetMoveLeft();
	//int GetSpeed();
	int GetX();
	int GetY();
	int GetDX();
	int GetDY();
	int GetTX();
	int GetTY();
	int GetDashStage();
	int GetOnGroundValue();
	int GetStartPoint();
	bool GetCheating();
	bool GetHitWall();
	int GetDeathStage();
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
	int dy; //Delta Y (Where y was the previous frame)
	int dx; //Delta X (Where x was the previous frame)
	int ty; //Theoretical Y (where y is this frame -- before being edited by the platforms n shit) //all theoritical shit is done in Game
	int tx; //Theoretical X (where x is this frame -- before being edited by the walls n shit) //all theoritical shit is done in Game
	int d = 2; //Direction. 1 = left, 2 = right
	bool MoveRight = false;
	bool MoveLeft = false;
	bool isJumping = false;
	bool isFalling = false;
	//	bool JumpLock = true;
	bool JumpisReady = false;
	bool WallJumpisReady = false;
	bool isWallJumpingY = false; //The reason I split these into 2, is so if you hit a ceiling, your y will stop, but your x will keep going. ...
	bool isWallJumpingX = false; //This also helps you not bounce off walls, so you can chain wall jumps
	bool HitWallLeft = false; //The last wall you made contact with, you hit on the left
	bool HitWallRight = false; //The last wall you made contact with, you hit on your right side
	bool HitWall = false; //Whether or not you hit a wall THIS FRAME. (Used in Ground() to prevent you clpping through walls if you hit a corner)
	int TempWallValueX = 0;
	int TempWallValueY = 0;
	int TempWallValueH = 0;
	int TempGroundValueX = 8; //Just initializing so everything doesn't brake at compile time.
	int TempGroundValueY = 8;
	int TempGroundValueW = 8;
	bool cheating = false;
	bool CheatingLock = false;
	int DashLength = 40;
	int DashStage = 0;
	int DashChargeup = 0;
	bool DashisReady = true;
	bool isDashing = false;
	int DashStartPoint;
	//int DashEndPoint;
//	int hR = 255; //hair RGB
//	int hG = 150;
//	int hB = 9;
	Color hC = Colors::Orange2; //hair colour
	int bR = 255; //body RGB
	int bG = 224;
	int bB = 218;
//	int eR = 23; //eye RGB
//	int eG = 105;
//	int eB = 255;
	int DeathStage = 0;
};