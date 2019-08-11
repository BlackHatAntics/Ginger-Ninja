#pragma once
#include "Graphics.h"

class Mob
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_y);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Movement();
private:
	int x; //Don't do this. Just have an Init call, when "Mob level 1" is activated. so have int x, int y, in the function perameters.
	int y; //This is just for testing purposes rn
	int w = 9;
};