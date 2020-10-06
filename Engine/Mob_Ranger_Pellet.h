#pragma once
#include "Graphics.h"

struct Pellet
{
public:
	void Draw(Graphics& gfx/*, int Rx, int Ry, int Rw*/);
	void Spawning(int PelletSize, int & i);
	void ShootyShootyPowPow();

	//void SetActive(bool Active);
	bool GetActive();
private:
	int x = 0;
	int y = 100;
	int w = 5;
	bool active = false;
	//int PelletNumber = 0;
	int PelletStage = 0;
};