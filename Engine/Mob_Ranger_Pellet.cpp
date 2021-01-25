#include "Mob_Ranger_Pellet.h"

void Pellet::Draw(Graphics & gfx/*, int Rx, int Ry, int Rw*/)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= w; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, Colors::Brown1);
		}
	}
}

void Pellet::Spawning(int PelletSize, int & i, int Rx, int Ry, int Rw, int Rh, bool aggro, int Gx, int Gy, int Gw, int Gdx, int Gdy)
{
	if (PelletStage == 10 && active == false) //short delay before he starts firing
	{
		active = true; //this is saying: okay, now you can load up the pel.Shoot() function, and Pellet[PelletNumber] will be drawn in Game.cpp
		x = Rx + Rw / 2 - w / 2; //Spawning pellets in middle of his body
		y = Ry + Rh / 2 - w / 2; //Spawning pellets in middle of his body

		//Determining the flight path
		if (Gx + Gw / 2 > Rx + Rw / 2) //If Ginger is to the right of Ranger
		{
			Direction = 1; //Make pellets fly to the right
		}
		else
		{
			Direction = -1; //Make pellets fly to the left
		}

//		Distance = Rx + Rw / 2 - Gx + Gw / 2;

//		amount of frames it takes to hit ground with 0 SpeedY: (Rh / 2 - w / 2) / 2   (5)
//		Distance pellet will travel till ground with 0 SpeedY: PotentialSpeed * AmountOfFrames (50)

//		amount of frames it will take to hit y peak with 0 SpeedY: 1
//		distance pellet will travel till YPeak: Potentialspeed * 1 (20)
		//with SpeedY of 1: Potentialspeed * 1.5 (30)
		//2: Potentialspeed * 2		(40)
		//3: Potentialspeed * 2.5	(50)
		//4: Potentialspeed * 3		(60)
		//5: Potentialspeed * 3.5	(70)
		//6: Potentialspeed * 4		(80)
		//7: Potentialspeed * 4.5	(90)
		//8: Potentialspeed * 5		(100)
	//	(divide by 2 and add 1) for number of frames
		//In order to get number of frames for distance till it gets back to the starting y value, just do SpeedY + 1

		//calculate how high each pellet gets
		//with SpeedY of 1:
		//2: 2		1
		//3: 4		1.3333333333333
		//4: 6		1.5
		//5: 9		1.8
		//6: 12		2
		//7: 16		2.2857142857142
		//8: 20		2.5
		//9: 25 
		//10: 30	3
		//11: 36
		//12: 42	3.5
		//13: 49
		//14: 56	4
		//so approximately add 0.25 each time

		//now calculate so that the same amount of force is generated at each angle, and you adjust x speed accordingly...

		//a projectile should travel 4 times further than the height it reaches, assuming 45 degrees. so figure out what height a projectile should be reaching, aka, determine how much SpeedY takes away from SpeedX
		//with 


		//This is where you should put code that makes the projectile fire at the player (this note is if you don't code for another month and come back) - delete
		SpeedY = -14;
		//SpeedX = PotentialSpeed + SpeedY * 1.5;
		//int NumberOfFrames = (-1 * (SpeedY / 2) + 1);
		//SpeedX = PotentialSpeed/4;
		int NumberOfFrames = (-1 * SpeedY) + 1; //Number of frames it takes for pellet to travel up, and back down to original y value
		int Height = (-1 * SpeedY) * ((-1 * SpeedY) * 0.25 + 0.5); //How high the peak of parabola is
	//	int XFactor = 4 * 
		SpeedX = Height * 4/*XFactor*/ / NumberOfFrames; //* 4 = exactly 45 degrees. Should be maximal distance. Need to adjust the multiplier based off the percentage that SpeedY is of PotentialSpeed........... Nah nevermind. Fuck it, I'll keep it simple. Always shoot in 45 degrees





	}

	//resetting to next pellet
	if (PelletStage == 100)
	{
		PelletStage = 0;
		i++;

		if (i == PelletSize)
		{
			i = 0;
		}
	}

	if (aggro) //incrementing pellet stage, only if he's aggro / actually firing
	{
		PelletStage++;
	}
	else //making sure it doesn't start firing super quick next time if it was in middle of PelletStage counter
	{
		PelletStage = 0;
	}
}

void Pellet::ShootyShootyPowPow(/*int Rx, int Ry, int Rw, int Gx, int Gy, int Gw, int Gdx, int Gdy*/)
{
	if (active)
	{
		x += SpeedX * Direction; //Moving the pellet along x value
		y += SpeedY/* + */; //Moving the pellet along y value
		SpeedY += 2; //Constant gravity
		if (x > 799 - w || x < 0 || y > 599 - w || y < 0) //borders
		{
			active = false;
			//x = 0;
			//y = 0;
		}
	}
}

void Pellet::Respawn()
{
	PelletStage = 0;
	active = false;
}

//void Pellet::SetActive(bool Active)
//{
//	active = Active;
//}
bool Pellet::GetActive()
{
	return active;
}