// Fill out your copyright notice in the Description page of Project Settings.

#include "TheCorrupted.h"


// Sets default values
ATheCorrupted::ATheCorrupted()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
float randomVelocity = 0;
float distance = 0;
bool ag = false;
bool leftturn = false;
bool rightturn = false;
int movedistance = 0;
float idlespeed = 0;


// Called when the game starts or when spawned
void ATheCorrupted::BeginPlay()
{
	
	Super::BeginPlay();
	 randomVelocity = 0;
	 distance = 0;
	 ag = false;
     leftturn = false;
	 rightturn = false;
	 movedistance = 0;
	 idlespeed = 0;
	
	randomVelocity = 1 + (rand() % 8);
	if (randomVelocity < 3)
	{
		 leftturn = false;

	}
	else
	{
		leftturn = true;
	}
	if (randomVelocity > 3)
	{
	  rightturn = false;

	}
	else
	{
		rightturn = true;
	}
	randomVelocity = randomVelocity / 7;
	
	
}

// Called every frame
void ATheCorrupted::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector myposition = GetActorLocation();
	distance = (PlayerLocation.X - myposition.X) * 1;
	if (distance < 0)
	{
		distance = distance * -1;
	}
	if (distance < 100)
	{
		ag = true;
	}
	if (ag == true)
	{
		if (myposition.X < PlayerLocation.X)
		{
			myposition.X = myposition.X + randomVelocity;
			SetActorLocation(myposition);
		}
		if (myposition.X > PlayerLocation.X)
		{
			myposition.X = myposition.X - randomVelocity;
			SetActorLocation(myposition);
		}
	}
	else
	{
		idlespeed = randomVelocity / 2;
		if (rightturn == true )
		{
			myposition.X = myposition.X + idlespeed;
			SetActorLocation(myposition);
			if (movedistance > 250)
			{
				rightturn = false;
				leftturn = true;
			}
			movedistance++;
		}
		if (leftturn == true)
		{
			myposition.X = myposition.X - idlespeed;
			SetActorLocation(myposition);
			if (movedistance < -250)
			{
				rightturn = true;
				leftturn = false;
			}
			movedistance--;
		}
	}

}

