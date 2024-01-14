/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Ginger.h"
#include "Mob_Basic.h"
#include "Mob_Jumper.h"
#include "Mob_Charger.h"
#include "Mob_Ranger.h"
#include "Mob_Ranger_Pellet.h"
#include "Mob_Wizard.h"
#include "Mob_Wizard_Orb.h"
#include <string>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void UserMovement();
	void Ground(int x, int y, int w, Color c = Colors::White);
	void Platform(int x, int y, int w);
	void Wall(int x, int y, int h, Color c = Colors::White);
	void GroundPre(int x, int y, int w);
	void WallPre(int x, int y, int h);
	void PlatformPre(int x, int y, int w);
	bool tHitWall = false; //theoretically hit a wall
	bool tHitGround = false; //theoretically hit the ground
//	bool tHitCeiling = false; //theoretically hit the ceiling
	void Screens();
	void ScreenSwitch();
	void Screen100();
	void Screen00();
	void Screen0();
	void Screen1();
	void Screen2();
	void Screen3();
	void Screen4();
	void Screen5();
	void Screen6();
	void Screen7();
	void Screen8();
	void Screen9();
	void Screen10();
	void Screen11();
	void Screen19();
	void Screen20(); //was gonna be frogs. now idk
	void UserCollision();
	void HealthBar();
	void MobGroupBasic(int i);
	void MobGroupJumper(int i);
	void MobGroupCharger(int i);
	void MobGroupRanger(int i);
	void MobGroupWizard(int i);
	void UserRespawn();
	void UserSuicide();
	void Cheats();
	void Checkpoint(int x, int y);
	void DrawArrow(int x, int y, int length, std::string direction);
	//void Screen[6](); //I wish...
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr int GinSize = 1; //I don't know why I even gave the option of having more than 1 ginger...
	static constexpr int BasicSize = 30;
	static constexpr int JumperSize = 20;
	static constexpr int ChargerSize = 5;
	static constexpr int RangerSize = 10;
	static constexpr int PelletSize = 8;
	static constexpr int WizardSize = 5;
	Ginger gin[GinSize];
	Basic bas[BasicSize];
	Jumper jum[JumperSize];
	Charger cha[ChargerSize];
	Ranger ran[RangerSize];
	Pellet pel[PelletSize * RangerSize]; //each ranger has PelletSize amount dedicated to them
	Wizard wiz[WizardSize];
	Orb orb[WizardSize];
	int screen = 0; //Start this at 0, but it's 7 right now for testing purposes
	//int Level = 0; //jk scrapped this entire idea just so I could call this game "done" sooner
	int checkpoint = 0;
	bool UserisColliding = false;
	int UserHealth = 3;
	bool DamageLock = false;
	int DamageLockCounter = 0;
	//bool RespawnInBed = true;
//	int Pi = 0; // looping through pellet index
//	int Oi = 0; // looping through orb index
	/********************************/
};