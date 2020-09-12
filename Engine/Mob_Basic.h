#pragma once
#include "Graphics.h"

class Basic
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_y, int in_Px, int in_Pw);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Movement(int Gx, int Gw);
	void Aggro(int Gx, int Gy, int Gw, int Gog);
	void Death(int Gx, int Gy, int Gw, int Gds, int Gsp);
	void StartPoint(); //Just called once in the Game initializer
	void Respawn();

	int GetStartPointX();
	int GetStartPointY();

	bool GetAlive();
private:
	int StartPointX;
	int StartPointY;
	int x /*= StartPointX*/;
	int y /*= StartPointY*/;
	int w = 9;
	int speed = 1;
	bool aggro = false;
	bool MoveRight = false;
	bool MoveLeft = false;
	int RandStage = 0;
	int Px; //Platform x (of the platform it is standing on. This is manually determined in the Init function)
	int Pw; //Platform width
	bool alive = true;
};