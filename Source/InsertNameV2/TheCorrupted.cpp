// Fill out your copyright notice in the Description page of Project Settings.

#include "TheCorrupted.h"


// Sets default values
ATheCorrupted::ATheCorrupted()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float velocity = 0;
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

	 ag = false;
  
}

// Called every frame
void ATheCorrupted::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector myposition = GetActorLocation();
	distance = (PlayerLocation.X - myposition.X) * 1;
	
	if (ag == true)
	{
		if (myposition.X < PlayerLocation.X)
		{
			myposition.X = myposition.X + velocity;
			SetActorLocation(myposition);
		}
		if (myposition.X > PlayerLocation.X)
		{
			myposition.X = myposition.X - velocity;
			SetActorLocation(myposition);
		}
		if (myposition.Z < PlayerLocation.Z)
		{
			myposition.Z = myposition.Z + velocity;
			SetActorLocation(myposition);
		}
		if (myposition.Z > PlayerLocation.Z)
		{
			myposition.Z = myposition.Z - velocity; 
			SetActorLocation(myposition);
		}
	}
	else
	{
		idlespeed = velocity / 2;
		if (rightturn == true )
		{
			myposition.X = myposition.X + idlespeed;
			SetActorLocation(myposition);
			if (movedistance > 100)
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
			if (movedistance < -100)
			{
				rightturn = true;
				leftturn = false;
			}
			movedistance--;
		}
	}

}

