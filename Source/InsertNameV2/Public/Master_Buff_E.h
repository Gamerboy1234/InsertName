// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffData.h"
#include "Master_Buff_E.generated.h"

UCLASS()
class INSERTNAMEV2_API AMaster_Buff_E : public AActor
{
	GENERATED_BODY()
	
public:	

  AMaster_Buff_E();

  /* Whether or not the buff is already active on the given enemy */
  UPROPERTY(BlueprintReadWrite, Category = "Buff Info")
  bool bAlreadyApplied;
  /* The actual enemy to apply the buff to */
  UPROPERTY(BlueprintReadWrite, Category = "Buff Info")
  class AMaster_Enemy* TargetEnemy;
  /* Type of Buff to apply */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff Info")
  EBuffType BuffType;
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff Info")
  FBuffData BuffSettings;
  /* Returns the actual ID of the given buff */
  UFUNCTION(BlueprintPure, Category = "Enemy Buff Getter Functions")
  const int32 GetID();

  /* Removes buff from enemy */
  UFUNCTION(BlueprintCallable, Category = "Enemy Buff Functions")
  void RemoveBuff(AMaster_Buff_E* BuffToRemove, class AMaster_Enemy* CurrentActor);
  /* Applies buff to given enemy target */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Buff Events")
  void StartBuff();
  void StartBuff_Implementation();
  /* Applies a visual effect */
  void SpawnEffect(class AMaster_Enemy* CurrentActor);
  /* Stops the given buff applied to the enemy and returns enemy to default state */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Buff Events")
  void StopBuff();
  void StopBuff_Implementation();
  /* Sets up all needed buff data */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Buff Events")
  void SetUpBuff(class AMaster_Enemy* Target, AMaster_Buff_E* BuffToApply);
  void SetUpBuff_Implementation(class AMaster_Enemy* Target, AMaster_Buff_E* BuffToApply);
  /* If Buff should stack */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "!bRefresh"), Category = "Buff Info")
  bool bStack = true;
  /* If Buff should be refreshed when a buff of the same type is applied */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "!bTower"), Category = "Buff Info")
  bool bRefresh = false;
  /* Loops through current actors debuff array to see if buff already is applied */
  UFUNCTION(BlueprintPure, Category = "Enemy Buff functions")
  const bool IsBuffAlreadyApplied(AMaster_Buff_E* Buff, class AMaster_Enemy* CurrentActor);
  /* Returns the current stack count of the buff */
  UFUNCTION(BlueprintPure, Category = "Enemy Buff Getter Functions")
  const int32 GetCurrentStack();
  /* Remove then reapply the given buff */
  UFUNCTION(BlueprintCallable, Category = "Enemy Buff functions")
  void RefreshBuff(AMaster_Buff_E* BuffToRefresh, class AMaster_Enemy* CurrentActor);
  /* Increase the buff stack count by 1 */
  UFUNCTION(BlueprintCallable, Category = "Enemy Buff functions")
  void AddToBuffStack(AMaster_Buff_E* BuffToAddTo, class AMaster_Enemy* CurrentActor);

private:

  int32 ID;

  FBuffData CurrentInfo;

  TSubclassOf<class AMasterDamageEffect> BuffEffect;

  class AMasterDamageEffect* CurrentEffect;

  float BuffAmount;

  float BuffDuration;

  FVector EffectScale;

  int32 CurrentStackCount;

  void AddToStack(AMaster_Buff_E* BuffToAddTo);

  void UnPackSettings();

};
