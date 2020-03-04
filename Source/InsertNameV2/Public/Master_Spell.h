// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Pickup.h"
#include "SpellInfo.h"
#include "SavedSpellInfo.h"
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

  /* Will end the current spell cast then will either apply a cooldown or reset the spell */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void OnCastComplete(bool bSuccess);
  virtual void OnCastComplete_Implementation(bool bSuccess);
  /* Constructs the player spell cast by default only calls BeginSpellCast */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void OnSpellCastStart();
  virtual void OnSpellCastStart_Implementation();
  /* This where the actually code is called */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void BeginSpellCast();
  void BeginSpellCast_Implementation();
  /* Will pause the spell cooldown timer */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void PauseCoolDown();
  void PauseCoolDown_Implementation();
  /* Will resume the current spell cooldown timer */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spell Events")
  void ResumeCoolDown();
  void ResumeCoolDown_Implementation();
  /* This the actual event will start a cooldown timer */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spell Events")
  void OnCoolDown(bool ResumeCooldown, float Time);
  /* Resets the spell back to it's default values */
  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void ResetSpell();
  /* Sets up all the needed values to pause the current cooldown timer */
  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void SetupPause();
  /* Sets up all the needed values to resume the current cooldown timer */
  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void SetupResume();
  /* Override UseItem to and make it start the spell cast */
  virtual void UseItem_Implementation() override;

  UFUNCTION(BlueprintPure, Category = "Spell Functions")
  const bool GetCurrentlyOnCooldown();

  UFUNCTION(BlueprintPure, Category = "Spell Functions")
  const bool GetCurrentlyCasting();

  UFUNCTION(BlueprintPure, Category = "Spell Functions")
  const float GetDefaultCoolDownTime();
  
  /* The length of the cooldown timer */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  float CoolDownTime;
  /* Current position the cooldown timeline */
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  float CurrentTimeLinePostion;
  /* Checks to see if player is already casting a spell */
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool bCurrentlyCasting;
  /* Tells if spell is already on cooldown */
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool bCurrentlyOnCooldown;
  /* Current scale the cooldown timer material */
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  float CurrentScalerValue;
  /* Tells if the current cooldown timer is paused */
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool bCoolDownPaused;
  /* Whether or not the continue from the last position of the cooldown timer */
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool bContinueFromLastCoolDown;

  /* Gets saved spell data and sets all vars to saved info */
  void UnpackSpellInfo(FSavedPlayerSpell NewSpellInfo);

private:

  float DefaultCoolDownTime;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
};
