// Fill out your copyright notice in the Description page of Project Settings.

#include "JocryrNativeRanged.h"


// Sets default values
AJocryrNativeRanged::AJocryrNativeRanged()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJocryrNativeRanged::BeginPlay()
{
	Super::BeginPlay();
	
}

int distance1 = 0;




FRotator direction1;

// Called every frame
void AJocryrNativeRanged::Tick(float DeltaTime)
{
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

