#pragma once
#include "Graphics.h"

class Jumper
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_y, int in_Px, int in_Pw);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Death(int Gx, int Gy, int Gw, int Gds, int Gsp);
	void StartPoint();
	void Respawn();
	void Movement(int Gx, int Gw/*, int Gdx*/);
	//void Aggro(int Gx, int Gy, int Gw, int Gog);

	bool GetAlive();
private:
	int StartPointX;
	int StartPointY;
	int x = StartPointX;
	int y = StartPointY;
	int w = 11;
	int Px; //Platform x (of the platform it is standing on. This is manually determined in the Init function)
	int Pw;	//Platform width
	bool alive = true;
	int sjh = 13; //starting jump height
	int jh = sjh; //jump height
	int RandStage = 0;
	bool isJumping = false;
	int JumpX = 0;
	bool aggro = false;
};