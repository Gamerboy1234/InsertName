// Fill out your copyright notice in the Description page of Project Settings.

#include "JN_Ranged.h"


// Sets default values
AJN_Ranged::AJN_Ranged()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJN_Ranged::BeginPlay()
{
	Super::BeginPlay();
	
}

int distance1 = 0;
FRotator direction1;
bool dead = false; 
bool isLeft = false; 
bool isRight = false; 
bool SpearFound = false;
FVector SpearLocation; 
bool aggro = false; 
bool isFiring = false;
bool finished1 = false;

// Called every frame
void AJN_Ranged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector myposition = GetActorLocation();
	distance1 = (PlayerLocation.X - myposition.X) * 1;
	if (distance1 < 0)
	{
		distance1 = distance1 * -1;
	}
	if (distance1 < agRadius) {
		aggro = true;
	}
	
	if (aggro) {
		if (SpearAmmount > 0 && finished1 == false)
		{
			if (SpearAmmount <= 1)
			{
				finished1 = true;
			}
			if (dead != true && SpearFound != true) {

				distance1 = (PlayerLocation.X - myposition.X) * 1;
				if (distance1 < 0)
				{
					distance1 = distance1 * -1;
				}

				Super::Tick(DeltaTime);
				//moves object back and forth
				if (myposition.X > PlayerLocation.X && distance1 < 150 )
				{
					// left
					direction1.Yaw = 180;
					myposition.X = myposition.X + .5;
					SetActorLocation(myposition);
					SetActorRotation(direction1);
					isLeft = true;
					isRight = false;

				}
				if (myposition.X < PlayerLocation.X && distance1 < 150 )
				{
					// right
					direction1.Yaw = 0;
					myposition.X = myposition.X - .5;
					SetActorLocation(myposition);
					SetActorRotation(direction1);
					isLeft = false;
					isRight = true;
				}

			}
		}
		else
		{
			if (SpearFound && finished1 == true)
			{
				
				if (myposition.X > SpearLocation.X)

				{
					direction1.Yaw = 180;
					myposition.X = myposition.X - .5;
					SetActorLocation(myposition);
					SetActorRotation(direction1);
					
				}
				if (myposition.X < SpearLocation.X)
				{
					direction1.Yaw = 0;
					myposition.X = myposition.X + .5;
					SetActorLocation(myposition);
					SetActorRotation(direction1);
				
				}
				if (SpearAmmount >= 2)
				{
					finished1 = false;
				}

			}
		}
	}
	
	if (isFiring)
	{
		if (myposition.X > PlayerLocation.X)
		{
			direction1.Yaw = 0;
	    }
		if (myposition.X < PlayerLocation.X)
		{
			direction1.Yaw = 180;
		}
	}
}

