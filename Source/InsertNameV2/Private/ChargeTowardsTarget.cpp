// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargeTowardsTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BrainComponent.h"
#include "GameFramework/Pawn.h"
#include "PaperWarden.h"
#include "TimerManager.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "E_Charger.h"
#include "GeneralFunctions.h"
#include "InsertNameV2.h"

EBTNodeResult::Type UChargeTowardsTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
  bCreateNodeInstance = true;

  if (GetControlledEnemy(OwnerComp))
  {
    FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
    return EBTNodeResult::InProgress;
  }
  else
  {
    FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
    return EBTNodeResult::Aborted;
  }
}

bool UChargeTowardsTarget::GetControlledEnemy(UBehaviorTreeComponent& OwnerComp)
{
  UBlackboardComponent* CurrentBlackBoard = OwnerComp.GetBlackboardComponent();
  UBrainComponent* Brain = CurrentBlackBoard->GetBrainComponent();
  CurrentPawn = Brain->GetAIOwner()->GetPawn();
  CurrentEnemy = Cast<AE_Charger>(CurrentPawn);
 
  if (CurrentBlackBoard)
  {
    if (Brain)
    {
      if (CurrentPawn)
      {
        if (CurrentEnemy)
        {
          PlayerRef = UGeneralFunctions::GetPlayer(this);

          if (PlayerRef)
          {
            StartCharge();
            return true;
          }
          else
          {
            UE_LOG(LogMasterEnemy, Error, TEXT("Failed to start Charge enemy %s failed to get player"), *CurrentPawn->GetName())
            return false;
          }
        }
        else
        {
          UE_LOG(LogMasterEnemy, Error, TEXT("Failed to start Charge enemy %s is not of class E_Charger"), *CurrentPawn->GetName())
          return false;
        }
      }
      else
      {
        UE_LOG(LogMasterEnemy, Error, TEXT("Failed to start charge CurrentPawn was not vaild"))
        return false;
      }
    }
    else
    {
      UE_LOG(LogMasterEnemy, Error, TEXT("Failed to start Charge failed to get brain"))
      return false;
    }
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Failed to start Charge failed to get CurrentBlackBoard"))
    return false;
  }
}

void UChargeTowardsTarget::StartCharge()
{
  UpdateMovement();

  // Create Movement Timer
  CurrentEnemy->GetWorldTimerManager().SetTimer(ChargeTimer, this, &UChargeTowardsTarget::ChargeDelay, 0.01f, true);

  // Creates delay timer
  SetDelay();
}

void UChargeTowardsTarget::ChargeToTarget()
{

}

FVector UChargeTowardsTarget::GetDirection()
{
  FVector TraceStart = CurrentEnemy->GetActorLocation();
  FVector TraceEnd = CurrentEnemy->TraceRange * CurrentEnemy->GetActorForwardVector() + TraceStart;

  FHitResult OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldStatic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldDynamic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel13);

  FCollisionQueryParams CollisionParms;
  CollisionParms.AddIgnoredActor(CurrentEnemy);

  DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2);

  if (GetWorld()->LineTraceSingleByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
  {
    if (OutHit.bBlockingHit)
    {
      return UGeneralFunctions::GetUnitVector(CurrentEnemy->GetActorLocation(), OutHit.ImpactPoint);
    }
    else
    {
      return UGeneralFunctions::GetUnitVector(CurrentEnemy->GetActorLocation(), OutHit.TraceEnd);
    }
  }
  else
  {
    return UGeneralFunctions::GetUnitVector(CurrentEnemy->GetActorLocation(), TraceEnd);
  }
}

FVector UChargeTowardsTarget::GetLocation()
{
  FVector TraceStart = CurrentEnemy->GetActorLocation();
  FVector TraceEnd = CurrentEnemy->TraceRange * CurrentEnemy->GetActorForwardVector() + TraceStart;

  FHitResult OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldStatic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldDynamic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel13);

  FCollisionQueryParams CollisionParms;
  CollisionParms.AddIgnoredActor(CurrentEnemy);

  DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2);

  if (GetWorld()->LineTraceSingleByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
  {
    if (OutHit.bBlockingHit)
    {
      return OutHit.ImpactPoint;
    }
    else
    {
      return OutHit.TraceEnd;
    }
  }
  else
  {
    return TraceEnd;
  }
}

void UChargeTowardsTarget::UpdateLocationAndDirection()
{
  RotateToTarget();
  TargetLocation = GetLocation();
  TargetDirection = GetDirection();
}

void UChargeTowardsTarget::RotateToTarget()
{
  if (CurrentEnemy)
  {
    if (PlayerRef)
    {
      if (CurrentEnemy->bDefaultToPlayer)
      {
        FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(CurrentEnemy->GetActorLocation(), PlayerRef->GetActorLocation());

        NewRotation.Pitch = 0;
        NewRotation.Roll = 0;

        CurrentEnemy->SetActorRotation(NewRotation);
      }
      else
      {
        if (CurrentEnemy->TargetActor)
        {
          FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(CurrentEnemy->GetActorLocation(), CurrentEnemy->TargetActor->GetActorLocation());

          NewRotation.Pitch = 0;
          NewRotation.Roll = 0;

          CurrentEnemy->SetActorRotation(NewRotation);
        }
        else
        {
          UE_LOG(LogMasterEnemy, Error, TEXT("Enemy %s failed to rotate TargetActor is not valid"), *CurrentEnemy->GetName())
        }
      }
    }
    else
    {
      UE_LOG(LogMasterEnemy, Error, TEXT("Enemy %s failed to rotate PlayerRef is not valid"), *CurrentEnemy->GetName())
    }
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Enemy %s failed to rotate CurrentEnemy is not valid"))
  }
}

void UChargeTowardsTarget::ChargeDelay()
{
  bCanCharge = true;
  CurrentEnemy->ResetSpriteColor();

  ChargeToTarget();
}

void UChargeTowardsTarget::UpdateMovement()
{
  bCanCharge = false;
  CurrentEnemy->GetSprite()->SetSpriteColor(FLinearColor::Green);
  UpdateLocationAndDirection();
}

void UChargeTowardsTarget::SetDelay()
{
  FTimerHandle ChargeDelayTimer;

  if (ChargeDelayTimer.IsValid())
  {
    CurrentEnemy->GetWorldTimerManager().ClearTimer(ChargeDelayTimer);
  }
  // Delay Timer
  CurrentEnemy->GetWorldTimerManager().SetTimer(ChargeDelayTimer, this, &UChargeTowardsTarget::ChargeDelay, CurrentEnemy->ChargeDelay, false);
}

void UChargeTowardsTarget::EndMovement()
{
  AAIController* EnemyController = Cast<AAIController>(CurrentEnemy->GetController());

  UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(EnemyController->GetBrainComponent());

  if (OwnerComp)
  {
    FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Failed to stop Charge failed to get UBehaviorTreeComponent"))
  }
}
