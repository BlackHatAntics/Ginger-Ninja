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
	bas[7].Init(640, 420, 500, 799 - 420, 140);
	//screen 1
	bas[8].Init(370, 0, 500, 610);
	bas[9].Init(500, 0, 500, 610);
	bas[10].Init(550, 290, 280, 383, 175);
	jum[5].Init(300, 130, 370, 380, 140);
	jum[6].Init(400, 290, 280, 383);
	jum[7].Init(600, 290, 280, 383);
	//screen 2
	bas[11].Init(262, 220, 260, 65);
	bas[12].Init(148, 110, 360, 94);
	bas[13].Init(249, 230, 460, 90);
	bas[14].Init(140, 100, 520, 153);
	jum[8].Init(200, 100, 520, 153);
	//screen 3
	cha[2].Init(340, 0, 485, 500);
	//screen 4
	bas[15].Init(60, 0, 260, 350, 130);
	bas[16].Init(440, 350, 360, 799 - 350);
	bas[17].Init(520, 350, 360, 799 - 350);
	bas[18].Init(610, 350, 360, 799 - 350);
	bas[19].Init(680, 350, 360, 799 - 350);
	ran[2].Init(480, 120, 180, 700 - 120, 120);
	//ran[2].Init(750, 750, 180, 49); //for testing purposes only
	ran[3].Init(315, 0, 260, 350, 90);
	//screen5
	wiz[1].Init(500, 460, 350, 100);
	//screen6
	bas[20].Init(370, 310, 250, 150, 40);
	bas[21].Init(500, 460, 250, 150);
	jum[9].Init(100, 0, 560, 370);
	jum[10].Init(300, 0, 560, 370);
	jum[11].Init(481, 381, 560, 735 - 381);
	jum[12].Init(681, 381, 560, 735 - 381);
	ran[4].Init(160, 0, 560, 370);
	ran[5].Init(541, 381, 560, 735 - 381);
	wiz[2].Init(500, 460, 350, 100);
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
//Planning && drawing level layouts

	//Fix:
//If user is holding space (charging dash) as they die, they will keep charging after they respawn. There is no blocker shutting off the space key, or needed to release it to re-enable it.
//Mobs sometimes glitch off the map??? Happens super rarely. I think it started when I implemented roaming ranges? Seen it twice with basic mob, and once with ranger. Another theory is that it happens when you reset the mobs a lot. or repeatedly die. Cause it only happens after you respawned and you first walk into a room.
//If dash puts you far enough to touch 2 walls in 1 frame, it will put you at the one that's last in load order. (If I fix it will have the same issue as Ground / Fix #2)
//If you touch 2 platforms in the same frame, one on either side of a wall, and the one on the other side of the wall is higher, you will pass through the lower one.

	//Add:
//Better mob ai (wizard & ranger & charger still just use the outdated basic_mob ai)
//For Ranger: change aggro so once he spots him, he can be high up or low down on platforms, and will still shoot (within reason)
//**Ranger charge-up animation
//Wizard charge-up animation?
//Fall speed is reduced when hugging wall?
//?Implement the level switcher //nvm, don't need this anymore
//**Add more enemy types
//**Plan out level layouts
//?Put Walls && Ground in their own class, so you can have moving platforms
//?Don't let yourself wall hop if you're falling too quickly?
//?Move all your movement code into Ginger
//?Add burning via sun
//?Have your bed restore 1hp/frame

	//Thoughts & Ideas:
//Your Dash feels really lame to use. Keep it, but let the player have another way to kill enemies. Eh, nvm, the new "hold to change dash length" actually feels pretty good
//In screen4, as part of platforming test, have a portal that lets you warp from bottom to top of screen (don't need to add new code, just let yourself fall and you auto move to top) Just draw some bs
//?Create a Mob struct, and have all the functions that are the same for every mob class be in there. Just include Mob.h in all the different mob classes, and call the functions with their own variables..... Nevermind. It would benefit me if I had tons of mobs, but I only have ~6 so it's more inconvenient.
//Is Dash method too easy? My prediction: if few mobs, too easy. if lots of mobs, really hard, and may force you to always corral the mobs. Which is anti-fun.
//The reason your game is so finnicky and able to break is because it's incredibly dependant on load order. Everything is calling the same values. Try to put all of the same shit into the same function
//1. Idea! You could have really unique controls, where you are locked into your previous velocity after jumping, but you have a double jump which can adjust you either up down left or right. So you get the one correction in flight path. I actually really like this idea. We'll see how it plays out in practice though.
//2. I've changed my mind, I won't use the fancy jump mechanics. Maybe in another game.

	//Could fix, but honestly don't care:
//Ginger code (in: jumping, gravity, and draw) is tied to !(DashStage > 0 && DashStage <= 4) instead of !isDashing. You should clean it up
//Figure out why your WallJump takes slightly longer to activate now that you changed around the code.
//Clean up orb code
//Do proper rise/run wizard eyeball tracking

	//Remember:
//Don't do single-pixel thick walls if they have an open edge. Otherwise you can jump into them from above/below and perform a walljump. (nvm doesn't work anymore?)
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

