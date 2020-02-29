// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SavedSpellInfo.generated.h"

class AMaster_Spell;

USTRUCT(BlueprintType)
struct FSavedPlayerSpell
{
  GENERATED_USTRUCT_BODY()


   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saved Spell Info")
   float SavedCoolDownTime;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saved Spell Info")
   float SavedCurrentTimeLinePostion;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saved Spell Info")
   float SavedCurrentScalerValue;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saved Spell Info")
   bool SavedbWasOnCooldown;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saved Spell Info")
   bool SavedbWasPaused;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saved Spell Info")
   UClass* SpellToSave;
};
