// Fill out your copyright notice in the Description page of Project Settings.


#include "WanderComponent.h"
#include "Master_AIController.h"
#include "GeneralFunctions.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "Master_Enemy.h"
#include "InsertNameV2.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWanderComponent::UWanderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

  WanderRadius = 500.0f;
  WaitDelayMin = 2.0f;
  WaitDelayMax = 5.0f;
}

void UWanderComponent::MoveOwnerToRandomPoint()
{
  bool bGotLocation = false;

  if (GetInUse() && !bOnDelay)
  {
    if (!bGotLocation)
    {
      AMaster_AIController* LocalController = GetOwnerController();

      if (LocalController)
      {
        if (GetRandomPoint(WanderRadius, TargetLocation))
        {
          UGeneralFunctions::RotateActorToVector(GetOwner(), TargetLocation);
          TargetLocation.Y = 0;
        }
        else
        {
          UE_LOG(LogMasterEnemy, Error, TEXT("Failed to get Random location"))
          return;
        }

        LocalController->MoveToLocation(TargetLocation);
        bGotLocation = true;
        CreateDelay(CreateRandomWaitTime());

      }
    }
    else
    {
      UE_LOG(LogMasterEnemy, Error, TEXT("Failed to MoveOwnerToRandomPoint Controller was not valid"))
      return;
    }
  }
}

bool UWanderComponent::GetRandomPoint(float RandomPointDeviation, FVector& OutResult)
{
  UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

  if (NavSystem)
  {
    FNavLocation Result;
    bool bSuccess = NavSystem->GetRandomReachablePointInRadius(GetOwner()->GetActorLocation(), RandomPointDeviation, Result);
    OutResult = Result;
    return bSuccess;
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Failed to GetRandomPoint NavSystem was not valid"))
    return false;
  }
}

void UWanderComponent::SetInUse(bool Value)
{
  bComponentInUse = Value;
}

void UWanderComponent::CreateDelay(float Delay)
{
  FTimerHandle DelayTimer;

  bOnDelay = true;

  GetOwner()->GetWorldTimerManager().SetTimer(DelayTimer, this, &UWanderComponent::OnDelayEnd, Delay, false);
}

class AMaster_AIController* UWanderComponent::GetOwnerController()
{
  return FindOwnerController();
}

FVector UWanderComponent::GetTargetLocation()
{
  return TargetLocation;
}

const bool UWanderComponent::GetInUse()
{
  return bComponentInUse;
}

float UWanderComponent::CreateRandomWaitTime()
{
  return FMath::RandRange(WaitDelayMin, WaitDelayMax);
}

void UWanderComponent::OnDelayEnd()
{
  bOnDelay = false;
}

AMaster_AIController* UWanderComponent::FindOwnerController()
{
  AMaster_Enemy* LocalEnemy = Cast<AMaster_Enemy>(GetOwner());

  if (LocalEnemy)
  {
    AMaster_AIController* LocalController = Cast<AMaster_AIController>(LocalEnemy->GetController());

    if (LocalController)
    {
      return LocalController;
    }
    else
    {
      UE_LOG(LogMasterEnemy, Error, TEXT("Failed to get GetOwnerController cast to AMaster_AIController failed"))
      return nullptr;
    }
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Failed to get GetOwnerController cast to AMaster_Enemy failed"))
    return nullptr;
  }
}
