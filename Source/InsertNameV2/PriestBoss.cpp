// Fill out your copyright notice in the Description page of Project Settings.

#include "PriestBoss.h"

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


FVector insert;
int distance = 0;
bool on = true;
bool turn = false;// Called every frame
float tick = 0;
int range = 200;
int distance2 = 0;
bool negate1 = false;
bool negate2 = false;
FRotator direction;

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
		// left
		direction.Yaw = 180;
		myposition.X = myposition.X + .5;
		SetActorLocation(myposition);
		SetActorRotation(direction);
		
	}
	if (myposition.X < PlayerLocation.X && distance < 100)
	{
		// right
		direction.Yaw = 0;
		myposition.X = myposition.X - .5;
		SetActorLocation(myposition);
		SetActorRotation(direction );
	}
			
			
	}

	
	
	





