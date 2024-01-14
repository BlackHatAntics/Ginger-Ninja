#include "Mob_Wizard_Orb.h"

void Orb::Draw(Graphics & gfx/*, int Rx, int Ry, int Rw*/)
{
	for (int loopx = 0; loopx <= w; loopx++)
	{
		for (int loopy = 0; loopy <= w; loopy++)
		{
			gfx.PutPixel(x + loopx, y + loopy, Colors::Blue2);
		}
	}
}

void Orb::Collision(int Gx, int Gy, int Gw, bool & Colliding)
{
	if ((Gx + Gw + 1 > x && Gx < x + w + 1 && Gy + Gw + 1 > y && Gy < y + w + 1) && active)
	{
		Colliding = true;
	}
}

void Orb::Death(int Gx, int Gy, int Gw, int Gds, int Gsp)
{
	if (Gds > 0 && Gds <= 4) //If dashing
	{
		//if (((Gsp < x && Gx + Gw / 2 >= x + w) || (Gsp > x + w && Gx + Gw / 2 <= x)) //If you started from left and are now on their right, or started on right and are now to the left
		//	&& Gy + Gw > y && Gy < y + w) //Gotta be at the same height level
		if (((Gsp - (Gw / 2 - 1) <= x && Gx + Gw >= x + w) || (Gsp + (Gw / 2 - 1) >= x + w && Gx <= x))
			&& Gy + Gw >= y && Gy <= y + w)
		{
			active = false; //Killing the orb
			OrbStage = 0; //Making it so it can spawn again
			XValue = 0; //resetting velocity so it doesn't spawn already going in a direction
			YValue = 0;
		}
	}
}

void Orb::Spawning(int Rx, int Ry, int Rw, int Rh)
{
	if (OrbStage == 300 && active == false) //delay before he releases orb
	{
		active = true; //this is saying: okay, now you can load up the orb.Shoot() function, and Orb[OrbNumber] will be drawn in Game.cpp
		x = Rx + Rw / 2 - w / 2; //Spawning orbs in middle of his body
		y = Ry + Rh / 2 - w / 2; //Spawning orbs in middle of his body
	}

	//resetting to next orb
//	if (OrbStage == 300)
//	{
//		OrbStage = 0;
//		i++;
//
//		if (i == OrbSize)
//		{
//			i = 0;
//		}
//	}


	if (OrbStage < 300) //incrementing orb stage, only if it hasn't shot yet
	{
		OrbStage++;
	}
//	else //making sure it doesn't start firing super quick next time if it was in middle of OrbStage counter
//	{
//		OrbStage = 0;
//	}
}

