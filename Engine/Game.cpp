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
	gin[0].Init(50, 450 - 21 - 10, 3);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

	//Fix:
//Figure out why your WallJump takes slightly longer to activate now that you changed around the code.
//Find a solution to the issue that you will clip on a corner where a wall and ground meet if you land perfectly. (Happens rarely if wall is loaded before ground, but still happens) Honestly, fuck it, I don't give enough shits.

	//Currently working on:
//Switching screens

	//Add:
//Don't let yourself wall hop if you're falling too quickly
//Add the locked post-jump velocity, and the multi-directional air-jump
//Make switching directions delayed if in the air? (Honestly it's fancy and more realistic, but I kinda hate games that do this)
//Move all your movement code into Ginger?
//Implement the loading the next screen
//Add enemies

	//Thoughts & Ideas:
//The reason your game is so finnicky and able to break is because it's incredibly dependant on load order. Everything is calling the same vlues. Try to put all of the same shit into the same function
//Idea! You could have really unique controls, where you are locked into your previous velocity after jumping, but you have a double jump which can adjust you either up down left or right. So you get the one correction in flight path. I actually really like this idea. We'll see how it plays out in practice though.
//When you lock the velocity of the jump, if your velocity is greater than your running speed, you will lower speed by 2 until it is equal. This way if you are going super fast for whatever reason (maybe enemies will knock you back, idk) then your jump won't just make you some super-saiyan cross-map jumper. ... actually, maybe don't do this. This will go against the game's physics for a normal jump at running speed. Don't only SOMETIMES have air resistance; that's dumb.

	//Remember:
//Don't do single-pixel thick walls if they have an open edge. Otherwise you can jump into them from above/below and perform a walljump.

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
	if (wnd.kbd.KeyIsPressed(0x57) && gin[0].GetJumpisReady() == true && gin[0].OnGround()) //"w" //The !(y is greater than dy) prevents you from jumping while falling
	{
		gin[0].SetJumping(true);
		gin[0].SetJumpisReady(false); //Find a way to do this in Ginger.cpp? This is kinda shit code rn
	}
	//Removing (and re-setting) JumpLock
	if (!wnd.kbd.KeyIsPressed(0x57) && gin[0].OnGround() == true)
	{
		gin[0].SetJumpisReady(true);
	}
	else
	{
		gin[0].SetJumpisReady(false);
	}

//	if (wnd.kbd.KeyIsPressed(0x53)) //"s" //s only does something in Platform() function rn
//	{
//	}
}

void Game::Ground(int x, int y, int w)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		gfx.PutPixel(x + loopx, y, Colors::White);
	}
	for (int i = 0; i < 2; i++)
	{
		if (gin[i].GetX() < x + w && gin[i].GetX() + gin[i].GetW() > x)
		{
			if (gin[i].GetDY() + gin[i].GetW() + 1 <= y && gin[i].GetY() + gin[i].GetW() + 1 >= y)
			{
				gin[i].HitGround(x, y, w);
			}
			else if (gin[i].GetDY() - 1 >= y && gin[i].GetY() - 1 <= y)
			{
				gin[i].HitCeiling(y);
			}
		}
	}
}

void Game::Platform(int x, int y, int w)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		gfx.PutPixel(x + loopx, y, Colors::Gray);
	}
	for (int i = 0; i < 2; i++)
	{
		if (gin[i].GetX() < x + w && gin[i].GetX() + gin[i].GetW() > x && gin[i].GetDY() + gin[i].GetW() + 1 <= y && gin[i].GetY() + gin[i].GetW() + 1 >= y && !wnd.kbd.KeyIsPressed(0x53)) //pressing s lets you fall through platforms
		{
			gin[i].HitGround(x, y, w);
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
			if (gin[i].GetDX() + gin[i].GetW() <= x - 1 && gin[i].GetX() + gin[i].GetW() > x - 1)
			{
				//you hit the wall on the left side
				//gin[i].HitWall(x - gin[i].GetW() - 1, wnd.kbd.KeyIsPressed(0x57)); //HitWall needs to pass the value to WallJump, that's why you reference "w" key
				gin[i].HitWall2(x - gin[i].GetW() - 1, y, h, wnd.kbd.KeyIsPressed(0x57));
			}
			else if (gin[i].GetDX() >= x + 1 && gin[i].GetX() < x + 1)
			{
				//you hit the wall on the right side
				//gin[i].HitWall(x + 1, wnd.kbd.KeyIsPressed(0x57));
				gin[i].HitWall2(x + 1, y, h, wnd.kbd.KeyIsPressed(0x57));
			}

			//TEST: Please delete
//			if (gin[i].GetDX() + gin[i].GetW() <= x - 1)
//			{
//				gfx.PutPixel(355, 255, 255, 255, 255);
//			}
//			if (gin[i].GetX() + gin[i].GetW() > x - 1)
//			{
//				gfx.PutPixel(255, 255, 255, 255, 255);
//			}
		}
	}
}

