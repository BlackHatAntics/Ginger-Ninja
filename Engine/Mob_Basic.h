#pragma once
#include "Graphics.h"

class Basic
{
public:
	void Draw(Graphics& gfx);
	void Init(int in_x, int in_Px, int in_y, int in_Pw, int in_roam = 800);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Death(int Gx, int Gy, int Gw, int Gds, int Gsp);
	void StartPoint(); //Just called once in the Game initializer
	void Respawn();
	void Movement(int Gx, int Gw);
	void Aggro(int Gx, int Gy, int Gw, int Gog);
	void DeathAnimation(Graphics& gfx);

	int GetStartPointX();
	int GetStartPointY();

	bool GetAlive();
	int GetDeathStage();
private:
	int StartPointX;
	int StartPointY;
	int x /*= StartPointX*/;
	int y /*= StartPointY*/;
	static const int w = 9;
	float speed = 1;
	bool aggro = false;
	bool MoveRight = false;
	bool MoveLeft = false;
	int RandStage = 0;
	int Px; //Platform x (of the platform it is standing on. This is manually determined in the Init function)
	int Pw; //Platform width
	int InitX; //Initial X position
	int roam; //how far the mob can roam from InitX
	bool alive = true;
	int DeathStage = 0;
};