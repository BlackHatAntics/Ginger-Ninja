/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
//	gin[0](50, 450 - 21, 3)
{
	gin[0].Init(50, 450 - 21 -10, 3);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

	//Fix:
//Stop yourself from being able to double-jump (or jump after walking off a ledge)
//Figure out why you can get up onto the platform, even though it's above your jump height

	//Add:
//Ceiling functionality
//Wall functionality
//Colour code platforms based off of whether you can pass through the bottom or not. (or just draw them thicker). But then you gotta have them act as a wall too
//?See how to call keyboard in other classes besides Game. Check the snake video

void Game::UserMovement()
{
	//Lateral movement
	if (wnd.kbd.KeyIsPressed(0x44)) //"d"
	{
		gin[0].SetMoveRight(true);
	}
	else
	{
		gin[0].SetMoveRight(false);
	}

	if (wnd.kbd.KeyIsPressed(0x41)) //"a"
	{
		gin[0].SetMoveLeft(true);
	}
	else
	{
		gin[0].SetMoveLeft(false);
	}

	//Jump
	if (wnd.kbd.KeyIsPressed(0x57) && gin[0].GetJumpLock() == false) //"w"
	{
		gin[0].SetJumping(true);
		gin[0].SetJumpLock(true); //Find a way to do this in Ginger.cpp? This is kinda shit code rn
	}
	//Removing JumpLock
	if (!wnd.kbd.KeyIsPressed(0x57) && gin[0].GetDY() == gin[0].GetY())
	{
		gin[0].SetJumpLock(false);
	}

	if (wnd.kbd.KeyIsPressed(0x53)) //"s"
	{
	}
}

void Game::Ground(int x, int y, int w)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		gfx.PutPixel(x + loopx, y, Colors::White);
	}
	for (int i = 0; i < 2; i++)
	{
		if (gin[i].GetX() < x + w && gin[i].GetX() + gin[i].GetW() > x && gin[i].GetDY() + gin[i].GetW() <= y && gin[i].GetY() + gin[i].GetW() >= y)
		{
			gin[i].HitGround(y);
			//Just temporarily writing it this way for testing purposes
			//if (gin[i].GetX() + gin[i].GetW() > x)
			//{
			//	if (gin[i].GetX() < x + w)
			//	{
			//		if (gin[i].GetDY() + gin[i].GetW() <= y)
			//		{
			//			if (gin[i].GetY() + gin[i].GetW() >= y)
			//			{
			//				gin[i].HitGround(y);
			//			}
			//		}
			//	}
			//}
		}
	}
}

void Game::Wall(int x, int y, int h)
{
	for (int loopy = 0; loopy <= h; loopy++)
	{
		gfx.PutPixel(x, y + loopy, Colors::White);
	}
	for (int i = 0; i < 2; i++)
	{
		if (gin[i].GetY() < y + h && gin[i].GetY() + gin[i].GetW() > y)
		{
			if (gin[i].GetDX() + gin[i].GetW() <= x && gin[i].GetX() + gin[i].GetW() > x)
			{
				//you hit the wall on the left side
				gin[i].HitWall(x - gin[i].GetW());
			}
			else if (gin[i].GetDX() >= x && gin[i].GetX() < x)
			{
				//you hit the wall on the right side
				gin[i].HitWall(x);
			}
		}
	}
}

void Game::Screen1()
{
	//Maybe split this shit up into drawing code, and logic code
	//Also, maybe have this shit as an array, so you can easily set it to "Screen[3]" and back
	Ground(0, 450, 320); //Left
	Ground(320, 530, 799-320); //Low
	Ground(410, 450, 799 - 410); //Right
	Wall(320, 450, 80); //The only fucking wall
	Wall(500, 400, 40); //Nevermind, I added a test wall in the middle of everything, to see if it works on both sides.
}

void Game::UpdateModel()
{

	UserMovement();
	gin[0].Delta(); //Keep before Gravity && Movement
	gin[0].Movement();
	gin[0].EyeLogic();
	gin[0].Jump();
	gin[0].Gravity(); //Keep 2nd last
	Screen1(); //Keep last
}

void Game::ComposeFrame()
{
	gin[0].Draw(gfx, Colors::Orange2, Colors::Burnt);
}
