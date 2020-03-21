// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_MoveablePlatform.h"
#include "PaperSpriteComponent.h"

// Sets default values
AMaster_MoveablePlatform::AMaster_MoveablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  RootComponent = SpriteComp;

  MovementSpeed = 200.0f;
  bOneShot = true;
}

// Called when the game starts or when spawned
void AMaster_MoveablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
  GlobalStartLocation = GetActorLocation();
  GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

// Called every frame
void AMaster_MoveablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  if (bCanMove)
  {
    FVector Location = GetActorLocation();

    float Journeylength = (GlobalTargetLocation - GlobalStartLocation).Size();
    float JourneyTravelled = (Location - GlobalStartLocation).Size();

    if (JourneyTravelled >= Journeylength)
    {
      bCanMove = (!bOneShot) ? true : false;

      FVector Swap = GlobalStartLocation;
      GlobalStartLocation = GlobalTargetLocation;
      GlobalTargetLocation = Swap;
    }
 
    FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

    Location += MovementSpeed * DeltaTime * Direction;

    SetActorLocation(Location);
  }
}

const bool AMaster_MoveablePlatform::GetCanMove()
{
  return bCanMove;
}

void AMaster_MoveablePlatform::SetCanMove(bool bShouldMove)
{
  bCanMove = bShouldMove;
}
