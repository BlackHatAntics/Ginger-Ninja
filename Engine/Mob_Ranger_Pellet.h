#pragma once
#include "Graphics.h"
//#include <cmath> //I guess this is already included by default?

struct Pellet
{
public:
	void Draw(Graphics& gfx/*, int Rx, int Ry, int Rw*/);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding, int Gdx, int Gdy);
	void Spawning(int PelletSize, int & i, int Rx, int Ry, int Rw, int Rh, bool aggro, int Gx, int Gy, int Gw, int Gdx, int Gdy);
	void Delta();
	void ShootyShootyPowPow(/*int Rx, int Ry, int Rw, int Gx, int Gy, int Gw, int Gdx, int Gdy*/);
	void Respawn();

	//void SetActive(bool Active);
	bool GetActive();
private:
	int x = 0;
	int y = 100;
	static const int w = 4;
	float SpeedX = 10;
	float SpeedY = 0;
	bool active = false;
	//int PelletNumber = 0;
	int PelletStage = 0;
	int Direction = 1; //Whether the pellet flies left (-1) or right (1)
	int dx;
	int dy;
	//int PotentialSpeed = 50;
	//int MaxSpeedY = -21;
};