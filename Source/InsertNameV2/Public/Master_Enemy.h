// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Master_Enemy.generated.h"

class UBehaviorTree;
class AAIController;

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API AMaster_Enemy : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

  AMaster_Enemy(const FObjectInitializer& ObjectInitializer);

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float CurrentHP;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float MaxHP;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float ActorDespawnDelay;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float HPBarHideDelay;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  bool bCanBeStunned;

  UPROPERTY(EditAnywhere, Category = "AI")
  UBehaviorTree* BehaviorTreeToUse;

  UPROPERTY(EditAnywhere, Category = "AI")
  bool bUseBT;

  UPROPERTY(EditAnywhere, Category = "AI")
  bool bAddToKillCount;

  UPROPERTY(EditAnywhere, Category = "AI")
  AAIController* ControllerToUse;

  UPROPERTY(BlueprintReadOnly, Category = "AI")
  bool bAggroed;

  UPROPERTY(BlueprintReadWrite, Category = "Movement")
  bool bIsFlying;

  UPROPERTY(EditAnywhere, Category = "Damage")
  float DamageToPlayer;

  UPROPERTY(EditDefaultsOnly, Category = "Movement")
  FLinearColor NewColor;

private:

  bool bTakenDamage;

  bool bIsDead;

  TSubclassOf<AActor> PlayerRef;

  TSubclassOf<AActor> WarlustEffect;
};
