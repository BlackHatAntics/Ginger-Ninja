#pragma once
#include "Graphics.h"

class Jumper
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_Px, int in_y, int in_Pw, int in_roam = 420);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Death(int Gx, int Gy, int Gw, int Gds, int Gsp);
	void StartPoint();
	void Respawn();
	void Movement(int Gx, int Gw/*, int Gdx*/);
	void DeathAnimation(Graphics& gfx);
	//void Aggro(int Gx, int Gy, int Gw, int Gog);

	bool GetAlive();
	int GetDeathStage();
private:
	int StartPointX;
	int StartPointY;
	int x = StartPointX;
	int y = StartPointY;
	static const int w = 11;
	int Px; //Platform x (of the platform it is standing on. This is manually determined in the Init function)
	int Pw;	//Platform width
	int InitX; //Initial X position
	int roam; //how far the mob can roam from InitX. Fun fact: Jumpers move in increments of 14 (sjh + 1). So make all roam values multiples of this. And 14 is smallest possible value, unless you want it to jump straight up.
	bool alive = true;
	static const int sjh = 13; //starting jump height
	int jh = sjh; //jump height
	int RandStage = 0;
	bool isJumping = false;
	int JumpX = 0;
	bool aggro = false;
//	int EyeDirection = 1; //Determined once in Movement()
	int DeathStage = 0;
};