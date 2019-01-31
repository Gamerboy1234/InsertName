// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Damage_Increass_.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UDamage_Increass_ : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()
private:

    UFUNCTION(BlueprintPure, meta = (DisplayName = "DamageBuff", CompactNodeTitle = "Buff", Keywords = "DamageBuff"), Category = Game)
    static float IncreaseDamage(float Damage, float DamageAmount);
};
