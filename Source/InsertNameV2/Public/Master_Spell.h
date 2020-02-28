// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Pickup.h"
#include "SpellInfo.h"
#include "Master_Spell.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API AMaster_Spell : public AMaster_Pickup
{
	GENERATED_BODY()
	
public:

  AMaster_Spell();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void OnCastComplete();
  virtual void OnCastComplete_Implementation();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void OnSpellCastStart();
  virtual void OnSpellCastStart_Implementation();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void BeginSpellCast();
  void BeginSpellCast_Implementation();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void PauseCoolDown();
  void PauseCoolDown_Implementation();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void ResumeCoolDown();
  void ResumeCoolDown_Implementation();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spell Events")
  void OnCoolDown(bool ResumeCooldown);

  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void ResetSpell();

  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void SetupPause();

  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void SetupResume();

  virtual void UseItem_Implementation() override;

  UFUNCTION(BlueprintPure, Category = "Spell Functions")
  const bool GetCurrentlyOnCooldown();

  UFUNCTION(BlueprintPure, Category = "Spell Functions")
  const bool GetCurrentlyCasting();

  UFUNCTION(BlueprintPure, Category = "Spell Functions")
  const float GetDefaultCoolDownTime();
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  float CoolDownTime;
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  float CurrentTimeLinePostion;
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool bCurrentlyCasting;
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool bCurrentlyOnCooldown;
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  float CurrentScalerValue;
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool bCoolDownPaused;
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool bContinueFromLastCoolDown;

private:

  float DefaultCoolDownTime;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
};
