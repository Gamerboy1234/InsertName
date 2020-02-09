// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebuffData.h"
#include "Master_Debuff_E.generated.h"

class AMasterDamageEffect;
class AMaster_Enemy;

UCLASS()
class INSERTNAMEV2_API AMaster_Debuff_E : public AActor
{
	GENERATED_BODY()
	
public:

  AMaster_Debuff_E();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable , Category = "Enemy Debuffs")
  void StartDamageTimer(AMaster_Debuff_E* DebuffToApply, AMaster_Enemy* CurrentActor, FDebuffData DebuffInfo);
  void StartDamageTimer_Implementation(AMaster_Debuff_E* DebuffToApply, AMaster_Enemy* CurrentActor, FDebuffData DebuffInfo);

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debuff Settings")
  EDebuffType DebuffType;

  UFUNCTION(BlueprintCallable, Category = "Enemy Debuffs")
  void RemoveDebuff(AMaster_Debuff_E* DebuffToRemove, AMaster_Enemy* CurrentActor);

  UFUNCTION(BlueprintCallable, Category = "Enemy Debuffs")
  void SpawnEffect(AMaster_Enemy* CurrentActor);

  UFUNCTION(BlueprintPure, Category = "Enemy Debuffs")
  const float GetTotalTime();

  UFUNCTION(BlueprintPure, Category = "Enemy Debuffs")
  const bool IsDebuffAlreadyApplied(AMaster_Debuff_E* Debuff, AMaster_Enemy* CurrentActor);

  UFUNCTION(BlueprintNativeEvent, Category = "Enemy Debuffs")
  void StartDebuff();
  void StartDebuff_Implementation();

  UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Debuffs")
  void OnDebuffStop();

  UFUNCTION(BlueprintPure, Category = "Enemy Debuffs")
  float GetCurrentTickCount();

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  int32 ID;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  AMasterDamageEffect* CurrentEffect;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  AMaster_Enemy* TargetEnemy;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  FTimerHandle DebuffTimer;
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "!bRefresh"), Category = "Debuff Settings")
  bool bTower;
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "!bTower"), Category = "Debuff Settings")
  bool bRefresh;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  float Damage;

  UPROPERTY(BlueprintReadWrite, Category = "Debuff Settings")
  float Ticks;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  float Occurrence;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  TSubclassOf<AMasterDamageEffect> DamageEffect;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  FVector EffectScale;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  bool bUseTicks;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  int32 CurrentStackCount;

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool CanContinueDebuff(AMaster_Enemy* CurrentActor);
  /* Finds debuff in CurrentActor's debuff array and add given debuff to it's stack */
  UFUNCTION(BlueprintCallable, Category = "Debuff Functions")
  void AddDebuffToStack(AMaster_Debuff_E* DebuffToAdd, AMaster_Enemy* CurrentActor);
  /* Re apply the given debuff */
  UFUNCTION(BlueprintCallable, Category = "Debuff Functions")
  void RefreshDebuff(AMaster_Debuff_E* DebuffToRefresh, AMaster_Enemy* CurrentActor, FDebuffData DebuffInfo);

private:

  void DecrementTick();
  
  /* Increases enemy stack by one */
  void AddToStack(AMaster_Debuff_E* DebuffToAddTo);
};

