// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySightComponent.h"
#include "GeneralFunctions.h"
#include "PaperWarden.h"
#include "GameFramework/Actor.h"
#include "InsertNameV2.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

static int32 DebugEnemySight = 0;
FAutoConsoleVariableRef CVARDebugEnemySight(
  TEXT("Sight.DebugEnemySight"),
  DebugEnemySight,
  TEXT("Draw enemy line of sight"),
  ECVF_Cheat);

// Sets default values for this component's properties
UEnemySightComponent::UEnemySightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

  SightRange = 500.0f;
}

void UEnemySightComponent::CheckSight()
{
  FHitResult OutHit;

  FVector StartLocation = GetOwner()->GetActorLocation();
  FVector EndLocation = GetOwner()->GetActorRotation().Vector() * SightRange + StartLocation;

  FCollisionQueryParams CollisionParams;

  if (DebugEnemySight)
  {
    DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 1, 0, 1);
  }

  if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
  {
    if (OutHit.bBlockingHit)
    {
      if (OutHit.Actor != NULL)
      {

        if (DebugEnemySight)
        {
          UE_LOG(LogGameplaySystem, Log, TEXT("Hit : %s"), *OutHit.Actor->GetName())
        }

        APaperCharacter* HitPlayer = Cast<APaperWarden>(OutHit.Actor);

        if (HitPlayer)
        {
          HitLocation = OutHit.Location;
          bSightBlocked = false;
        }
        else
        {
          HitLocation = OutHit.Location;
          bSightBlocked = true;
        }
      }
      else
      {
        HitLocation = EndLocation;
        bSightBlocked = false;
      }
    }
    else
    {
      HitLocation = EndLocation;
      bSightBlocked = false;
    }
  }
  else
  {
    HitLocation = EndLocation;
    bSightBlocked = false;
  }
}

const bool UEnemySightComponent::GetSightBlocked()
{
  return bSightBlocked;
}

FVector UEnemySightComponent::GetHitLocation()
{
  return HitLocation;
}
