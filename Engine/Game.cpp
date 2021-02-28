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
#include "time.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	srand(time(NULL));
	//gin[0].Init(200, 585 - 21, 3); //This is the proper one, for starting in Screen0. But use the other one until you're done working on the screens
	gin[0].Init(45, 60 - 21, 3);
	//gin[0].Init(705, 60 - 21, 3);
	//screen 0
	bas[7].Init(640, 420, 500, 799 - 420);
	//screen 1
	bas[8].Init(370, 0, 500, 610);
	bas[9].Init(500, 0, 500, 610);
	bas[10].Init(550, 290, 280, 383);
	jum[5].Init(300, 130, 370, 380);
	jum[6].Init(400, 290, 280, 383);
	jum[7].Init(600, 290, 280, 383);
	//screen 2
	bas[11].Init(250, 220, 260, 65);
	bas[12].Init(148, 110, 360, 90);
	bas[13].Init(249, 230, 460, 90);
	bas[14].Init(140, 100, 520, 153);
	jum[8].Init(200, 100, 520, 153);
	//screen 7
	bas[0].Init(200, 20, 205, 280);
	bas[1].Init(100, 20, 205, 280);
	bas[2].Init(700, 110, 560, 799 - 110);
	bas[3].Init(440, 200, 130, 360);
	bas[4].Init(230, 195, 440, 580 - 195);
	bas[5].Init(500, 195, 440, 580 - 195);
	bas[6].Init(710, 650, 440, 790 - 650);
	jum[0].Init(70, 20, 205, 280);
	jum[1].Init(300, 110, 560, 799 - 110);
	jum[2].Init(350, 110, 560, 799 - 110);
	jum[3].Init(480, 110, 560, 799 - 110);
	jum[4].Init(270, 20, 205, 280);
	cha[0].Init(270, 200, 130, 360);
	cha[1].Init(500, 110, 560, 799 - 110);
	ran[0].Init(320, 110, 560, 799 - 110);
	ran[1].Init(430, 195, 440, 580 - 195);
	//ran[2].Init(220, 110, 545, 799 - 110);
	wiz[0].Init(40, 20, 400, 90);
	//wiz[1].Init(420, 110, 545, 799 - 110);

	for (int i = 0; i < BasicSize; i++) //So every time you call Respawn after, you can just loop through all mobs, and call "StartPoint", instead of manually plugging in variables
	{
		bas[i].StartPoint();
	}
	for (int i = 0; i < JumperSize; i++)
	{
		jum[i].StartPoint();
	}
	for (int i = 0; i < ChargerSize; i++)
	{
		cha[i].StartPoint();
	}
	for (int i = 0; i < RangerSize; i++)
	{
		ran[i].StartPoint();
	}
	for (int i = 0; i < WizardSize; i++)
	{
		wiz[i].StartPoint();
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}


	//Currently working on:
//Making pellets shoot at the player
//Planning && drawing level layouts

	//Fix:
//Mobs vibrating when underneath you && aggro

	//Add:
//For Ranger: make it so if Gin is close, he backs up, if he's far away he walks towards him to stay in range, and if he's medium then ranger stands still
//For Ranger: change aggro so once he spots him, he can be high up or low down on platforms, and will still shoot (within reason)
//Implement a visual, so user knows when dash is currently on cooldown
//Implement the level switcher
//Add a death animation. Imperative, so your players understand what happened, and you didn't just teleport. Also want them to see the red healthbar for at least a few frames.
//Have a death animation for enemies
//Add more enemy types
//Plan out level layouts
//?Put Walls && Ground in their own class, so you can have moving platforms
//?Don't let yourself wall hop if you're falling too quickly
//?Move all your movement code into Ginger
//?Add burning via sun
//?Have your bed restore 1hp/frame

	//Thoughts & Ideas:
