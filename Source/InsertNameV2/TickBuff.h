// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TickBuff.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UTickBuff : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
    UFUNCTION(BlueprintPure, meta = (DisplayName = "TickBuff", CompactNodeTitle = "Buff", Keywords = "TickBuff"), Category = Math)
    static float TickDamage(float Tick, float GunDamage, float BuffAmount);
};
