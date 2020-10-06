#pragma once
#include "Graphics.h"
#include "Mob_Ranger_Pellet.h"

class Ranger
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_y, int in_Px, int in_Pw);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Death(int Gx, int Gy, int Gw, int Gds, int Gsp);
	void StartPoint();
	void Respawn();
	void Movement(int Gx, int Gw/*, int Gdx*/);
	void Aggro(int Gx, int Gy, int Gw, int Gog);
	void Shoot(int Gx, int Gy, int Gw);

	bool GetAlive();
	//int GetPelletSize();
private:
	//static constexpr int PelletSize = 3;
	//Pellet pel[PelletSize];

	int StartPointX;
	int StartPointY;
	int x;
	int y;
	int w = 11;
	int h = 15;
	int speed = 1;
	bool aggro = false;
	bool MoveRight = false;
	bool MoveLeft = false;
	int RandStage = 0;
	int Px; //Platform x (of the platform it is standing on. This is manually determined in the Init function)
	int Pw; //Platform width
	bool alive = true;
	//int PelletNumber = 0;
	//int PelletStage = 0;
};