//Your Dash feels really lame to use. Keep it, but let the player have another way to kill enemies.
//In screen4, as part of platforming test, have a portal that lets you warp from bottom to top of screen (don't need to add new code, just let yourself fall and you auto move to top) Just draw some bs
//?Create a Mob struct, and have all the functions that are the same for every mob class be in there. Just include Mob.h in all the different mob classes, and call the functions with their own variables..... Nevermind. It would benefit me if I had tons of mobs, but I only have ~6 so it's more inconvenient.
//Is Dash method too easy? My prediction: if few mobs, too easy. if lots of mobs, really hard, and may force you to always corral the mobs. Which is anti-fun.
//The reason your game is so finnicky and able to break is because it's incredibly dependant on load order. Everything is calling the same values. Try to put all of the same shit into the same function
//1. Idea! You could have really unique controls, where you are locked into your previous velocity after jumping, but you have a double jump which can adjust you either up down left or right. So you get the one correction in flight path. I actually really like this idea. We'll see how it plays out in practice though.
//2. I've changed my mind, I won't use the fancy jump mechanics. Maybe in another game.

	//Could fix, but honestly don't care:
//Figure out why your WallJump takes slightly longer to activate now that you changed around the code.
//Find a solution to the issue that you will clip on a corner where a wall and ground meet if you land perfectly? (besides just changing the load order) (honestly the solution is just to not use 1-pixel-thick walls)
//Clean up orb code

	//Remember:
//Don't do single-pixel thick walls if they have an open edge. Otherwise you can jump into them from above/below and perform a walljump.
//You will be 1 frame late in determining when you stop colliding with a mob

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
	for (int i = 0; i < GinSize; i++)
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
	for (int i = 0; i < GinSize; i++)
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
	for (int i = 0; i < GinSize; i++)
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
		}
	}
}

void Game::Screens()
{
	//What a bunch of miserable code...
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
	else if (screen == 3)
	{
		Screen3();
	}
	else if (screen == 4)
	{
		Screen4();
	}
	else if (screen == 5)
	{
		Screen5();
	}
	else if (screen == 6)
	{
		Screen6();
	}
	else if (screen == 7)
	{
		Screen7();
	}
	else if (screen == 8)
	{
		Screen8();
	}
	else if (screen == 9)
	{
		Screen9();
	}
	else if (screen == 10)
	{
		Screen10();
	}
	else if (screen == 11)
	{
		Screen11();
	}
	else if (screen == 100)
	{
		Screen100(); //My bullshit test screen
	}
}

void Game::ScreenSwitch()
{
	
	//If I had vectors, I could increment the y value as well, without it fucking up everything. Without them, I have to manually assign the value to something.
	if (gin[0].GetX() < 0 || gin[0].GetX() > 799 - gin[0].GetW() || gin[0].GetY() < 0 || gin[0].GetY() > 599 - gin[0].GetW()) //If you off the screen in any direction
	{
		//Going down
		if (gin[0].GetY() > 599 - gin[0].GetW())
		{
			if (screen == 2)
			{
				screen++;
			}
			else if (screen == 9)
			{
				screen = 10;
			}
		}
		//Going up
		if (gin[0].GetY() < 0)
		{
			if (screen == 3)
			{
				screen--;
			}
			else if (screen == 10)
			{
				screen = 9;
			}
		}

		//Left and right
		if (screen <= 9)
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
		else if (screen > 9)
		{
			if (gin[0].GetX() < 0)
			{
				screen++;
			}
			else if (gin[0].GetX() > 799 - gin[0].GetW())
			{
				screen--;
			}
		}

		/* //All this shit down here is from before, when I had a different world layout
		//Going down
		if (gin[0].GetY() > 599 - gin[0].GetW())
		{
			if (screen == 2)
			{
				screen = 0;
			}
			else if (screen == 3)
			{
				screen = 7;
			}
			else if (screen == 9)
			{
				screen = 10;
			}
		}
		//Going up
		if (gin[0].GetY() < 0)
		{
			if (screen == 0)
			{
				screen = 2;
			}
			else if (screen == 7)
			{
				screen = 3;
			}
			else if (screen == 10)
			{
				screen = 9;
			}
		}

		//Left and right
		if (screen <= 9)
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
		else if (screen > 9)
		{
			if (gin[0].GetX() < 0)
			{
				screen++;
			}
			else if (gin[0].GetX() > 799 - gin[0].GetW())
			{
				screen--;
			}
		}
		*/

		gin[0].ScreenSwitch(); //Putting ginger on opposite side of screen. Keep at the end, so they can make their checks based off of his x/y value before this changes them
	}
}

