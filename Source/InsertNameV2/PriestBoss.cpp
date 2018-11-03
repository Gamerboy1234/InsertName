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
	distance = (PlayerLocation.X - myposition.X) * 1;
	if (distance < 0)
	{
		distance = distance * -1;
	}

	Super::Tick(DeltaTime);
	//moves object back and forth
	if (myposition.X > PlayerLocation.X && distance < 100)
	{
		myposition.X = myposition.X + .5;
	}
	if (myposition.X < PlayerLocation.X && distance < 100)
	{
		myposition.X = myposition.X - .5;
	}

	

	
		

		SetActorLocation(myposition);
	}

	
	
	





