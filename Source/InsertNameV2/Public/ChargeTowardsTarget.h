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

  class AE_Charger* CurrentEnemy;

  class APawn* CurrentPawn;

  void StartCharge();

  void ChargeToTarget();

  FVector GetDirection();
  
  FVector GetLocation();

  void UpdateLocationAndDirection();

  void RotateToTarget();

  bool GetControlledEnemy(UBehaviorTreeComponent& OwnerComp);

  class APaperWarden* PlayerRef;

  void ChargeDelay();

  void UpdateMovement();

  void SetDelay();
  
  void EndMovement();

  bool bCanCharge;

  FVector TargetLocation;

  FVector TargetDirection;

  FTimerHandle ChargeTimer;
};
