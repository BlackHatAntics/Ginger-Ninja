#pragma once
#include "Graphics.h"

struct Orb
{
public:
	void Draw(Graphics& gfx/*, int Rx, int Ry, int Rw*/);
	void Spawning(int Rx, int Ry, int Rw, int Rh);
	void ShootyShootyPowPow(/*int Rx, int Ry, int Rw,*/ int Gx, int Gy, int Gw/*, int Gdx, int Gdy*/);

	//void SetActive(bool Active);
	bool GetActive();
	int GetX();
	int GetY();
	int GetW();
private:
	int x = 0;
	int y = 100;
	int w = 8;
	int UpValue = 0;
	int DownValue = 0;
	int LeftValue = 0;
	int RightValue = 0;
	bool active = false;
	//int PelletNumber = 0;
	int OrbStage = 0;
	int OrbSeakingCounter = 0;
//	int Direction = 1; //Whether the pellet flies left (-1) or right (1)
//	int PotentialSpeed = 50;
};