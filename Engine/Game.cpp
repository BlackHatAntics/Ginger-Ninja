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
//Make the screen move with you

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

	//His movement is stopped in MoveScreen()
}

void Game::MoveScreen()
{
	//Screenpoint is just where the screen is right now. Think of it as an invisible dot on the left edge of the screen. Whenever you move past the midpoint of the screen, you stop moving, 
	//and move the ScreenPoint instead. This does nothing on it's own, except you have each item's location set in accordance with the position of ScreenPoint
	//So for example you would draw EVERY item set to "x + ScreenPoint", so whenever you move the ScreenPoint, everything else moves too. Creates the illusion of your character walking

	if (gin0.GetX() + 19 > 414 && gin0.GetMoveRight() == true)
	{
		ScreenPoint += gin0.GetSpeed();
		gin0.SetMoveRight(false);
	}
	if (gin0.GetX() < 384 && gin0.GetMoveLeft() == true)
	{
		ScreenPoint -= gin0.GetSpeed();
		gin0.SetMoveLeft(false); //Stop you from moving, and will always be back on for next frame from UserMovement 
	}

	if (ScreenPoint < 0) //if it's at the left edge of the room
	{
		ScreenPoint = 0;
		gin0.SetMoveLeft(true); //Re-activates movement once you hit the edge of the room
	}
	if (ScreenPoint > RoomWidth) //if you get to the right edge of the room
	{
		ScreenPoint = RoomWidth;
		gin0.SetMoveRight(true);
	}

}

void Game::DrawBullshit()
{
	gfx.PutPixel(255 + ScreenPoint, 255, Colors::White);
}

void Game::UpdateModel()
{
	UserMovement();
	MoveScreen();
	gin0.Movement();
	gin0.EyeLogic();
}

void Game::ComposeFrame()
{
	gin0.Draw(gfx, Colors::Orange2, Colors::Pasty);
	DrawBullshit();
}