void Game::Screens()
{
	if (screen == 0)
	{
		Screen0();
	}
	else if (screen == 1)
	{
		Screen1();
	}
	else if (screen == 2)
	{
		Screen2();
	}
}

void Game::ScreenSwitch()
{
	if (gin[0].GetX() < 0 || gin[0].GetX() > 799 - gin[0].GetW() || gin[0].GetY() < 0 || gin[0].GetY() > 599 - gin[0].GetW())
	{
		//If I had vectors, I could increment the y value as well, without it fucking up everything. Without them, I have to manually assign the value to something.
		if (screen <= 10)
		{
			if (gin[0].GetX() < 0)
			{
				screen--;
			}
			else if (gin[0].GetX() > 799 - gin[0].GetW())
			{
				screen++;
			}
		}
		else if (screen == 8000) //Make sure to keep the "else" for all additional screens
		{
			if (gin[0].GetX() < 0)
			{
				screen = 1;
			}
			else if (gin[0].GetX() > 799 - gin[0].GetW())
			{
				screen = 3;
			}
		}


		gin[0].ScreenSwitch(); //Putting ginger on opposite side of screen. Keep at the end, so they can make their checks based off of his x/y value before this changes them
	}
}

void Game::Screen0()
{
	//**RULE** Always load ground before walls UNLESS the wall is at a corner. Then you load that wall before whichever ground it's moving down from.
	//1.The reason for this is because if you are falling quickly, holding to one side, and the pixel values are well-timed, you can slip through the sides of walls at the base.
	//2.The walls are set to push you back if you are within their y values. But you were moving so fast, that your y value is outside their range this frame
	//3.You need ground to push you back into their y value, so wall can stop you from moving to the side.
	//And the reason for loading Wall before Ground on corners is because you will bonk your head when jumping up against a wall connected to ground.
	//The same issue is prevelant for if you land on ground at the right spot, and bonk your side at the edge of the wall... But it happens so rarely idgaf. If you have the option though, load the ground first here.

	//Remember not to do 1 pixel thick walls. This prevents load order issues, as well as the issue where you can jump up inside a wall then walljump.
	//Maybe split this shit up into drawing code, and logic code. //Also, maybe have this shit as an array, so you can easily set it to "Screen[3]" and back. Screen[i].ImHorny i++;

	Wall(410, 450, 0); //Setting it so you can't pass through the side of the ground (Right platform, single pixel)
	Ground(320, 530, 799 - 320); //Low
	Wall(320, 450, 80); //Lower
	Ground(0, 450, 320); //Left
	Ground(410, 450, 799 - 410); //Right
	Ground(20, 450 - 400, 120); //Cap
	Wall(320, 450, 80); //Lower
	Wall(500, 400, 40); //Stumpy
	Wall(20, 450 - 400, 400); //Left close
	Wall(110, 450 - 300, 400 - 100 - 50); //Right close
	//Wall(109, 450 - 400, 400);
	Platform(600, 375, 100);
}

void Game::Screen1()
{
	Ground(0, 530, 799);
}

void Game::Screen2()
{
}

void Game::UpdateModel()
{
	gin[0].Cheating(wnd.kbd.KeyIsPressed(VK_UP), wnd.kbd.KeyIsPressed(VK_DOWN), wnd.kbd.KeyIsPressed(VK_LEFT), wnd.kbd.KeyIsPressed(VK_RIGHT), wnd.kbd.KeyIsPressed(0x43), wnd.kbd.KeyIsPressed(VK_SPACE));
	UserMovement();
	gin[0].Delta(); //Keep before Gravity && Movement
	gin[0].Movement(wnd.kbd.KeyIsPressed(VK_SHIFT));
	gin[0].EyeLogic();
	gin[0].OnGround(); //Keep before jump, probably
	gin[0].OnWall();
	gin[0].Jump();
	gin[0].WallJump2(wnd.kbd.KeyIsPressed(0x57));
	gin[0].Gravity(); //Keep 2nd last
	//Keep last:
	Screens();
	ScreenSwitch(); //I keep this after Screens, so you don't accidentally activate a switch by jumping against a wall close to edge

}

void Game::ComposeFrame()
{
	gin[0].Draw(gfx, Colors::Orange2, Colors::Burnt);
}
