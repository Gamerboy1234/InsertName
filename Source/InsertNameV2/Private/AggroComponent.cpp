// Fill out your copyright notice in the Description page of Project Settings.


#include "AggroComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UAggroComponent::UAggroComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

  AggroRange = 300;
}

// Called every frame
void UAggroComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  TraceRight();
  TraceLeft();
}

void UAggroComponent::TraceRight()
{
  FVector TraceStart = GetOwner()->GetActorLocation();
  FVector TraceEnd = GetOwner()->GetActorForwardVector() * AggroRange + TraceStart;

  FHitResult OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel13);

  FCollisionQueryParams CollisionParms;
  CollisionParms.AddIgnoredActor(GetOwner());

  DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2);

  if (GetWorld()->LineTraceSingleByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
  {
    if (OutHit.bBlockingHit)
    {
      if (OutHit.Actor != nullptr)
      {
        bAggro = true;
      }
    }
  }
}

void UAggroComponent::TraceLeft()
{
  FVector TraceStart = GetOwner()->GetActorLocation();
  FVector TraceEnd = GetOwner()->GetActorForwardVector() * AggroRange + TraceStart;

  FHitResult OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel13);

  FCollisionQueryParams CollisionParms;
  CollisionParms.AddIgnoredActor(GetOwner());

  DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2);

  if (GetWorld()->LineTraceSingleByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
  {
    if (OutHit.bBlockingHit)
    {
      if (OutHit.Actor != nullptr)
      {
        bAggro = true;
      }
    }
  }
}

const bool UAggroComponent::GetAggro()
{
  return bAggro;
}

