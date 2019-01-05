// Fill out your copyright notice in the Description page of Project Settings.

#include "TheCourrupted_MedSpeed.h"



// Sets default values
ATheCourrupted_MedSpeed::ATheCourrupted_MedSpeed()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


float randomVelocity1= 0;
float distance1 = 0;
bool ag1 = false;
bool leftturn1 = false;
bool rightturn1 = false;
int movedistance1 = 0;
float idlespeed1 = 0;


// Called when the game starts or when spawned
void ATheCourrupted_MedSpeed::BeginPlay()
{

	Super::BeginPlay();

	randomVelocity1 = 0;
	distance1 = 0;
	ag1 = false;
	leftturn1 = false;
	rightturn1 = false;
	movedistance1 = 0;
	idlespeed1 = 0;

	randomVelocity1 = 3 + (rand() % 8);
	if (randomVelocity1 < 3)
	{
		leftturn1 = false;

	}
	else
	{
		leftturn1 = true;
	}
	if (randomVelocity1 > 3)
	{
		rightturn1 = false;

	}
	else
	{
		rightturn1 = true;
	}
	randomVelocity1 = randomVelocity1 / 7;


}

// Called every frame
void ATheCourrupted_MedSpeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector myposition = GetActorLocation();
	distance1 = (PlayerLocation.X - myposition.X) * 1;
	if (distance1 < 0)
	{
		distance1 = distance1 * -1;
	}
	if (distance1 < 100)
	{
		ag1 = true;
	}
	if (ag1 == true)
	{
		if (myposition.X < PlayerLocation.X)
		{
			myposition.X = myposition.X + randomVelocity1;
			SetActorLocation(myposition);
			
		}
		if (myposition.X > PlayerLocation.X)
		{
			myposition.X = myposition.X - randomVelocity1;
			SetActorLocation(myposition);
		
		}
		if (myposition.Z < PlayerLocation.Z)
		{
			myposition.Z = myposition.Z + randomVelocity1;
			SetActorLocation(myposition);
		}
		if (myposition.Z > PlayerLocation.Z)
		{
			myposition.Z = myposition.Z - randomVelocity1;
			SetActorLocation(myposition);
		}
	}
	else
	{
		idlespeed1 = randomVelocity1 / 2;
		if (rightturn1 == true)
		{
			myposition.X = myposition.X + idlespeed1;
			SetActorLocation(myposition);
			if (movedistance1 > 250)
			{
				rightturn1 = false;
				leftturn1 = true;
			}
			movedistance1++;
		}
		if (leftturn1 == true)
		{
			myposition.X = myposition.X - idlespeed1;
			SetActorLocation(myposition);
			if (movedistance1 < -250)
			{
				rightturn1 = true;
				leftturn1 = false;
			}
			movedistance1--;
		}
	}

}


