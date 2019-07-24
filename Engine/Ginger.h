#pragma once
#include "Graphics.h"
#include "MainWindow.h"
#include "Keyboard.h"

class Ginger
{
public:
	Ginger(int in_x, int in_y)
	{
		x = in_x;
		y = in_y;
	}
	void Draw(Graphics& gfx, Color h, Color b);
	void EyeLogic();
	void Movement();

	void SetMoveRight(bool z);
	void SetMoveLeft(bool z);
private:
	int x;
	int y;
	bool MoveRight = false;
	bool MoveLeft = false;
};