void Game::Screen100()
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
void Game::Screen00()
{
	//Ginger HQ hospital & bed
	Ground(85, 585, 785-85); //Floor
	Ground(85, 310, 260 - 85); //Ceiling left
	Ground(370, 280, 785 - 370); //Ceiling right
	Wall(260, 310, 335-310); //Left tube
	Wall(370, 280, 335-280); //Right tube
	Wall(270, 0, 335); //Left tube inner
	Wall(360, 0, 335); //Right tube inner
	Wall(85, 310, 585-310); //Left wall
	Wall(785, 280, 585-280); //Right wall
	Ground(260, 335, 10); //Tube cap left
	Ground(360, 335, 10); //Tube cap right
	Platform(630, 500, 70); //Platform 1
	Platform(520, 430, 70); //Platform 2
	Platform(480, 370, 70); //Platform 3
	Platform(360, 440, 70); //Platform 4
	Platform(300, 400, 70); //Platform 5
	Ground(695, 575, 745 - 695); //Bed platform
	Wall(745, 555, 585 - 555); //Bed headboard left
	Wall(748, 555, 585 - 555); //Bed headboard right
	Ground(745, 555, 748 - 745); //Bed headboard cap
	Wall(695, 575, 585 - 575); //Bed end
	Platform(270, 335, 360 - 270); //Tube cover
}
void Game::Screen0()
{
	Wall(0, 0, 500); //wall left
	Ground(0, 500, 220); //ground left
	Wall(220, 500 - 70, 70); //left platform wall
	Wall(420, 500 - 70, 70); //right platform wall
	Ground(220, 500 - 70, 200); //platform top
	Ground(420, 500, 799-420); //right ground

	MobGroupBasic(7);
}
void Game::Screen1()
{
	Ground(0, 500, 610); //floor
	Wall(610, 500 - 220, 220); //floor wall right
	Ground(130, 370, 380); //2nd platform
	Wall(130, 200, 370 - 200); //2nd platform wall left
	Ground(290, 280, 383); //top platform
	Wall(290+383, 220, 60); //first step
	Ground(290 + 383, 220, 63); //first step
	Wall(736, 220-60, 60); //2nd step
	Ground(736, 160, 63); //2nd step

	MobGroupBasic(8);
	MobGroupBasic(9);
	MobGroupBasic(10);

	MobGroupJumper(5);
	MobGroupJumper(6);
	MobGroupJumper(7);
}
void Game::Screen2()
{
	Ground(0, 160, 220); //top
	Wall(0, 160, 599-160); //left border
	Ground(220, 260, 100); //platform top right
	Wall(285, 60, 200); //platform top right
	Ground(205, 60, 80); //platform top right ceiling
	Ground(110, 360, 94); //platform middle left
	Wall(110, 160, 200); //platform middle left
	Ground(230, 460, 90); //platform middle right
	Wall(320, 260, 200); //platform middle right
	Ground(100, 520, 153); //platform bottom
	Wall(253, 460, 60); //platform bottom
	Wall(100, 520, 599-520); //tube bottom right

//	Wall(220, 0, 599); //test measuring line
	
	MobGroupBasic(11);
	MobGroupBasic(12);
	MobGroupBasic(13);
	MobGroupBasic(14);

	MobGroupJumper(8);
}
void Game::Screen3()
{
	if (gin[0].GetX() < 400 || gin[0].GetY() + gin[0].GetW() > 385)
	{
		gfx.PutPixel(255, 255, 255, 255, 255);
	}

	Ground(0, 485, 500); //bottom
	Wall(0, 0, 485); //border left
	Wall(100, 0, 385); //left tube, right side
	Ground(400, 30, 799-400); //top tube, ceiling
	
	//for (int i = 0; i <= 1; i++) //do this for any corners you could fall on with a high velocity (aka, preventing you from clipping through the wall) //nevermind it doesn't work. figure this out
	//{
		Ground(100, 385, 300); //bottom tube, ceiling
		Wall(400, 30, 385 - 30); //right tube, left side
		//Ground(100, 385, 300); //bottom tube, ceiling
		//Wall(400, 30, 385 - 30); //right tube, left side
	//}

	Wall(500, 360, 485 - 360); //right tube, right side, bottom
	Wall(500, 130, 130); //right tube, right side, top
	Ground(500, 130, 299); //top tube, floor
	Ground(500, 260, 299); //middle tube, ceiling
	Ground(500, 360, 299); //middle tube, floor

//	MobGroupCharger(2);
}
void Game::Screen4()
{
}
void Game::Screen5()
{
}
void Game::Screen6()
{
	//Above ground
	Wall(620, 430, 475 - 430); //Ground wall
	Ground(0, 475, 620); //Ground
	Ground(620, 430, 799 - 620); //Ground right

	//Underground
	Wall(270, 594, 599 - 594); //Left tube
	Wall(360, 594, 599 - 594); //Right tube
	Wall(195, 555, 594 - 555); //Left first wall
	Ground(170, 555, 195 - 170); //Left first wall top
	Ground(90, 550, 170 - 90); //Left blip top
	Ground(20, 562, 90 - 20); //Left indent
	Ground(0, 553, 20); //Left exit
	Wall(90, 550, 12); //Left indent right
	Wall(20, 553, 562 - 553); //Left indent left
	Wall(170, 550, 5); //Left first blip
	Ground(195, 594, 270 - 195); //Floor Left
	Ground(360, 594, 505 - 360); //Floor Right
	Platform(270, 594, 360 - 270); //Tube cover
	Wall(220, 475, 495 - 475); //Left ceiling thing, close side
	Ground(135, 495, 220 - 135); //Left ceiling thing
	Wall(135, 495, 510 - 495); //Left ceiling thing, bottleneck right
	Ground(97, 510, 135 - 97); //Left ceiling thing
	Wall(97, 490, 510 - 490); //Left ceiling thing, bottleneck left
	Ground(0, 490, 97); //Far left ceiling
	Wall(250, 475, 525 - 475); //Middle ceiling thing, left side
	Wall(415, 475, 490 - 475); //Middle ceiling thing, right side
	Wall(345, 490, 525 - 490); //Middle ceiling thing, middle side
	Ground(250, 525, 345 - 250); //Middle ceiling thing, bottom
	Ground(345, 490, 415 - 345); //Middle ceiling thing, right
	Wall(430, 475, 565 - 475); //Stalagmite left
	Wall(455, 475, 565 - 475); //Stalagmite right
	Ground(430, 565, 455 - 430); //Stalagmite bottom
	Wall(505, 500, 594 - 500); //Right ground obstacle, left side outer
	Ground(505, 500, 540 - 505); //Right ground obstacle, left side
	Wall(540, 500, 10); //Right ground obstacle, left side inner
	Ground(540, 510, 700 - 540); //Right ground obstacle long
	Wall(700, 510, 8); //Right ground obstacle, divet left side
	Ground(700, 518, 15); //Right ground obstacle divet
	Wall(715, 475, 518 - 475); //Right ground obstacle, divet right side
	Wall(755, 475, 540 - 475); //Right ground obstacle, right side
	Ground(715, 475, 755 - 715); //Right ground obstacle right
	Ground(755, 540, 799 - 755); //Right exit
	Wall(790, 430, 495 - 430); //Right side barrier
	Ground(790, 495, 799 - 790); //Right side barrier
}
void Game::Screen7()
{
	Ground(110, 560, 799 - 110); //Ground
	Ground(600, 60, 790 - 600); //Top platform
	Wall(680, 0, 8); //Ceiling barrier
	Ground(20, 8, 680 - 20); //Ceiling barrier
	Ground(200, 130, 560 - 200); //2nd top platform
	Wall(110, 400, 560 - 400); //Left barrier bottom
	Ground(20, 400, 110 - 20); //Left barrier platform
	Wall(20, 8, 400 - 8); //Left barrier top
	Ground(300, 235, 460 - 300); //Left platform bottom
	Wall(300, 205, 235 - 205); //Left platform
	Ground(20, 205, 300 - 20); //Left platform top
	Wall(580, 380, 440 - 380); //Bottom platform
	Ground(195, 440, 580 - 195); //Bottom platform bottom
	Ground(580, 380, 650 - 580); //Bottom platform top
	Platform(270, 362, 110); //Lower platform
	Platform(500, 310, 110); //Higher platform
	Ground(650, 440, 790 - 650); //Right platform
	Wall(790, 0, 500); //Right wall
	Ground(790, 500, 799 - 790); //Right exit top barrier
//	Wall(650, 500, 560 - 500); //Bottom tiny thing
//	Ground(580, 500, 650 - 580); //Bottom tiny thing
	Ground(480, 500, 70); //Bottom tiny divide right
	Ground(280, 500, 70); //Bottom tiny divide left

	MobGroupBasic(0);
	MobGroupBasic(1);
	MobGroupBasic(2);
	MobGroupBasic(3);
	MobGroupBasic(4);
	MobGroupBasic(5);
	MobGroupBasic(6);

	MobGroupJumper(0);
	MobGroupJumper(1);
	MobGroupJumper(2);
	MobGroupJumper(3);
	MobGroupJumper(4);

	MobGroupCharger(0);
	MobGroupCharger(1);

	MobGroupRanger(0);
	MobGroupRanger(1);
	//MobGroupRanger(2);

	MobGroupWizard(0);
	//MobGroupWizard(1);
}
void Game::Screen8()
{
}
void Game::Screen9()
{
}
void Game::Screen10()
{
	//Add some decoration?
//	if (Level >= 2)
//	{
//		Show the DANGER warning;
//	}
	Ground(0, 445, 500); //Ground
	Wall(500, 345, 100); //Right wall
	Wall(355, 345, 410 - 345); //Left wall
	Ground(0, 410, 355); //Top of left exit
	Wall(440, 0, 345); //Tube left
	Wall(485, 0, 345); //tube right
	Ground(355, 345, 440 - 355); //Ceiling left
	Ground(485, 345, 500 - 485); //Ceiling right
}
void Game::Screen11()
{
	if (Level <= 1)
	{
		Ground(0, 445, 799); //Ground
		Wall(0, 0, 445); //Left wall
		Wall(799, 0, 410); //Right wall
		Ground(799, 410, 0); //1 pixel at base of right wall, to stop you from clipping
	}
}

