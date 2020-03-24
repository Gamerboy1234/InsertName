// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargeTowardsTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BrainComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "E_Charger.h"
#include "InsertNameV2.h"

EBTNodeResult::Type UChargeTowardsTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
  if (Setup(OwnerComp))
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

bool UChargeTowardsTarget::Setup(UBehaviorTreeComponent& OwnerComp)
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
          StartCharge();

          return true;
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
  
}
