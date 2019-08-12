#pragma once
#include "Graphics.h"

class Mob
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_y, int in_Px, int in_Pw);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Movement(int Gx, int Gy, int Gw, int Gog); //Just has Gy and Gog so it can pass it along to Aggro. Doesn't actually use it itself
	void Aggro(int Gx, int Gy, int Gw, int Gog); //Only called inside of Movement
private:
	int x; //Don't do this. Just have an Init call, when "Mob level 1" is activated. so have int x, int y, in the function perameters.
	int y; //This is just for testing purposes rn
	int w = 9;
	int speed = 1;
	bool aggro = false;
	bool MoveRight = false;
	bool MoveLeft = false;
	int RandStage = 0;
	int Px; //Platform x (of the platform you are standing on. This is manually determined in the Init function)
	int Pw; //Platform width
};