void Game::UserCollision()
{
	//UserisColliding = false; //Since there's many different things setting UserisColliding to true, you can't just have an "else {false}". So you set it to false every frame, and if it's colliding this frame in any of the mob functions it will be true.
	//for (int i = 0; i <= BasicSize; i++)
	//{
	//	mob[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding);
	//}
//	I had to remove this ^ and cause the 1 frame delay in recognizing when you are no longer colliding for 2 reasons:
//	1. You have to make sure to put the collision test inside of Screens, or else you will be affected by every mob on every screen.
//	2. If I want to fix that issue, I would need to move the other logic code inside of Screens.
//	But I'd rather just keep everything in it's own function for simplicity, so I moved "UserisColliding = false" to the end of the function, and accepted the delay.

	if (UserisColliding && DamageLock == false && !(gin[0].GetDashStage() > 0 && gin[0].GetDashStage() <= 4) && gin[0].GetCheating() == false) //Must be touching enemy, not damaged in last ~14 frames, and not mid-dash (and not cheating)
	{ 
		UserHealth--;
		DamageLock = true; //This is just so you can't take damage every frame from just 1 hit. Gives you a small window of invulnerability.
	}
	if (DamageLock == true)
	{
		DamageLockCounter++;

		if (DamageLockCounter > 15)
		{
			DamageLockCounter = 0;
			DamageLock = false;
		}
	}

	UserisColliding = false; //Since there's many different things setting UserisColliding to true, you can't just have an "else {false}". So you set it to false every frame, and if it's colliding this frame in any of the mob functions it will be true.
}

