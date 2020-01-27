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

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable , Category = "Enemy Debuffs")
  void StartDamageTimer(AMaster_Debuff_E* DebuffToApply, AMaster_Enemy* CurrentActor, FDebuffData DebuffInfo);
  void StartDamageTimer_Implementation(AMaster_Debuff_E* DebuffToApply, AMaster_Enemy* CurrentActor, FDebuffData DebuffInfo);

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debuff Settings")
  EDebuffType DebuffType;

  UFUNCTION(BlueprintCallable, Category = "Enemy Debuffs")
  void RemoveDebuff(AMaster_Debuff_E* DebuffToRemove);

  UFUNCTION(BlueprintCallable, Category = "Enemy Debuffs")
  void SpawnEffect(AMaster_Enemy* CurrentActor);

  UFUNCTION(BlueprintCallable, Category = "Enemy Debuffs")
  AMaster_Debuff_E* FindDebuffByID(AMaster_Debuff_E* Debuff);

  UFUNCTION(BlueprintPure, Category = "Enemy Debuffs")
  const float GetTotalTime();

  UFUNCTION(BlueprintPure, Category = "Enemy Debuffs")
  const bool IsDebuffAlreadyApplied(AMaster_Debuff_E* Debuff, AMaster_Enemy* CurrentActor);

  UFUNCTION(BlueprintNativeEvent, Category = "Enemy Debuffs")
  void StartDebuff();
  void StartDebuff_Implementation();

  UFUNCTION(BlueprintPure, Category = "Enemy Debuffs")
  float GetCurrentTickCount();

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  int32 ID;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  bool bAlreadApplied;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  AMasterDamageEffect* CurrentEffect;

  UPROPERTY(BlueprintReadWrite, Category = "Debuff Settings")
  AMaster_Enemy* CurrentEnemy;

  UPROPERTY(BlueprintReadOnly, Category = "Debuff Settings")
  FTimerHandle DebuffTimer;

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

  UFUNCTION(BlueprintCallable, Category = "Enemy Debuffs")
  void SetupDebuffInfo(FDebuffData DebuffInfo);
};
