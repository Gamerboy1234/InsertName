// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChargeTowardsTarget.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UChargeTowardsTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

  virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

  EBTNodeResult::Type CurrentCallResult;

  class AMaster_Enemy* CurrentEnemy;

  class APawn* CurrentPawn;

  void StartCharge();

  bool Setup(UBehaviorTreeComponent& OwnerComp);

};