void Game::HealthBar()
{
	//Red is always underneathe
	for (int loopx = 0; loopx < 60; loopx++)
	{
		for (int loopy = 0; loopy < 11; loopy++)
		{
			gfx.PutPixel(736 + loopx, 5 + loopy, Colors::Red);
		}
	}

	//Green is dependant on how much health you have
	if (UserHealth > 0)
	{
		for (int loopx = 0; loopx < 20; loopx++)
		{
			for (int loopy = 0; loopy < 11; loopy++)
			{
				gfx.PutPixel(736 + loopx, 5 + loopy, Colors::Green);
			}
		}
	}
	if (UserHealth > 1)
	{
		for (int loopx = 0; loopx < 20; loopx++)
		{
			for (int loopy = 0; loopy < 11; loopy++)
			{
				gfx.PutPixel(736 + 20 + loopx, 5 + loopy, Colors::Green);
			}
		}
	}
	if (UserHealth > 2)
	{
		for (int loopx = 0; loopx < 20; loopx++)
		{
			for (int loopy = 0; loopy < 11; loopy++)
			{
				gfx.PutPixel(736 + 40 + loopx, 5 + loopy, Colors::Green);
			}
		}
	}
}

void Game::MobGroupBasic(int i)
{
	//This does nothing at all, other than make your Screen functions look more clean
	if (bas[i].GetAlive())
	{
		bas[i].Aggro(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetOnGroundValue());
		bas[i].Movement(gin[0].GetX(), gin[0].GetW()); //Keep after Aggro
		bas[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement
		bas[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		bas[i].Draw(gfx);

		//mob.Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding, + i, bas[0].GetX(), bas[0].GetY(), etc. )
		//Honestly idk if I'm gonna do this/have a centralized "mob" class to pull functions from. I understand it would benefit me if I have 1000 types of mobs, but since I'm only have ~6, it's more inconvenient. 
	}
}
void Game::MobGroupJumper(int i)
{
	if (jum[i].GetAlive())
	{
//		jum[i].Aggro(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetOnGroundValue());
		jum[i].Movement(gin[0].GetX(), gin[0].GetW()/*, gin[0].GetDX()*/); //Keep after Aggro
		jum[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement
		jum[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		jum[i].Draw(gfx);
	}
}
void Game::MobGroupCharger(int i)
{
	if (cha[i].GetAlive())
	{
		cha[i].Aggro(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetOnGroundValue());
		cha[i].Movement(gin[0].GetX(), gin[0].GetW()/*, gin[0].GetDX()*/); //Keep after Aggro
		cha[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement
		cha[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		cha[i].Draw(gfx);
	}
}
void Game::MobGroupRanger(int i)
{
	if (ran[i].GetAlive())
	{
		ran[i].Aggro(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetOnGroundValue());
		ran[i].Movement(gin[0].GetX(), gin[0].GetW()/*, gin[0].GetDX()*/); //Keep after Aggro
//		ran[i].Shoot(gin[0].GetX(), gin[0].GetY(), gin[0].GetW());
//		for (int Piii = 0; Piii < RangerSize; Piii++)
//		{
//			int P = i * PelletSize + Pi;
//			pel[P].Spawning(PelletSize, Pi, ran[i].GetX(), ran[i].GetY(), ran[i].GetW(), ran[i].GetH(), ran[i].GetAggro(), gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[i].GetDX(), gin[i].GetDY());
//		}
		pel[ran[i].PelletNumber + i * PelletSize].Spawning(PelletSize, ran[i].PelletNumber, ran[i].GetX(), ran[i].GetY(), ran[i].GetW(), ran[i].GetH(), ran[i].GetAggro(), gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[i].GetDX(), gin[i].GetDY());

		ran[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement
		ran[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		ran[i].Draw(gfx);
	}

	for (int Pi = 0; Pi < PelletSize; Pi++) //this is outside of GetAlive {} bracket so that a pellet in motion will keep falling after it's ranger dies
	{
		pel[i * PelletSize + Pi].ShootyShootyPowPow(/*ran[i].GetX(), ran[i].GetY(), ran[i].GetW(), gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[i].GetDX(), gin[i].GetDY()*/);
		if (pel[i * PelletSize + Pi].GetActive() == true) //so basically this is saying each ranger has his own set of pellets, and it will only loop through his ones. ex: ranger 0 has pellets 0-7. ranger 1 has pellets 8-15, etc. 
		{
			pel[i * PelletSize + Pi].Draw(gfx); //i(ranger) * PelletSize(however many pellets are assigned to each ranger) + Pi(whatever pellet it's currently looping through here)
		}
	}
}
void Game::MobGroupWizard(int i)
{
	if (wiz[i].GetAlive())
	{
		wiz[i].Aggro(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetOnGroundValue());
		wiz[i].Movement(gin[0].GetX(), gin[0].GetW()/*, gin[0].GetDX()*/); //Keep after Aggro
//		wiz[i].Shoot(gin[0].GetX(), gin[0].GetY(), gin[0].GetW());
		orb[i].Spawning(wiz[i].GetX(), wiz[i].GetY(), wiz[i].GetW(), wiz[i].GetH());
		wiz[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement
		orb[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement
		wiz[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		orb[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());

		if (orb[i].GetActive() == true)
		{
			orb[i].ShootyShootyPowPow(/*wiz[i].GetX(), wiz[i].GetY(), wiz[i].GetW(),*/ gin[0].GetX(), gin[0].GetY(), gin[0].GetW()/*, gin[i].GetDX(), gin[i].GetDY()*/);
			if (!(orb[i].GetX() > 799 - orb[i].GetW() || orb[i].GetX() < 0 || orb[i].GetY() > 599 - orb[i].GetW() || orb[i].GetY() < 0)) //if not out of bounds, draw the orb
			{
				orb[i].Draw(gfx);
			}
		}

		wiz[i].Draw(gfx);
	}
}

void Game::UserRespawn()
{
	//This is always active, and is just determining which place you will respawn
	if (screen <= 3) //Yeah this will needlessly be called a shit-ton and isn't optimal code, but idc, it's clean.
	{
		RespawnInBed = true;
	}
	else if (screen == 10) //Just choosing if you respawn at screen 0 or screen 10. Basically if you make it to one side of the mobs, you will respawn on that side.
	{
		RespawnInBed = false;
	}

	if (wnd.kbd.KeyIsPressed(0x52)) //"R" key allows manual reset; so you don't have to actually die to respawn
	{
		UserHealth = 0;
	}

	//if you die, reset health, reset the mobs, and then respawn
	if (UserHealth == 0)
	{
		UserHealth = 3;

		for (int i = 0; i < BasicSize; i++)
		{
			bas[i].Respawn();
		}
		for (int i = 0; i < JumperSize; i++)
		{
			jum[i].Respawn();
		}
		for (int i = 0; i < ChargerSize; i++)
		{
			cha[i].Respawn();
		}
		for (int i = 0; i < RangerSize; i++)
		{
			ran[i].Respawn();
		}
		for (int i = 0; i < PelletSize * RangerSize; i++)
		{
			pel[i].Respawn();
		}
		for (int i = 0; i < WizardSize; i++)
		{
			wiz[i].Respawn();
		}
		for (int i = 0; i < WizardSize; i++)
		{
			orb[i].Respawn();
		}

		if (RespawnInBed)
		{
			screen = 0;
			gin[0].Respawn(715, 575 - 21);
		}
		else
		{
			screen = 10;
			gin[0].Respawn(420, 445 - 21);
		}
	}
}

void Game::UpdateModel()
{
	//Keep first
	gin[0].Cheating(wnd.kbd.KeyIsPressed(VK_UP), wnd.kbd.KeyIsPressed(VK_DOWN), wnd.kbd.KeyIsPressed(VK_LEFT), wnd.kbd.KeyIsPressed(VK_RIGHT), wnd.kbd.KeyIsPressed(0x43), wnd.kbd.KeyIsPressed(VK_INSERT));
	UserMovement();
	gin[0].Delta(); //Keep before Gravity && Movement
	//Keep middle?
	gin[0].Movement(wnd.kbd.KeyIsPressed(VK_SHIFT));
	gin[0].EyeLogic();
	gin[0].OnGround(); //Keep before Jump && Dash
	gin[0].OnWall(); //Keep before WallJump
	gin[0].Jump();
	gin[0].WallJump2(wnd.kbd.KeyIsPressed(0x57));
	gin[0].Dash(wnd.kbd.KeyIsPressed(VK_SPACE));
	gin[0].Gravity(); //Keep last in the movement functions
	gin[0].TheoreticalValue(); //Keep after all movement functions, but before Screens (aka, before ground/walls adjust value)
	UserCollision(); //Keep after all movement functions
	UserRespawn();
	//Keep last:
	Screens();
	ScreenSwitch(); //I keep this after Screens, so you don't accidentally activate a switch by jumping against a wall close to edge

}

void Game::ComposeFrame()
{
	gin[0].Draw(gfx, Colors::Orange2/*, Colors::Pasty*/);
	gin[0].DrawDash(gfx); //Keep after Draw()
	HealthBar(); //Keep last, just so it's always on top

//Test bullshit:
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		Sleep(400);
	}
//	gfx.PutPixel(ran[0].GetX() + ran[0].GetW() / 2 + 50, ran[0].GetY(), 255, 255, 255);
}
