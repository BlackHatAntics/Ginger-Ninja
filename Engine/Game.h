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
	void Ground(int x, int y, int w);
	void Platform(int x, int y, int w);
	void Wall(int x, int y, int h);
	void Screens();
	void ScreenSwitch();
	void Screen100();
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
	void UserCollision();
	void HealthBar();
	void MobGroupBasic(int i);
	void MobGroupJumper(int i);
	void MobGroupCharger(int i);
	void MobGroupRanger(int i);
	void UserRespawn();
	//void Screen[6](); //I wish...
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr int GinSize = 2;
	static constexpr int BasicSize = 3;
	static constexpr int JumperSize = 3;
	static constexpr int ChargerSize = 3;
	static constexpr int RangerSize = 3;
	static constexpr int PelletSize = 8;
	Ginger gin[GinSize];
	Basic bas[BasicSize];
	Jumper jum[JumperSize];
	Charger cha[ChargerSize];
	Ranger ran[RangerSize];
	Pellet pel[PelletSize];
	int screen = 7; //Start this at 0, but it's 7 right now for testing purposes
	int Level = 0;
	bool UserisColliding = false;
	int UserHealth = 3;
	bool DamageLock = false;
	int DamageLockCounter = 0;
	bool RespawnInBed = true;
	int Pi = 0; // looping through pellet index
	/********************************/
};