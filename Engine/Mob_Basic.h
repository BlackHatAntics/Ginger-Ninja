#pragma once
#include "Graphics.h"

class Mob
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_y, int in_Px, int in_Pw, bool in_alive);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Movement(int Gx, int Gw);
	void Aggro(int Gx, int Gy, int Gw, int Gog);
	void Death(int Gx, int Gy, int Gw, int Gds, int Gsp);

	bool GetAlive();
private:
	int x;
	int y;
	int w = 9;
	int speed = 1;
	bool aggro = false;
	bool MoveRight = false;
	bool MoveLeft = false;
	int RandStage = 0;
	int Px; //Platform x (of the platform it is standing on. This is manually determined in the Init function)
	int Pw; //Platform width
	bool alive;
};