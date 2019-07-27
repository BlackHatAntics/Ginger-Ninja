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
	gfx( wnd ),
	gin0(50, 500, 3)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

	//Fix:

	//Add:
//Remove screen scrolling.

void Game::UserMovement()
{
	if (wnd.kbd.KeyIsPressed(0x44)) //"d"
	{
		gin0.SetMoveRight(true);
	}
	else
	{
		gin0.SetMoveRight(false);
	}

	if (wnd.kbd.KeyIsPressed(0x41)) //"a"
	{
		gin0.SetMoveLeft(true);
	}
	else
	{
		gin0.SetMoveLeft(false);
	}
}

void Game::DrawBullshit()
{
	for (int loopx = 0; loopx <= 70; loopx++)
	{
		gfx.PutPixel(255 + loopx, 255, Colors::White);
	}
}

void Game::UpdateModel()
{
	UserMovement();
	gin0.Movement();
	gin0.EyeLogic();
}

void Game::ComposeFrame()
{
	gin0.Draw(gfx, Colors::Orange2, Colors::Pasty);
	DrawBullshit();
}
