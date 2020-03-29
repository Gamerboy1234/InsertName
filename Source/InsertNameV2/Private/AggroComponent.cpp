// Fill out your copyright notice in the Description page of Project Settings.


#include "AggroComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "InsertNameV2.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"

static int32 DebugEnemyAggro = 0;
FAutoConsoleVariableRef CVARDebugAggro(
  TEXT("Aggro.DebugEnemyAggro"),
  DebugEnemyAggro,
  TEXT("Draw aggro line of sight"),
  ECVF_Cheat);

// Sets default values for this component's properties
UAggroComponent::UAggroComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

  AggroRange = FVector(300, 0, 0);

  bTwoSided = true;
  bTraceRight = false;
  bTraceLeft = false;
}

// Called every frame
void UAggroComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (bTwoSided)
  {
    TraceRight();
    TraceLeft();
  }
  else if (bTraceRight)
  {
    TraceRight();
  }
  else if (bTraceLeft)
  {
    TraceLeft();
  }
  else
  {
    UE_LOG(LogGameplaySystem, Log, TEXT("Actor %s aggro component is not firing"), *GetOwner()->GetName())
  }
}

void UAggroComponent::TraceRight()
{
  FVector TraceStart = GetOwner()->GetActorLocation();
  FVector TraceEnd = TraceStart + AggroRange;

  FHitResult OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel13);

  FCollisionQueryParams CollisionParms;
  CollisionParms.AddIgnoredActor(GetOwner());

  if (DebugEnemyAggro)
  {
    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0);
  }

  if (GetWorld()->LineTraceSingleByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
  {
    if (OutHit.bBlockingHit)
    {
      if (OutHit.Actor != nullptr)
      {
        bAggro = true;

        if (DebugEnemyAggro)
        {
          UE_LOG(LogGameplaySystem, Log, TEXT("Hit %s on right side"), *OutHit.Actor->GetName())
        }
      }
    }
  }
}

void UAggroComponent::TraceLeft()
{
  FVector TraceStart = GetOwner()->GetActorLocation();
  FVector TraceEnd = TraceStart - AggroRange;

  FHitResult OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel13);

  FCollisionQueryParams CollisionParms;
  CollisionParms.AddIgnoredActor(GetOwner());

  if (DebugEnemyAggro)
  {
    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0);
  }

  if (GetWorld()->LineTraceSingleByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
  {
    if (OutHit.bBlockingHit)
    {
      if (OutHit.Actor != nullptr)
      {
        bAggro = true;

        if (DebugEnemyAggro)
        {
          UE_LOG(LogGameplaySystem, Log, TEXT("Hit %s on left side"), *OutHit.Actor->GetName())
        }
      }
    }
  }
}

const bool UAggroComponent::GetAggro()
{
  return bAggro;
}

void UAggroComponent::SetAggro(bool Value)
{
  bAggro = Value;
}
