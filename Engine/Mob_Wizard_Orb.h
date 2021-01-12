#pragma once
#include "Graphics.h"

struct Orb
{
public:
	void Draw(Graphics& gfx/*, int Rx, int Ry, int Rw*/);
	void Collision(int Gx, int Gy, int Gw, bool &Colliding);
	void Death(int Gx, int Gy, int Gw, int Gds, int Gsp);
	void Spawning(int Rx, int Ry, int Rw, int Rh);
	void ShootyShootyPowPow(/*int Rx, int Ry, int Rw,*/ int Gx, int Gy, int Gw/*, int Gdx, int Gdy*/);

	//void SetActive(bool Active);
	bool GetActive();
	int GetX();
	int GetY();
	int GetW();
private:
	float x = 0;
	float y = 100;
	static const int w = 8;
	//float UpValue = 0;
	//float DownValue = 0;
	//float LeftValue = 0;
	//float RightValue = 0;
	float XValue = 0;
	float YValue = 0;
	bool active = false;
	//int PelletNumber = 0;
	int OrbStage = 0;
	//int OrbTrackingCounter = 0;
	//const int MaxSpeed = 4; //this is defined in ShootyShootyPowPow()
	//const float MaxIncrement = 0.125; //This is 1/8

//	int Direction = 1; //Whether the pellet flies left (-1) or right (1)
//	int PotentialSpeed = 50;
};