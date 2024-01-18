#pragma once
#include "Graphics.h"

//This was one of the first things I coded so many years ago. 
//Don't mind the shitty code; I just copy-pasted it directly into this game out of laziness.

class Froggy
{
public:
	void Draw(Graphics& gfx);
	void InRange(int Gx, int Gw, int Gy);
	void Move();
	void PickUp(int Gx, int Gy, bool S);

private:
	int x = 150;
	int y = 578;
	int w = 7;
	int h = 6;
	int d = 1; //1 is right, 2 is left
	int e;
	bool isFrogJumping = false;
	bool isFrogReady = true;
	bool isFrogReady2 = true;
	int RandstageFrog = 0;
	int r1Frog = 0;
	int r2Frog = 0;
	int JumpHeight = 9;
	bool FrogMoveLeft = false;
	bool FrogMoveRight = false;
	bool isInRange = false;
	bool isFrogOnHead = false;
	int FrogTempX;
};