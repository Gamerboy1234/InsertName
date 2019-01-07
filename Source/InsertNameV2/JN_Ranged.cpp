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

// Called every frame
void AJN_Ranged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (dead != true) {
		FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		FVector myposition = GetActorLocation();
		distance1 = (PlayerLocation.X - myposition.X) * 1;
		if (distance1 < 0)
		{
			distance1 = distance1 * -1;
		}

		Super::Tick(DeltaTime);
		//moves object back and forth
		if (myposition.X > PlayerLocation.X && distance1 < 100)
		{
			// left
			direction1.Yaw = 180;
			myposition.X = myposition.X + .5;
			SetActorLocation(myposition);
			SetActorRotation(direction1);

		}
		if (myposition.X < PlayerLocation.X && distance1 < 100)
		{
			// right
			direction1.Yaw = 0;
			myposition.X = myposition.X - .5;
			SetActorLocation(myposition);
			SetActorRotation(direction1);
		}

	}

}

