// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Master_Gun.h"
#include "PlayerGun.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API APlayerGun : public AMaster_Gun
{
	GENERATED_BODY()

public:

  virtual void AttackKeyPressed() override;

  virtual void AttackKeyReleased() override;

  /* Amount of Time needed to charge the heavy attack attack */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float ChargeDelay;

  UPROPERTY(BlueprintReadWrite, Category = "Gun Settings")
  FTimerHandle ChargeTimer;

  virtual void StopGunFire_Implementation() override;

  UFUNCTION(BlueprintCallable, Category = "Gun Functions")
  void LightAttack();

  UFUNCTION(BlueprintCallable, Category = "Gun Functions")
  void HeavyAttack();

  UFUNCTION(BlueprintCallable, Category = "Gun Functions")
  void CompleteCharge();

  UPROPERTY(BlueprintReadOnly, Category = "Gun Vars")
  bool ChargeStarted;

  UPROPERTY(BlueprintReadOnly, Category = "Gun Vars")
  bool ChargeDone;

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Gun Events")
  void OnFireEnd();
};