void Orb::ShootyShootyPowPow(/*int Wx, int Wy, int Ww,*/ int Gx, int Gy, int Gw/*, int Gdx, int Gdy*/)
{
	static const float MaxIncrement = 0.125f; //this is 1/8 //other one is 1/16
	static const int MaxSpeed = 3;
	float SmallerIncrement;
	float SmallerSpeed;
	bool ActivateCap = false;
	//float XValue;
	//float YValue;
	//if (OrbTrackingCounter == 6) //This is here to make the orb react slowly. It works well when the values adjust by 1, but when it's adjusted by 0.125 it looks terrible. It's not a perfect system anyway, so 0.125 increments are better. They just make the "45 degree travel path" super apparent. So now I gotta fix it.
	//{

	// *********
	//The reason it stops suddenly, is because whenever it changes quadrant (or even whether it's "more left"/"more down"), it suddenly switches from the MaxSpeed cap to the SmallerSpeed cap. And it cuts out all momentum.
	//I'll have to think of a fix...
	//EDIT: I don't think this applies anymore; pretty sure I fixed it. But it's been so long since I looked at this project idek.
	// *********

	//currently working on determining how to set up the incrementing. Like, when do you actually adjust the value of x/y.

	

	//top right quadrant
	if (Gx + Gw / 2 >= x + w / 2 && Gy + Gw / 2 <= y + w / 2) //if in top right quadrant
	{
		//try to clean this shit up, and put as many things outside the function as possible. including SmallerSpeed definition. don't want to have to re-type it 8 times.

		//found an easy way to avoid repeating lines:
		SmallerIncrement = (((Gx + Gw / 2) - (x + w / 2)) / float((y + w / 2) - (Gy + Gw / 2)));
		if (SmallerIncrement > 1)
		{
			SmallerIncrement = 1 / SmallerIncrement; //saying if you divided the larger number by the smaller, then take the reciprocal value. (will be the same as though you divded the smaller by the larger)
		}
		SmallerIncrement = MaxIncrement * SmallerIncrement;
		SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);
		//This completely removes the need to do both rise/run and run/rise. The code is still inside of this specific funtion though, so it's still not optimal.
		//I also thought of an idea. Perhaps I can put all this shit into a function, and just place my own variables each time. I'm only changing a negative symbol or > here and there. I could totally do it.


		if (((Gx + Gw / 2) - (x + w / 2)) < ((y + w / 2) - (Gy + Gw / 2))) //if he is further up than he is right
		{
			//choosing how fast the slower value will go, aka what angle to fly at
			//SmallerIncrement = MaxIncrement * (((Gx + Gw / 2) - (x + w / 2)) / float((y + w / 2) - (Gy + Gw / 2))); //run/rise * MaxIncrement gives you the percentage of 0.125 (the max speed move-number) that you will move by for the smaller number. This make it so he can move in directions other than 45 degrees.
			//SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);

			//adjusting the variables
			YValue -= MaxIncrement;
			if (!(XValue > SmallerSpeed))
			{
				XValue += SmallerIncrement;
				ActivateCap = true;
			}
			
			//making sure it doesn't go too fast
			if (XValue > SmallerSpeed && ActivateCap) //cap is only activated if it incremented the speed this frame
			{
				XValue = SmallerSpeed;
			}
		}
		else //if he is further right than he is up
		{
			//SmallerIncrement = MaxIncrement * (((y + w / 2) - (Gy + Gw / 2)) / float((Gx + Gw / 2) - (x + w / 2))); //rise/run
			//SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);

			if (!(YValue < -SmallerSpeed))
			{
				YValue -= SmallerIncrement;
				ActivateCap = true;
			}
			XValue += MaxIncrement;

			//capping the speed
			if (YValue < -SmallerSpeed && ActivateCap) //cap is only activated if it incremented the speed this frame
			{
				YValue = -SmallerSpeed;
			}
		}
	}
	//top left quadrant
	else if (Gx + Gw / 2 <= x + w / 2 && Gy + Gw / 2 <= y + w / 2) //if in top left quadrant
	{
		//try to clean this shit up, and put as many things outside the function as possible. including SmallerSpeed definition. don't want to have to re-type it 8 times.
	
		if (((x + w / 2)) - (Gx + Gw / 2) < ((y + w / 2) - (Gy + Gw / 2))) //if he is further up than he is left
		{
			//choosing how fast the slower value will go, aka what angle to fly at
			float test1 = (x + w / 2) - (Gx + Gw / 2);
			float test2 = (y + w / 2) - (Gy + Gw / 2);
			float test3 = (((x + w / 2) - (Gx + Gw / 2)) / float((y + w / 2) - (Gy + Gw / 2)));


			SmallerIncrement = MaxIncrement * (((x + w / 2) - (Gx + Gw / 2)) / float((y + w / 2) - (Gy + Gw / 2))); //run/rise * MaxIncrement gives you the percentage of 0.125 (the max speed move-number) that you will move by for the smaller number. This make it so he can move in directions other than 45 degrees.
			SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);
	
			//adjusting the variables
			YValue -= MaxIncrement;
			if (!(XValue < -SmallerSpeed))
			{
				XValue -= SmallerIncrement;
				ActivateCap = true;
			}
	
			//making sure it doesn't go too fast
			if (XValue < -SmallerSpeed && ActivateCap) //cap is only activated if it incremented the speed this frame
			{
				XValue = -SmallerSpeed;
			}
		}
		else //if he is further left than he is up
		{
			float test1 = (y + w / 2) - (Gy + Gw / 2);
			float test2 = (x + w / 2) - (Gx + Gw / 2);
			float test3 = (((y + w / 2) - (Gy + Gw / 2)) / float((x + w / 2) - (Gx + Gw / 2)));

			SmallerIncrement = MaxIncrement * (((y + w / 2) - (Gy + Gw / 2)) / float((x + w / 2) - (Gx + Gw / 2))); //rise/run
			SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);
	
			if (!(YValue < -SmallerSpeed))
			{
				YValue -= SmallerIncrement;
				ActivateCap = true;
			}
			XValue -= MaxIncrement;
			
			//capping the speed
			if (YValue < -SmallerSpeed && ActivateCap) //cap is only activated if it incremented the speed this frame
			{
				YValue = -SmallerSpeed;
			}
		}
	}
	//bottom left quadrant
	else if (Gx + Gw / 2 <= x + w / 2 && Gy + Gw / 2 >= y + w / 2) //if in bottom left quadrant
	{
		//try to clean this shit up, and put as many things outside the function as possible. including SmallerSpeed definition. don't want to have to re-type it 8 times.

		if (((x + w / 2)) - (Gx + Gw / 2) < ((Gy + Gw / 2) - (y + w / 2))) //if he is further down than he is left
		{
			//choosing how fast the slower value will go, aka what angle to fly at
			float test1 = (x + w / 2) - (Gx + Gw / 2);
			float test2 = (y + w / 2) - (Gy + Gw / 2);
			float test3 = (((x + w / 2) - (Gx + Gw / 2)) / float((y + w / 2) - (Gy + Gw / 2)));


			SmallerIncrement = MaxIncrement * (((x + w / 2) - (Gx + Gw / 2)) / float((Gy + Gw / 2) - (y + w / 2))); //run/rise * MaxIncrement gives you the percentage of 0.125 (the max speed move-number) that you will move by for the smaller number. This make it so he can move in directions other than 45 degrees.
			SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);

			//adjusting the variables
			YValue += MaxIncrement;
			if (!(XValue < -SmallerIncrement)) //Only increment if you aren't already higher. This is needed, cause you can't just always put a cap on the speed. (see why directly below)
			{
				XValue -= SmallerIncrement;
				ActivateCap = true; //this prevents it from activating the cap when switching from a different quadrant. If this isn't here, it will suddenly jump from MaxSpeed to SmallerSpeed and kill all momentum.
			}
			

			//making sure it doesn't go too fast
			if (XValue < -SmallerSpeed && ActivateCap) //cap is only activated if it incremented the speed this frame
			{
				XValue = -SmallerSpeed;
			}
		}
		else //if he is further left than he is up
		{
			float test1 = (Gy + Gw / 2) - (y + w / 2);
			float test2 = (x + w / 2) - (Gx + Gw / 2);
			float test3 = (((Gy + Gw / 2) - (y + w / 2)) / float((x + w / 2) - (Gx + Gw / 2)));

			SmallerIncrement = MaxIncrement * (((Gy + Gw / 2) - (y + w / 2)) / float((x + w / 2) - (Gx + Gw / 2))); //rise/run
			SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);

			//adjusting the variables
			if (!(YValue > SmallerSpeed))
			{
				YValue += SmallerIncrement;
				ActivateCap = true;
			}
			XValue -= MaxIncrement;

			if (YValue > SmallerSpeed && ActivateCap) //cap is only activated if it incremented the speed this frame
			{
				YValue = SmallerSpeed;
			}
		}
	}
	//bottom right quadrant
	else if (Gx + Gw / 2 >= x + w / 2 && Gy + Gw / 2 >= y + w / 2) //if in bottom right quadrant
	{
	//try to clean this shit up, and put as many things outside the function as possible. including SmallerSpeed definition. don't want to have to re-type it 8 times.

	if (((Gx + Gw / 2) - (x + w / 2)) < ((Gy + Gw / 2) - (y + w / 2))) //if he is further down than he is left
	{
		//choosing how fast the slower value will go, aka what angle to fly at
		//float test1 = (x + w / 2) - (Gx + Gw / 2);
		//float test2 = (y + w / 2) - (Gy + Gw / 2);
		//float test3 = (((x + w / 2) - (Gx + Gw / 2)) / float((y + w / 2) - (Gy + Gw / 2)));


		SmallerIncrement = MaxIncrement * (((Gx + Gw / 2) - (x + w / 2)) / float((Gy + Gw / 2) - (y + w / 2))); //run/rise * MaxIncrement gives you the percentage of 0.125 (the max speed move-number) that you will move by for the smaller number. This make it so he can move in directions other than 45 degrees.
		SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);

		//adjusting the variables
		YValue += MaxIncrement;
		if (!(XValue > SmallerSpeed))
		{
			XValue += SmallerIncrement;
			ActivateCap = true;
		}		

		//making sure it doesn't go too fast
		if (XValue > SmallerSpeed && ActivateCap) //cap is only activated if it incremented the speed this frame
		{
			XValue = SmallerSpeed;
		}
	}
	else //if he is further left than he is up
	{
		//float test1 = (Gy + Gw / 2) - (y + w / 2);
		//float test2 = (x + w / 2) - (Gx + Gw / 2);
		//float test3 = (((Gy + Gw / 2) - (y + w / 2)) / float((x + w / 2) - (Gx + Gw / 2)));

		SmallerIncrement = MaxIncrement * (((Gy + Gw / 2) - (y + w / 2)) / float((Gx + Gw / 2) - (x + w / 2))); //rise/run
		SmallerSpeed = SmallerIncrement * float(MaxSpeed / MaxIncrement);

		//adjusting the variables
		if (!(YValue > SmallerSpeed))
		{
			YValue += SmallerIncrement;
			ActivateCap = true;
		}
		XValue += MaxIncrement;

		if (YValue > SmallerSpeed && ActivateCap) //cap is only activated if it incremented the speed this frame
		{
			YValue = SmallerSpeed;
		}
	}
	}



	//MaxSpeed / Max Increment is how many frames it will take to reach the max. so you're basically multiplying the speed by how many frames, so it is equal proportion to MaxSpeed. (ex: if your MaxSpeed is 4, your MaxIncrement is 0.125, and 4 / 0.125 = 32. then getting a speed of 0.100 will produce a max of 3 (as opposed to the max of 4). (3.2 + 0.5 = 3.7, rounded down to 3 by int function) So this is saying move up 3 pixels, every time it moves over by 4. creating proper angle.
