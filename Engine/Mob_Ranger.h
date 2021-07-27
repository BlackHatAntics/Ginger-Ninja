#pragma once
#include "Graphics.h"
//#include "Mob_Ranger_Pellet.h"

class Ranger
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
	//void Shoot(int Gx, int Gy, int Gw);

	bool GetAlive();
	bool GetAggro();
	int GetX();
	int GetY();
	int GetW();
	int GetH();
	//int GetPelletSize();
	//int GetPelletNumber();

	int PelletNumber = 0; //This is here instead of Mob_Ranger_Pellet, so each Ranger has a separate set of pellets. (Also public so I can change it in Mob_Ranger_Pellet. Too lazy to re-code)
private:
	//static constexpr int PelletSize = 3;
	//Pellet pel[PelletSize];

	int StartPointX;
	int StartPointY;
	int x;
	int y;
	static const int w = 10;
	static const int h = 14;
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
	
};