void Game::Ground(int x, int y, int w, Color c)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		gfx.PutPixel(x + loopx, y, c);
	}
	for (int i = 0; i < GinSize; i++)
	{
		if ( (tHitWall && gin[i].GetTX() <= x + w && gin[i].GetTX() + gin[i].GetW() >= x && tHitGround)
		|| (gin[i].GetHitWall() == false && gin[i].GetX() <= x + w && gin[i].GetX() + gin[i].GetW() >= x && tHitGround) )
		{
			if (gin[i].GetTY() + gin[i].GetW() + 1 == y)
			{
				gin[i].HitGround(x, y, w);
			}
			else if (gin[i].GetTY() - 1 == y)
			{
				gin[i].HitCeiling(y);
			}
		}
		/*else if (tHitWall == false && gin[i].GetX() <= x + w && gin[i].GetX() + gin[i].GetW() >= x && tHitGround) //if you've hit a wall you test via theoretical value, and if you haven't you test via the actual value
		{
			if (gin[i].GetDY() + gin[i].GetW() + 1 <= y && gin[i].GetTY() + gin[i].GetW() + 1 >= y)
			{
				gin[i].HitGround(x, y, w);
			}
			else if (gin[i].GetDY() - 1 >= y && gin[i].GetTY() - 1 <= y)
			{
				gin[i].HitCeiling(y);
			} 
			*/ /*if (gin[i].GetTY() + gin[i].GetW() + 1 == y)
			{
				gin[i].HitGround(x, y, w);
			}
			else if (gin[i].GetTY() - 1 == y)
			{
				gin[i].HitCeiling(y);
			}
		}*/
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
		//The old Platform() code
		//if (((tHitWall && gin[i].GetTX() < x + w && gin[i].GetTX() + gin[i].GetW() > x) || (gin[i].OnWall() == false && gin[i].GetX() < x + w && gin[i].GetX() + gin[i].GetW() > x)) && gin[i].GetTY() + gin[i].GetW() + 1 == y && tHitGround)
		//{
		//	gin[i].HitGround(x, y, w);
		//}

		if ( ((tHitWall && gin[i].GetTX() <= x + w && gin[i].GetTX() + gin[i].GetW() >= x && tHitGround)
			|| (gin[i].GetHitWall() == false && gin[i].GetX() <= x + w && gin[i].GetX() + gin[i].GetW() >= x && tHitGround))
			&& (gin[i].GetTY() + gin[i].GetW() + 1 == y) 
			&& !wnd.kbd.KeyIsPressed(0x53) )
		{
			gin[i].HitGround(x, y, w);
		}

		//This is the exact code in Ground(). Only here for testing purposes
		//if ((tHitWall && gin[i].GetTX() <= x + w && gin[i].GetTX() + gin[i].GetW() >= x && tHitGround)
		//	|| (gin[i].GetHitWall() == false && gin[i].GetX() <= x + w && gin[i].GetX() + gin[i].GetW() >= x && tHitGround))
		//{
		//	if (gin[i].GetTY() + gin[i].GetW() + 1 == y)
		//	{
		//		gin[i].HitGround(x, y, w);
		//	}
		//}
	}
}