//	int SmallerSpeed = SmallerIncrement * (MaxSpeed / MaxIncrement) + 0.5; //+0.5 is so that you pick the closest rounded value, not just the one that moves at 90degrees because it can't make orb move 1 pixel too high
	//NEVERMIND make SmallerSpeed a float, and it will only convert to int when you absolutely finally draw it, so you can make it move exactly on any angle you wish. (Chili Tutorial 16)

		//if (Gx + Gw / 2 < x + w / 2)
		//{
		//	LeftValue -= MaxIncrement; //it is 0.125 so it reacts slowly, and has a slow "tracking" effect. Makes it wavy and whatnot as well. 0.125 is 1/8. Don't really have any other numbers that go in nicely. 0.2 is too much, 0.1 is too little
		//	if (LeftValue < -MaxSpeed) //Only starts adding speed from RightValue if LeftValue is at max speed
		//	{
		//		RightValue -= MaxIncrement;
		//	}
		//}
		//if (Gx + Gw / 2 > x + w / 2)
		//{
		//	RightValue += MaxIncrement;
		//	if (RightValue > MaxSpeed) //Only starts adding speed from LeftValue if RightValue is at max speed
		//	{
		//		LeftValue += MaxIncrement;
		//	}
		//}
		//if (Gy + Gw / 2 < y + w / 2)
		//{
		//	UpValue -= MaxIncrement;
		//	if (UpValue < -MaxSpeed) //Only starts adding speed from DownValue if UpValue is at max speed
		//	{
		//		DownValue -= MaxIncrement;
		//	}
		//}
		//if (Gy + Gw / 2 > y + w / 2)
		//{
		//	DownValue += MaxIncrement;
		//	if (DownValue > MaxSpeed) //Only starts adding speed from UpValue if DownValue is at max speed
		//	{
		//		UpValue += MaxIncrement;
		//	}
		//}
	//	OrbTrackingCounter = -1;
	//}
	//OrbTrackingCounter++;

	//making sure nothing ever goes above MaxSpeed
	if (XValue > MaxSpeed)
	{
		XValue = MaxSpeed;
	}
	else if (XValue < -MaxSpeed)
	{
		XValue = -MaxSpeed;
	}
	if (YValue < -MaxSpeed)
	{
		YValue = -MaxSpeed;
	}
	else if (YValue > MaxSpeed)
	{
		YValue = MaxSpeed;
	}

	//Stopping it from moving too quickly
	//if (LeftValue < -MaxSpeed)
	//{
	//	LeftValue = -MaxSpeed;
	//}
	//else if (LeftValue > 0)
	//{
	//	LeftValue = 0;
	//}
	//if (RightValue > MaxSpeed)
	//{
	//	RightValue = MaxSpeed;
	//}
	//else if (RightValue < 0)
	//{
	//	RightValue = 0;
	//}
	//if (UpValue < -MaxSpeed)
	//{
	//	UpValue = -MaxSpeed;
	//}
	//else if (UpValue > 0)
	//{
	//	UpValue = 0;
	//}
	//if (DownValue > MaxSpeed)
	//{
	//	DownValue = MaxSpeed;
	//}
	//else if (DownValue < 0)
	//{
	//	DownValue = 0;
	//}	
	

	x += XValue/*LeftValue + RightValue*/; //Moving the orb along x value
	y += YValue/*UpValue + DownValue*/; //Moving the orb along y value
}

void Orb::Respawn()
{
	//OrbStage = 0; //Retired.
	active = false;
	XValue = 0;
	YValue = 0;
	OrbStage = 200; //So the first shot when you enter a room is fast
}

//void Orb::SetActive(bool Active)
//{
//	active = Active;
//}
bool Orb::GetActive()
{
	return active;
}
int Orb::GetX()
{
	return x;
}
int Orb::GetY()
{
	return y;
}
int Orb::GetW()
{
	return w;
}
