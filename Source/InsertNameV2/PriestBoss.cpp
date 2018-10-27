// Fill out your copyright notice in the Description page of Project Settings.

#include "PriestBoss.h"
#include <ctime>
#include <cstdio>


// Sets default values
APriestBoss::APriestBoss()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APriestBoss::BeginPlay()
{
	Super::BeginPlay();

}
bool timer(double secondsToDelay)
{
	clock_t startTime = clock(); //Start timer

	clock_t testTime;
	clock_t timePassed;
	double secondsPassed;

	while (true)
	{
		testTime = clock();
		timePassed = startTime - testTime;
		secondsPassed = timePassed / (double)CLOCKS_PER_SEC;

		if (secondsPassed >= secondsToDelay)
		{
			return true;
		}
	}


}
float position = 0;
FVector insert;
int distance = 0;
bool on = true;
bool turn = false;// Called every frame
float tick = 0;
int range = 200;
int distance2 = 0;
bool negate1 = false;
bool negate2 = false;
void APriestBoss::Tick(float DeltaTime)
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector myposition = GetActorLocation();

	Super::Tick(DeltaTime);


	//moves object back and forth
	if (on == true)
	{
		distance = (PlayerLocation.X - position) * 1;
		distance2 = PlayerLocation.X - position;
		if (distance2 > 20)
		{
			negate1 = true;
		}
		else
		{
			negate1 = false;
		}
		if (distance2 < -20)
		{
			negate2 = true;
		}
		else
		{
			negate2 = false;
		}
		if (distance < 1)
		{


			if (negate1 == false)
			{
				position = position + .3f;
			}
		}
		else if(distance > 1)
		{
			if (negate2 == false)
			{
				position = position - .3f;
			}
			
			

		}
		myposition.X = position;

		SetActorLocation(myposition);
	}

	
	
	




}
