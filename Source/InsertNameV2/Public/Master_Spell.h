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

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spell Events")
  void OnCoolDown();

  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void ResetSpell();

  virtual void UseItem_Implementation() override;

  UFUNCTION(BlueprintPure, Category = "Spell Functions")
  bool GetCurrentlyOnCooldown();

  UFUNCTION(BlueprintPure, Category = "Spell Functions")
  bool GetCurrentlyCasting();
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  float CoolDownTime;
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool CurrentlyCasting;
  UPROPERTY(BlueprintReadWrite, Category = "Item Info")
  bool CurrentlyOnCooldown;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
};