void Game::Wall(int x, int y, int h, Color c)
{
	for (int loopy = 0; loopy <= h; loopy++)
	{
		gfx.PutPixel(x, y + loopy, c);
	}
	for (int i = 0; i < GinSize; i++)
	{
		if (tHitGround && gin[i].GetTY() <= y + h && gin[i].GetTY() + gin[i].GetW() >= y && tHitWall)
		{
			if (/*(gin[i].GetDX() + gin[i].GetW() <= x - 1 && gin[i].GetX() + gin[i].GetW() > x - 1) ||*/ (gin[i].GetTX() + gin[i].GetW() == x - 1)) //original wall test, or it can be right beside it and have theoretically already hit it
			{
				//you hit the wall on the left side
				//gin[i].HitWall(x - gin[i].GetW() - 1, wnd.kbd.KeyIsPressed(0x57)); 
				gin[i].HitWall2(x - gin[i].GetW() - 1, y, h, wnd.kbd.KeyIsPressed(0x57)); //HitWall needs to pass the value to WallJump, that's why you reference "w" key
			}
			else if (/*(gin[i].GetDX() >= x + 1 && gin[i].GetX() < x + 1) ||*/ (gin[i].GetTX() == x + 1))
			{
				//you hit the wall on the right side
				//gin[i].HitWall(x + 1, wnd.kbd.KeyIsPressed(0x57));
				gin[i].HitWall2(x + 1, y, h, wnd.kbd.KeyIsPressed(0x57));
			}
		}
		else if (tHitGround == false && gin[i].GetY() <= y + h && gin[i].GetY() + gin[i].GetW() >= y && tHitWall)
		{
			if (gin[i].GetDX() + gin[i].GetW() <= x - 1 && gin[i].GetX() + gin[i].GetW() > x - 1)
			{
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

void Game::GroundPre(int x, int y, int w)
{
	for (int i = 0; i < GinSize; i++)
	{
		if ((gin[i].GetX() <= x + w && gin[i].GetX() + gin[i].GetW() >= x) || (gin[i].GetTX() <= x + w && gin[i].GetTX() + gin[i].GetW() >= x)) //within left/right bounds of the platform. TX is for if you hit a wall already this frame and it adjusted your position.
		{
			//have crossed past the platform && either haven't already hit a ground yet this frame, or you have hit one and this one is closer. (So if you travel through multiple, you will hit the one on top. and load order won't matter)
			if ((gin[i].GetDY() + gin[i].GetW() + 1 <= y && gin[i].GetY() + gin[i].GetW() + 1 >= y) && (tHitGround == false || (tHitGround == true && /*y - gin[i].GetDY() < gin[i].GetTY() - gin[i].GetDY()*/ y < gin[i].GetTY() )))
			{
				gin[i].HitGroundPre(y);
				tHitGround = true; //reset to false each frame in Screens()
			}
			else if ((gin[i].GetDY() - 1 >= y && gin[i].GetY() - 1 <= y) && (tHitGround == false || (tHitGround == true && /*gin[i].GetDY() - y < gin[i].GetDY() - gin[i].GetTY()*/ y > gin[i].GetTY() )))
			{
				gin[i].HitCeilingPre(y);
				tHitGround = true;
			}
		}
	}
}

void Game::WallPre(int x, int y, int h)
{
	for (int i = 0; i < GinSize; i++)
	{
		if ((gin[i].GetY() <= y + h && gin[i].GetY() + gin[i].GetW() >= y) || (gin[i].GetTY() <= y + h && gin[i].GetTY() + gin[i].GetW() >= y))
		{
			if (gin[i].GetDX() + gin[i].GetW() <= x - 1 && gin[i].GetX() + gin[i].GetW() > x - 1)
			{
				//you hit the wall on the left side
				gin[i].HitWallPre(x - gin[i].GetW() - 1);
				tHitWall = true;
			}
			else if (gin[i].GetDX() >= x + 1 && gin[i].GetX() < x + 1)
			{
				//you hit the wall on the right side
				gin[i].HitWallPre(x + 1);
				tHitWall = true;
			}
		}
	}
}

void Game::PlatformPre(int x, int y, int w)
{
	for (int i = 0; i < GinSize; i++)
	{
		//This is the old code for PlatformPre
		//if (gin[i].GetX() < x + w && gin[i].GetX() + gin[i].GetW() > x && gin[i].GetDY() + gin[i].GetW() + 1 <= y && gin[i].GetY() + gin[i].GetW() + 1 >= y && !wnd.kbd.KeyIsPressed(0x53) //pressing s lets you fall through platforms
		//	&& (tHitGround == false || (tHitGround == true && y - gin[i].GetDY() < gin[i].GetTY() - gin[i].GetDY() )))
		//{
		//	gin[i].HitGroundPre(y);
		//	tHitGround = true;
		//}

		if ( ((gin[i].GetX() <= x + w && gin[i].GetX() + gin[i].GetW() >= x) || (gin[i].GetTX() <= x + w && gin[i].GetTX() + gin[i].GetW() >= x))
			&& ((gin[i].GetDY() + gin[i].GetW() + 1 <= y && gin[i].GetY() + gin[i].GetW() + 1 >= y) && (tHitGround == false || (tHitGround == true && y < gin[i].GetTY())))
			&& !wnd.kbd.KeyIsPressed(0x53) )
		{
			gin[i].HitGroundPre(y);
			tHitGround = true;
		}

		//this is exact code in GroundPre(). Put here only for testing purposes
		//if ((gin[i].GetX() <= x + w && gin[i].GetX() + gin[i].GetW() >= x) || (gin[i].GetTX() <= x + w && gin[i].GetTX() + gin[i].GetW() >= x)) //within left/right bounds of the platform. TX is for if you hit a wall already this frame and it adjusted your position.
		//{
		//	//have crossed past the platform && either haven't already hit a ground yet this frame, or you have hit one and this one is closer. (So if you travel through multiple, you will hit the one on top. and load order won't matter)
		//	if ((gin[i].GetDY() + gin[i].GetW() + 1 <= y && gin[i].GetY() + gin[i].GetW() + 1 >= y) && (tHitGround == false || (tHitGround == true && /*y - gin[i].GetDY() < gin[i].GetTY() - gin[i].GetDY()*/ y < gin[i].GetTY())))
		//	{
		//		gin[i].HitGroundPre(y);
		//		tHitGround = true; //reset to false each frame in Screens()
		//	}
		//}

	}
}

void Game::Screens()
{
	//resetting all the GroundPre and WallPre interactions for next frame
	tHitWall = false; //theoretically hit a wall
	tHitGround = false; //theoretically hit the ground
//	tHitCeiling = false; //theoretically hit the ceiling

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
			if (screen == 2 || screen == 5)
			{
				screen++;
			}
			else if (screen == 9)
			{
				screen = 10;
			}
			else if (screen == 7)
			{
				screen--;
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
			else if (screen == 6)
			{
				screen++;
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

	WallPre(410, 450, 0); //Setting it so you can't pass through the side of the ground (Right platform, single pixel)
	GroundPre(320, 530, 799 - 320); //Low
	WallPre(320, 450, 80); //Lower
	GroundPre(0, 450, 320); //Left
	GroundPre(410, 450, 799 - 410); //Right
	GroundPre(20, 450 - 400, 120); //Cap
	WallPre(320, 450, 80); //Lower
	WallPre(500, 400, 40); //Stumpy
	WallPre(20, 450 - 400, 400); //Left close
	WallPre(110, 450 - 300, 400 - 100 - 50); //Right close
	//WallPre(109, 450 - 400, 400);
	PlatformPre(600, 375, 100);

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
	WallPre(0, 0, 500); //wall left
	GroundPre(0, 500, 220); //ground left
	WallPre(220, 500 - 70, 70); //left platform wall
	WallPre(420, 500 - 70, 70); //right platform wall
	GroundPre(220, 500 - 70, 200); //platform top
	GroundPre(420, 500, 799 - 420); //right ground

	Wall(0, 0, 500); //wall left
	Wall(220, 500 - 70, 70); //left platform wall
	Wall(420, 500 - 70, 70); //right platform wall
	Ground(0, 500, 220); //ground left
	Ground(220, 500 - 70, 200); //platform top
	Ground(420, 500, 799-420); //right ground

	MobGroupBasic(7);
}
void Game::Screen1()
{
	GroundPre(0, 500, 610); //floor
	WallPre(610, 500 - 220, 220); //floor wall right
	GroundPre(130, 370, 380); //2nd platform
	WallPre(130, 200, 370 - 200); //2nd platform wall left
	GroundPre(290, 280, 383); //top platform
	//GroundPre(260, 280, 383 + 30); //top platform
	WallPre(290 + 383, 220, 60); //first step
	GroundPre(290 + 383, 220, 63); //first step
	WallPre(736, 220 - 60, 60); //2nd step
	GroundPre(736, 160, 63); //2nd step

	Wall(610, 500 - 220, 220); //floor wall right
	Wall(130, 200, 370 - 200); //2nd platform wall left
	Wall(290 + 383, 220, 60); //first step
	Wall(736, 220 - 60, 60); //2nd step
	Ground(0, 500, 610); //floor
	Ground(130, 370, 380); //2nd platform
	Ground(290, 280, 383); //top platform
	Ground(290 + 383, 220, 63); //first step
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
	GroundPre(0, 160, 205); //top
	WallPre(0, 160, 599 - 160); //left border
	GroundPre(205, 260, 115); //platform top right
	WallPre(285, 60, 200); //platform top right
	GroundPre(205, 60, 80); //platform top right ceiling
	GroundPre(110, 360, 94); //platform middle left
	WallPre(110, 160, 200); //platform middle left
	GroundPre(230, 460, 90); //platform middle right
	WallPre(320, 260, 200); //platform middle right
	GroundPre(100, 520, 153); //platform bottom
	WallPre(253, 460, 60); //platform bottom
	WallPre(100, 520, 599 - 520); //tube bottom right

	Wall(0, 160, 599 - 160); //left border
	Wall(285, 60, 200); //platform top right
	Wall(110, 160, 200); //platform middle left
	Wall(320, 260, 200); //platform middle right
	Wall(253, 460, 60); //platform bottom
	Wall(100, 520, 599 - 520); //tube bottom right
	Ground(0, 160, 205); //top
	Ground(205, 260, 115); //platform top right
	Ground(205, 60, 80); //platform top right ceiling
	Ground(110, 360, 94); //platform middle left
	Ground(230, 460, 90); //platform middle right
	Ground(100, 520, 153); //platform bottom

//	Wall(220, 0, 599); //test measuring line
	
	MobGroupBasic(11);
	//MobGroupBasic(12);
	MobGroupBasic(13);
	MobGroupBasic(14);

	MobGroupJumper(8);

	if (checkpoint < 1)
	{
		Checkpoint(150, 160);
	}
}
void Game::Screen3()
{
	//okay so the issue with falling through ground is created because if it interacts with a GroundPre(), it changes the theoretical y to be ontop of the platform... 
	//...but if it interacts with an ADDITIONAL ground function (aka, they are close together, and he was traveling quickly enough to pass through both in one frame)
	//...then it puts him at the y value of the last ground he interacted with; not the one that he would have directly hit
	//
	//So my line of thinking is that I need to run a check for which ground is closest to his DY.
	//Perhaps I add "if" tHitGround (if he's already passed through a platform) then y - DY < ty - DY
	//aka, the distance between this current platform must be less than that of the previous platform he just sent his y value to.
	//this way he can pass through as many grounds as he wants in a frame, and he will always end up at the one that is ontop / closest to his starting fall position.
	//obviously do the reverse function for ceiling, and do this with x for walls as well.

	//*** okay new issue. when you pass by the platform on your way down, you hit the platform, register tHitGround, then have a ty value that is before the ground you're trying to land on.


	//for testing purposes:
	//if (gin[0].GetY() + gin[0].GetW() + 1 >= 385)
	//{
	//	gfx.PutPixel(255, 255, 255, 255, 255);
	//}


	PlatformPre(400, 360, 20); //platform, right tube
	GroundPre(0, 485, 500); //bottom
	GroundPre(400, 30, 799 - 400); //top tube, ceiling
	GroundPre(100, 385, 300); //bottom tube, ceiling
	GroundPre(500, 130, 299); //top tube, floor
	GroundPre(500, 260, 299); //middle tube, ceiling
	GroundPre(500, 360, 299); //middle tube, floor
	WallPre(400, 30, 385 - 30); //right tube, left side
	WallPre(0, 0, 485); //border left
	WallPre(100, 0, 385); //left tube, right side
	WallPre(500, 360, 485 - 360); //right tube, right side, bottom
	WallPre(500, 130, 130); //right tube, right side, top

	Wall(400, 30, 385 - 30); //right tube, left side
	Wall(0, 0, 485); //border left
	Wall(100, 0, 385); //left tube, right side
	Wall(500, 360, 485 - 360); //right tube, right side, bottom
	Wall(500, 130, 130); //right tube, right side, top
	Platform(400, 360, 20); //platform, right tube
	Ground(0, 485, 500); //bottom
	Ground(400, 30, 799-400); //top tube, ceiling
	Ground(100, 385, 300); //bottom tube, ceiling
	Ground(500, 130, 299); //top tube, floor
	Ground(500, 260, 299); //middle tube, ceiling
	Ground(500, 360, 299); //middle tube, floor

	MobGroupCharger(2);
}
void Game::Screen4()
{
	WallPre(120, 130, 50); //top platform, left
	WallPre(350, 260, 100); //middle tube
	WallPre(700, 30, 230); //right
	WallPre(0, 130, 130); //left
	PlatformPre(585, 180, 85);
	GroundPre(0, 30, 700); //ceiling
	GroundPre(0, 130, 120); //top tube, floor
	GroundPre(120, 180, 585 - 120); //top platform
	GroundPre(585 + 85, 180, 30); //top platform, small bit, right side
	GroundPre(350 + 70, 260, 700 - 350 - 70); //lower platform
	GroundPre(0, 260, 350); //middle tube, ceiling
	GroundPre(0, 360, 799); //floor

	Wall(120, 130, 50); //top platform, left
	Wall(350, 260, 100); //middle tube
	Wall(700, 30, 230); //right
	Wall(0, 130, 130); //left
	Platform(585, 180, 85);
	Ground(0, 30, 700); //ceiling
	Ground(0, 130, 120); //top tube, floor
	Ground(120, 180, 585 - 120); //top platform
	Ground(585 + 85, 180, 30); //top platform, small bit, right side
	Ground(350 + 70, 260, 700 - 350 - 70); //lower platform
	Ground(0, 260, 350); //middle tube, ceiling
	Ground(0, 360, 799); //floor

	MobGroupRanger(2);
	MobGroupRanger(3);

	MobGroupBasic(15);
	//MobGroupBasic(16);
	MobGroupBasic(17);
	MobGroupBasic(18);
	MobGroupBasic(19);

	if (checkpoint < 2)
	{
		Checkpoint(90, 130);
	}
}
void Game::Screen5()
{
	WallPre(70, 337, 597 - 337); //left side tube
	WallPre(124, 337, 543 - 337); //right side tube
	WallPre(282, 244, 40); //hovering wall
	WallPre(670, 385, 568 - 385); //bottom right ledge
	WallPre(799, 0, 385); //right border
	WallPre(799 - 50, 385, 597 - 385); //corner ledge tube, right side
	WallPre(720, 385, 568 - 385); //corner ledge tube, left side
	WallPre(400, 568, 597 - 568); //ground
	WallPre(429, 597, 2); //bottom tube right side pixels
	GroundPre(0, 360, 70); //left of tube
	GroundPre(124, 360, 61); //right of tube
	GroundPre(70, 337, 0); //pixel at top left of tube
	GroundPre(124, 337, 0); //pixel at top right of tube
	GroundPre(124, 543, 0); //pixel at bottom right of tube
	GroundPre(400, 568, 320); //ground (raised layer)
	GroundPre(429, 597, 749 - 429); //ground, right
	GroundPre(70, 597, 330); //ground, left
	GroundPre(312, 472, 50); //low platform
	GroundPre(400, 404, 7); //small platform 1
	GroundPre(321, 342, 7); //small platform 2
	PlatformPre(350, 205, 50); //top platform
	GroundPre(431, 205, 7); //small top platform 1
	GroundPre(470, 215, 7); //small top platform 2
	GroundPre(520, 208, 7); //small top platform 3
	GroundPre(560, 178, 7); //small top platform 4
	GroundPre(670, 385, 50); //corner ledge (left)
	GroundPre(799 - 50, 385, 50); //corner ledge (right)

	Wall(70, 337, 597-337); //left side tube
	Wall(124, 337, 543 - 337); //right side tube
	Wall(282, 244, 40); //hovering wall
	Wall(670, 385, 568 - 385); //bottom right ledge
	Wall(799, 0, 385); //right border
	Wall(799-50, 385, 597-385); //corner ledge tube, right side
	Wall(720, 385, 568-385); //corner ledge tube, left side
	Wall(400, 568, 597-568); //ground
	Wall(429, 597, 2); //bottom tube right side pixels
	Ground(0, 360, 70); //left of tube
	Ground(124, 360, 61); //right of tube
	Ground(70, 337, 0); //pixel at top left of tube
	Ground(124, 337, 0); //pixel at top right of tube
	Ground(124, 543, 0); //pixel at bottom right of tube
	Ground(400, 568, 320); //ground (raised layer)
	Ground(429, 597, 749-429); //ground, right
	Ground(70, 597, 330); //ground, left
	Ground(312, 472, 50); //low platform
	Ground(400, 404, 7); //small platform 1
	Ground(321, 342, 7); //small platform 2
	Platform(350, 205, 50); //top platform
	Ground(431, 205, 7); //small top platform 1
	Ground(470, 215, 7); //small top platform 2
	Ground(520, 208, 7); //small top platform 3
	Ground(560, 178, 7); //small top platform 4
	Ground(670, 385, 50); //corner ledge (left)
	Ground(799-50, 385, 50); //corner ledge (right)



	//MobGroupWizard(1);
}
void Game::Screen6()
{
}
void Game::Screen7()
{
	GroundPre(110, 560, 799 - 110); //Ground
	GroundPre(600, 60, 790 - 600); //Top platform
	WallPre(680, 0, 8); //Ceiling barrier
	GroundPre(20, 8, 680 - 20); //Ceiling barrier
	GroundPre(200, 130, 560 - 200); //2nd top platform
	WallPre(110, 400, 560 - 400); //Left barrier bottom
	GroundPre(20, 400, 110 - 20); //Left barrier platform
	WallPre(20, 8, 400 - 8); //Left barrier top
	GroundPre(300, 235, 460 - 300); //Left platform bottom
	WallPre(300, 205, 235 - 205); //Left platform
	GroundPre(20, 205, 300 - 20); //Left platform top
	WallPre(580, 380, 440 - 380); //Bottom platform
	GroundPre(195, 440, 580 - 195); //Bottom platform bottom
	GroundPre(580, 380, 650 - 580); //Bottom platform top
	PlatformPre(270, 362, 110); //Lower platform
	PlatformPre(500, 310, 110); //Higher platform
	GroundPre(650, 440, 790 - 650); //Right platform
	WallPre(790, 0, 500); //Right wall
	GroundPre(790, 500, 799 - 790); //Right exit top barrier
//	WallPre(650, 500, 560 - 500); //Bottom tiny thing
//	GroundPre(580, 500, 650 - 580); //Bottom tiny thing
	GroundPre(480, 500, 70); //Bottom tiny divide right
	GroundPre(280, 500, 70); //Bottom tiny divide left

	Wall(680, 0, 8); //Ceiling barrier
	Wall(110, 400, 560 - 400); //Left barrier bottom
	Wall(20, 8, 400 - 8); //Left barrier top
	Wall(300, 205, 235 - 205); //Left platform
	Wall(580, 380, 440 - 380); //Bottom platform
	Wall(790, 0, 500); //Right wall
	Ground(110, 560, 799 - 110); //Ground
	Ground(600, 60, 790 - 600); //Top platform
	Ground(20, 8, 680 - 20); //Ceiling barrier
	Ground(200, 130, 560 - 200); //2nd top platform
	Ground(20, 400, 110 - 20); //Left barrier platform
	Ground(300, 235, 460 - 300); //Left platform bottom
	Ground(20, 205, 300 - 20); //Left platform top
	Ground(195, 440, 580 - 195); //Bottom platform bottom
	Ground(580, 380, 650 - 580); //Bottom platform top
	Platform(270, 362, 110); //Lower platform
	Platform(500, 310, 110); //Higher platform
	Ground(650, 440, 790 - 650); //Right platform
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
	//for testing purposes:
	//if (gin[0].GetY() - 1 <= 510)
	//{
	//	gfx.PutPixel(255, 255, 255, 255, 255);
	//}

	//Above ground
	WallPre(620, 430, 475 - 430); //Ground wall
	GroundPre(0, 475, 620); //Ground
	GroundPre(620, 430, 799 - 620); //Ground right
	//Underground
	WallPre(270, 594, 599 - 594); //Left tube
	WallPre(360, 594, 599 - 594); //Right tube
	WallPre(195, 555, 594 - 555); //Left first wall
	GroundPre(170, 555, 195 - 170); //Left first wall top
	GroundPre(90, 550, 170 - 90); //Left blip top
	GroundPre(20, 562, 90 - 20); //Left indent
	GroundPre(0, 553, 20); //Left exit
	WallPre(90, 550, 12); //Left indent right
	WallPre(20, 553, 562 - 553); //Left indent left
	WallPre(170, 550, 5); //Left first blip
	GroundPre(195, 594, 270 - 195); //Floor Left
	GroundPre(360, 594, 505 - 360); //Floor Right
	PlatformPre(270, 594, 360 - 270); //Tube cover
	WallPre(220, 475, 495 - 475); //Left ceiling thing, close side
	GroundPre(135, 495, 220 - 135); //Left ceiling thing
	WallPre(135, 495, 510 - 495); //Left ceiling thing, bottleneck right
	GroundPre(97, 510, 135 - 97); //Left ceiling thing			//////////////////////////////
	WallPre(97, 490, 510 - 490); //Left ceiling thing, bottleneck left
	GroundPre(0, 490, 97); //Far left ceiling
	WallPre(250, 475, 525 - 475); //Middle ceiling thing, left side
	WallPre(415, 475, 490 - 475); //Middle ceiling thing, right side
	WallPre(345, 490, 525 - 490); //Middle ceiling thing, middle side
	GroundPre(250, 525, 345 - 250); //Middle ceiling thing, bottom
	GroundPre(345, 490, 415 - 345); //Middle ceiling thing, right
	WallPre(430, 475, 565 - 475); //Stalagmite left
	WallPre(455, 475, 565 - 475); //Stalagmite right
	GroundPre(430, 565, 455 - 430); //Stalagmite bottom
	WallPre(505, 500, 594 - 500); //Right ground obstacle, left side outer
	GroundPre(505, 500, 540 - 505); //Right ground obstacle, left side
	WallPre(540, 500, 10); //Right ground obstacle, left side inner
	GroundPre(540, 510, 700 - 540); //Right ground obstacle long
	WallPre(700, 510, 8); //Right ground obstacle, divet left side
	GroundPre(700, 518, 15); //Right ground obstacle divet
	WallPre(715, 475, 518 - 475); //Right ground obstacle, divet right side
	WallPre(755, 475, 540 - 475); //Right ground obstacle, right side
	GroundPre(715, 475, 755 - 715); //Right ground obstacle right
	GroundPre(755, 540, 799 - 755); //Right exit
	WallPre(790, 430, 495 - 430); //Right side barrier
	GroundPre(790, 495, 799 - 790); //Right side barrier

	//Above ground
	Wall(620, 430, 475 - 430); //Ground wall
	Ground(0, 475, 620); //Ground
	Ground(620, 430, 799 - 620); //Ground right
	//Underground
	Wall(270, 594, 599 - 594); //Left tube
	Wall(360, 594, 599 - 594); //Right tube
	Wall(195, 555, 594 - 555); //Left first wall
	Wall(90, 550, 12); //Left indent right
	Wall(20, 553, 562 - 553); //Left indent left
	Wall(170, 550, 5); //Left first blip
	Wall(220, 475, 495 - 475); //Left ceiling thing, close side
	Wall(135, 495, 510 - 495); //Left ceiling thing, bottleneck right
	Wall(97, 490, 510 - 490); //Left ceiling thing, bottleneck left
	Wall(250, 475, 525 - 475); //Middle ceiling thing, left side
	Wall(415, 475, 490 - 475); //Middle ceiling thing, right side
	Wall(345, 490, 525 - 490); //Middle ceiling thing, middle side
	Wall(430, 475, 565 - 475); //Stalagmite left
	Wall(455, 475, 565 - 475); //Stalagmite right
	Wall(505, 500, 594 - 500); //Right ground obstacle, left side outer
	Wall(540, 500, 10); //Right ground obstacle, left side inner
	Wall(700, 510, 8); //Right ground obstacle, divet left side
	Wall(715, 475, 518 - 475); //Right ground obstacle, divet right side
	Wall(755, 475, 540 - 475); //Right ground obstacle, right side
	Wall(790, 430, 495 - 430); //Right side barrier
	Ground(170, 555, 195 - 170); //Left first wall top
	Ground(90, 550, 170 - 90); //Left blip top
	Ground(20, 562, 90 - 20); //Left indent
	Ground(0, 553, 20); //Left exit
	Ground(195, 594, 270 - 195); //Floor Left
	Ground(360, 594, 505 - 360); //Floor Right
	Platform(270, 594, 360 - 270); //Tube cover
	Ground(135, 495, 220 - 135); //Left ceiling thing
	Ground(97, 510, 135 - 97); //Left ceiling thing			////////////////////////////
	Ground(0, 490, 97); //Far left ceiling
	Ground(250, 525, 345 - 250); //Middle ceiling thing, bottom
	Ground(345, 490, 415 - 345); //Middle ceiling thing, right
	Ground(430, 565, 455 - 430); //Stalagmite bottom
	Ground(505, 500, 540 - 505); //Right ground obstacle, left side
	Ground(540, 510, 700 - 540); //Right ground obstacle long
	Ground(700, 518, 15); //Right ground obstacle divet
	Ground(715, 475, 755 - 715); //Right ground obstacle right
	Ground(755, 540, 799 - 755); //Right exit
	Ground(790, 495, 799 - 790); //Right side barrier
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
	//if (Level <= 1)
	//{
		Ground(0, 445, 799); //Ground
		Wall(0, 0, 445); //Left wall
		Wall(799, 0, 410); //Right wall
		Ground(799, 410, 0); //1 pixel at base of right wall, to stop you from clipping
	//}
}
void Game::Screen19()
{
	WallPre(110, 360, 60); //left platform
	WallPre(0, 360, 200); //left wall
	WallPre(735, 190, 560 - 190); //right wall, lower
	WallPre(799, 0, 190); //right wall, higher
	WallPre(770, 0, 155); //right tube, left side

	WallPre(381, 530, 30); //dinky barrier, right side
	WallPre(370, 530, 30); //dinky barrier, left side

	WallPre(460, 210, 210); //middle/main platform divider
	WallPre(560, 350, 140); //bottom platform
	WallPre(310, 250, 170); //middle/main platform left side
	WallPre(196, 420, 70); //rectangle platform left
	WallPre(196 + 25, 420, 70); //rectangle platform right
	WallPre(650, 315, 490 - 315); //floating wall bottom right
	GroundPre(0, 360, 110); //far left platform
	GroundPre(170, 300, 75); //left platform, floating
	GroundPre(0, 560, 735); //ground
	GroundPre(650, 190, 149); //far right platform
	GroundPre(370, 530, 11); //dinky barrier, top
	GroundPre(310, 250, 300); //middle/main platform
	GroundPre(450, 210, 20); //middle/main platform divider top
	GroundPre(460, 350, 100); //bottom platform, tucked away
	GroundPre(196, 420, 25); //rectangle platform top
	GroundPre(196, 490, 25); //rectangle platform bottom
	GroundPre(770, 155, 0); //right tube, left side, single pixel

	Wall(110, 360, 60); //left platform
	Wall(0, 360, 200); //left wall
	Wall(735, 190, 560 - 190); //right wall, lower
	Wall(799, 0, 190); //right wall, higher
	Wall(770, 0, 155); //right tube, left side

	Wall(381, 530, 30); //dinky barrier, right side
	Wall(370, 530, 30); //dinky barrier, left side

	Wall(460, 210, 210); //middle/main platform divider
	Wall(560, 350, 140); //bottom platform
	Wall(310, 250, 170); //middle/main platform left side
	Wall(196, 420, 70); //rectangle platform left
	Wall(196 + 25, 420, 70); //rectangle platform right
	Wall(650, 315, 490 - 315); //floating wall bottom right
	Ground(0, 360, 110); //far left platform
	Ground(170, 300, 75); //left platform, floating
	Ground(0, 560, 735); //ground
	Ground(650, 190, 149); //far right platform
	Ground(370, 530, 11); //dinky barrier, top
	Ground(310, 250, 300); //middle/main platform
	Ground(450, 210, 20); //middle/main platform divider top
	Ground(460, 350, 100); //bottom platform, tucked away
	Ground(196, 420, 25); //rectangle platform top
	Ground(196, 490, 25); //rectangle platform bottom
	Ground(770, 155, 0); //right tube, left side, single pixel

	MobGroupBasic(20);
	MobGroupBasic(21);

	MobGroupJumper(9);
	MobGroupJumper(10);
	MobGroupJumper(11);
	MobGroupJumper(12);

	MobGroupRanger(4);
	MobGroupRanger(5);

	MobGroupWizard(2);

	//creating the barrier that disappears once you kill all the mobs
	bool AllDead = //if even one of the bools return false, the outcome is false. Every single bool has to be true for AllDead to return true.
		!bas[20].GetAlive()
		&& !bas[21].GetAlive()
		&& !jum[9].GetAlive()
		&& !jum[10].GetAlive()
		&& !jum[11].GetAlive()
		&& !jum[12].GetAlive()
		&& !ran[4].GetAlive()
		&& !ran[5].GetAlive()
		&& !wiz[1].GetAlive();

	if (AllDead == false)
	{
		GroundPre(771, 100, 27);
		Ground(771, 100, 27, Colors::Red); //thank god for optional function variables
	}

	if (checkpoint < 3)
	{
		Checkpoint(75, 360);
	}
}
void Game::Screen20()
{
	WallPre(100, 337, 23); //left side
	WallPre(470, 337, 23); //right side
	GroundPre(0, 360, 100); //left
	GroundPre(100, 337, 370); //middle
	GroundPre(470, 360, 799 - 470); //right

	Wall(100, 337, 23); //left side
	Wall(470, 337, 23); //right side
	Ground(0, 360, 100); //left
	Ground(100, 337, 370); //middle
	Ground(470, 360, 799 - 470); //right
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
		bas[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		bas[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement && Death
		bas[i].Draw(gfx);

		//mob.Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding, + i, bas[0].GetX(), bas[0].GetY(), etc. )
		//Honestly idk if I'm gonna do this/have a centralized "mob" class to pull functions from. I understand it would benefit me if I have 1000 types of mobs, but since I'm only have ~6, it's more inconvenient. 
	}
	else if (bas[i].GetDeathStage() <= 3 + 1) //if dead and the animation hasn't already happened
	{
		bas[i].DeathAnimation(gfx);
	}
}
void Game::MobGroupJumper(int i)
{
	if (jum[i].GetAlive())
	{
//		jum[i].Aggro(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetOnGroundValue());
		jum[i].Movement(gin[0].GetX(), gin[0].GetW()/*, gin[0].GetDX()*/); //Keep after Aggro
		jum[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		jum[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement && Death
		jum[i].Draw(gfx);
	}
	else if (jum[i].GetDeathStage() <= 3 + 1) //if dead and the animation hasn't already happened
	{
		jum[i].DeathAnimation(gfx);
	}
}
void Game::MobGroupCharger(int i)
{
	if (cha[i].GetAlive())
	{
		cha[i].Aggro(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetOnGroundValue());
		cha[i].Movement(gin[0].GetX(), gin[0].GetW()/*, gin[0].GetDX()*/); //Keep after Aggro
		cha[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		cha[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement && Death
		cha[i].Draw(gfx);
	}
	else if (cha[i].GetDeathStage() <= 3 + 1) //if dead and the animation hasn't already happened
	{
		cha[i].DeathAnimation(gfx);
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
		pel[ran[i].PelletNumber + i * PelletSize].Spawning(PelletSize, ran[i].PelletNumber, ran[i].GetX(), ran[i].GetY(), ran[i].GetW(), ran[i].GetH(), ran[i].GetAggro(), gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDX(), gin[0].GetDY());

		ran[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		ran[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement && Death
		ran[i].Draw(gfx);
	}
	else if (ran[i].GetDeathStage() <= 3 + 1) //if dead and the animation hasn't already happened
	{
		ran[i].DeathAnimation(gfx);
	}

	for (int Pi = 0; Pi < PelletSize; Pi++) //this is outside of GetAlive {} bracket so that a pellet in motion will keep falling after it's ranger dies
	{
		pel[i * PelletSize + Pi].Delta(); //keep before ShootyShootyPowPow
		pel[i * PelletSize + Pi].ShootyShootyPowPow(/*ran[i].GetX(), ran[i].GetY(), ran[i].GetW(), gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[i].GetDX(), gin[i].GetDY()*/);
		if (pel[i * PelletSize + Pi].GetActive() == true) //so basically this is saying each ranger has his own set of pellets, and it will only loop through his ones. ex: ranger 0 has pellets 0-7. ranger 1 has pellets 8-15, etc. 
		{
			pel[i * PelletSize + Pi].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding, gin[0].GetDX(), gin[0].GetDY() ); //Keep after Movement.
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
		wiz[i].EyeLogic(gin[0].GetX(), gin[0].GetY(), gin[0].GetW());
//		wiz[i].Shoot(gin[0].GetX(), gin[0].GetY(), gin[0].GetW());
		orb[i].Spawning(wiz[i].GetX(), wiz[i].GetY(), wiz[i].GetW(), wiz[i].GetH());
		wiz[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		orb[i].Death(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), gin[0].GetDashStage(), gin[0].GetStartPoint());
		wiz[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement && Death
		orb[i].Collision(gin[0].GetX(), gin[0].GetY(), gin[0].GetW(), UserisColliding); //Keep after Movement && Death

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
	else if (wiz[i].GetDeathStage() <= 3 + 1) //if dead and the animation hasn't already happened
	{
		wiz[i].DeathAnimation(gfx);
	}
}

void Game::UserRespawn()
{
	//This is always active, and is just determining which place you will respawn
	//if (screen <= 3) //Yeah this will needlessly be called a shit-ton and isn't optimal code, but idc, it's clean.
	//{
	//	RespawnInBed = true;
	//}
	//else if (screen == 10) //Just choosing if you respawn at screen 0 or screen 10. Basically if you make it to one side of the mobs, you will respawn on that side.
	//{
	//	RespawnInBed = false;
	//}

	//if you die and the animation is done, reset health, reset the mobs, and then respawn. (Movement() function also stops movement during the animation)
	if (/*UserHealth == 0 &&*/ gin[0].GetDeathStage() > 13)
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

		//checkpoints
		if (/*RespawnInBed*/checkpoint == 0)
		{
			screen = 0;
			//gin[0].Respawn(715, 575 - 21);
			gin[0].Respawn(45, 60 - 21);
		}
		else if (checkpoint == 1)
		{
			screen = 2;
			gin[0].Respawn(60, 60);
		}
		else if (checkpoint == 2)
		{
			screen = 3;
			gin[0].Respawn(600, 60);
		}
		else if (checkpoint == 3)
		{
			screen = 6;
			gin[0].Respawn(45, 150);
		}
	}
}

void Game::UserSuicide()
{
	if (wnd.kbd.KeyIsPressed(0x52)) //"R" key allows manual reset; so you don't have to actually die to respawn
	{
		UserHealth = 0;
	}
}

void Game::Cheats()
{
	//All that flying/taking no damage/clip through walls bs
	gin[0].Cheating(wnd.kbd.KeyIsPressed(VK_UP), wnd.kbd.KeyIsPressed(VK_DOWN), wnd.kbd.KeyIsPressed(VK_LEFT), wnd.kbd.KeyIsPressed(VK_RIGHT), wnd.kbd.KeyIsPressed(0x43), wnd.kbd.KeyIsPressed(VK_CONTROL));

	//slow motion
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		Sleep(400);
	}

	//jump ahead in checkpoint
	if (wnd.kbd.KeyIsPressed(VK_F1))
	{
		checkpoint = 0;
	}
	else if (wnd.kbd.KeyIsPressed(VK_F2))
	{
		checkpoint = 1;
	}
	else if (wnd.kbd.KeyIsPressed(VK_F3))
	{
		checkpoint = 2;
	}
	else if (wnd.kbd.KeyIsPressed(VK_F4))
	{
		checkpoint = 3;
	}
}

void Game::Checkpoint(int x, int y)
{
	//horizontal rectangle
	for (int loopx = 0; loopx <= 30; loopx++)
	{
		for (int loopy = 0; loopy <= 10; loopy++)
		{
			gfx.PutPixel(x - 10 + loopx, y - 30 + loopy, 66, 220, 41); //66, 220, 41
		}
	}
	//vertical rectangle
	for (int loopx = 0; loopx <= 10; loopx++)
	{
		for (int loopy = 0; loopy <= 30; loopy++)
		{
			gfx.PutPixel(x + loopx, y - 40 + loopy, 66, 220, 41); //48, 244, 15
		}
	}

	//when you touch the checkpoint, it ups checkpoint, which changes where you respawn, and makes it disappear.
	//Keep this after the draw code; it's just kinda nice to have a frame of lag, so you can sort of walk into it before it poofs.
	if (gin[0].GetX() + gin[0].GetW() + 1 > x - 10 && gin[0].GetX() < x - 10 + 30 + 1 && gin[0].GetY() + gin[0].GetW() + 1 > y - 40 && gin[0].GetY() < y - 40 + 30 + 1)
	{
		checkpoint++;
		UserHealth = 3; //fullheal, baby.
	}	
}

void Game::UpdateModel()
{
	//Keep first
	Cheats();
	UserSuicide();
	if (UserHealth != 0)
	{
		UserMovement();
		gin[0].Delta(); //Keep before Gravity && Movement
		//Keep middle?
		gin[0].Movement(wnd.kbd.KeyIsPressed(VK_SHIFT));
		//gin[0].Direction(); //keep before EyeLogic, but after Movement
		gin[0].EyeLogic();
		gin[0].OnGround(); //Keep before Jump && Dash
		gin[0].OnWall(); //Keep before WallJump
		gin[0].Jump();
		gin[0].WallJump2(wnd.kbd.KeyIsPressed(0x57));
		gin[0].Dash(wnd.kbd.KeyIsPressed(VK_SPACE));
		gin[0].Gravity(); //Keep last in the movement functions
	//	gin[0].TheoreticalValue(); //Keep after all movement functions, but before Screens (aka, before ground/walls adjust value) //you should probably delete this
		UserCollision(); //Keep after all movement functions
	}
	if (UserHealth == 0) //you can't use an else statement, otherwise it will be 1 frame late in drawing the animation. (He will blink to black at start of animation)
	{
		UserRespawn();
		gin[0].DeathAnimation(gfx);
	}
	//Keep last:
	Screens();
	ScreenSwitch(); //I keep this after Screens, so you don't accidentally activate a switch by jumping against a wall close to edge
}

void Game::ComposeFrame()
{
	if (UserHealth != 0)
	{
		gin[0].Draw(gfx/*, Colors::Orange2, Colors::Pasty*/);
		gin[0].DrawDash(gfx); //Keep after Draw()
	}
	HealthBar(); //Keep last, just so it's always on top

//Test bullshit:
	//if (gin[0].GetY() > 300)
	//{
	//	gfx.PutPixel(ran[0].GetX() + ran[0].GetW() / 2 + 50, ran[0].GetY(), 255, 255, 255);
	//}

	//seeing if this works
	//if (6 < (5 || 7) )
	//{
	//	gfx.PutPixel(255, 255, 255, 255, 255);
	//}

	//seeing the length of 100, 200, 300 pixels
	//for (int loop = 0; loop <= 100; loop++)
	//{
	//	gfx.PutPixel(100 + loop, 100, 255, 255, 255);
	//}
	//for (int loop = 0; loop <= 200; loop++)
	//{
	//	gfx.PutPixel(100 + loop, 200, 255, 255, 255);
	//}
	//for (int loop = 0; loop <= 300; loop++)
	//{
	//	gfx.PutPixel(100 + loop, 300, 255, 255, 255);
	//}

	//leaves a trail at all corners of gin. For use with the archer pellets.
	//gfx.PutPixel(gin[0].GetX() - ((gin[0].GetX() - gin[0].GetDX()) / 2), gin[0].GetY() - ((gin[0].GetY() - gin[0].GetDY()) / 2), 255, 255, 255);
	//gfx.PutPixel(gin[0].GetX() - ((gin[0].GetX() - gin[0].GetDX()) / 2), gin[0].GetY() - ((gin[0].GetY() - gin[0].GetDY()) / 2) + gin[0].GetW(), 255, 255, 255);
	//gfx.PutPixel(gin[0].GetX() - ((gin[0].GetX() - gin[0].GetDX()) / 2) + gin[0].GetW(), gin[0].GetY() - ((gin[0].GetY() - gin[0].GetDY()) / 2), 255, 255, 255);
	//gfx.PutPixel(gin[0].GetX() - ((gin[0].GetX() - gin[0].GetDX()) / 2) + gin[0].GetW(), gin[0].GetY() - ((gin[0].GetY() - gin[0].GetDY()) / 2) + gin[0].GetW(), 255, 255, 255);
}
