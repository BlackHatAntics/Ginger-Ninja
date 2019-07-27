#pragma once
#include "Graphics.h"
#include "MainWindow.h"
#include "Keyboard.h"

class Ginger
{
public:
	Ginger(int in_x, int in_y, int in_speed)
	{
		x = in_x;
		y = in_y;
		speed = in_speed;
	}
	void Draw(Graphics& gfx, Color h, Color b);
	void EyeLogic();
	void Movement();

	void SetMoveRight(bool z);
	void SetMoveLeft(bool z);
	//bool GetMoveRight();
	//bool GetMoveLeft();
	//int GetSpeed();
	//int GetX();
	//int GetY();
private:
	int x;
	int y;
	int speed;
	int eye = 15;
	bool MoveRight = false;
	bool MoveLeft = false;
};