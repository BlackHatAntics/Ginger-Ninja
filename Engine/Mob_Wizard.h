#pragma once
#include "Graphics.h"
//#include "Mob_Wizard_Orb.h"

class Wizard
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_Px, int in_y, int in_Pw, int in_roam = 800);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Death(int Gx, int Gy, int Gw, int Gds, int Gsp);
	void StartPoint();
	void Respawn();
	void Movement(int Gx, int Gw/*, int Gdx*/);
	void Aggro(int Gx, int Gy, int Gw, int Gog);
	void EyeLogic(int Gx, int Gy, int Gw);
	void DeathAnimation(Graphics& gfx);
	//void Shoot(int Gx, int Gy, int Gw);

	bool GetAlive();
	bool GetAggro();
	int GetX();
	int GetY();
	int GetW();
	int GetH();
	//int GetPelletSize();
	int GetDeathStage();

private:
	//static constexpr int PelletSize = 3;
	//Pellet pel[PelletSize];

	int StartPointX;
	int StartPointY;
	int x;
	int y;
	static const int w = 10;
	static const int h = 14;
	int eye = w - 4;
	int pEyeX = w - 1;
	int pEyeY = 1;
	int speed = 1;
	bool aggro = false;
	bool MoveRight = false;
	bool MoveLeft = false;
	int RandStage = 0;
	int Px; //Platform x (of the platform it is standing on. This is manually determined in the Init function)
	int Pw; //Platform width
	int InitX; //Initial X position
	int roam; //how far the mob can roam from InitX
	bool alive = true;
	//int PelletNumber = 0;
	//int PelletStage = 0;
	int DeathStage = 0;
};