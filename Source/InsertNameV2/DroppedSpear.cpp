// Fill out your copyright notice in the Description page of Project Settings.

#include "DroppedSpear.h"

// Sets default values
ADroppedSpear::ADroppedSpear()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADroppedSpear::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADroppedSpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector myposition = GetActorLocation();

}

