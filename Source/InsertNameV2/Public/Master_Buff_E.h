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

  /* Whether or not the buff is already active on the given enemy */
  UPROPERTY(BlueprintReadWrite, Category = "Enemy Buff Info")
  bool bAlreadyApplied;
  /* The actual enemy to apply the buff to */
  UPROPERTY(BlueprintReadWrite, Category = "Enemy Buff Info")
  class AMaster_Enemy* TargetEnemy;
  /* Type of Buff to apply */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Buff Info")
  EBuffType BuffType;
  /* Returns the actual ID of the given buff */
  UFUNCTION(BlueprintPure, Category = "Enemy Buff Getter Functions")
  const int32 GetID();
  /* Returns the current stack count of the buff */
  UFUNCTION(BlueprintPure, Category = "Enemy Buff Getter Functions")
  const int32 GetCurrentStack();
  /* Returns current Buff Info */
  UFUNCTION(BlueprintPure, Category = "Enemy Buff Getter Functions")
  const FBuffData GetCurrentData();
  /* Removes buff from enemy */
  UFUNCTION(BlueprintCallable, Category = "Enemy Buff Functions")
  void RemoveBuff(AMaster_Buff_E* BuffToRemove);
  /* Increases the current stack by 1 */
  UFUNCTION(BlueprintCallable, Category = "Enemy Buff Functions")
  void AddToStack();
  /* Applies buff to given enemy target */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Buff Events")
  void StartBuff();
  void StartBuff_Implementation();
  /* Applies a visual effect */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Enemy Buff Events")
  void SetEffect(FBuffData BuffInfo);
  /* Stops the given buff applied to the enemy and returns enemy to default state */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Buff Events")
  void StopBuff();
  void StopBuff_Implementation();

  void SetUpBuff(FBuffData BuffData, class AMaster_Enemy* Target);


private:

  int32 ID;

  FBuffData CurrentInfo;

  int32 CurrentStackCount;

};
