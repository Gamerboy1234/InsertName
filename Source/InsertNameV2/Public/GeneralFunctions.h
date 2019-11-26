// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralFunctions.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UGeneralFunctions : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintPure, meta = (DisplayName = "IsNumberNegative", CompactNodeTitle = "NumberNegative", Keywords = "IsNumberNegative"), Category = Math)
  static bool IsNumberNegative(float number);
  UFUNCTION(BlueprintPure, meta = (DisplayName = "TickBuff", CompactNodeTitle = "Buff", Keywords = "TickBuff"), Category = Math)
    static float TickDamage(float Tick, float GunDamage, float BuffAmount);
  UFUNCTION(BlueprintPure, meta = (DisplayName = "CalcReflectionVector", CompactNodeTitle = "CalcReflectionVector", Keywords = "CalcReflectionVector"), Category = Math)
    static FVector CalcReflectionVector(FVector VectorToReflect, FVector Normal);
  UFUNCTION(BlueprintPure, meta = (DisplayName = "LeftOrRight?", CompactNodeTitle = "LeftOrRight?", Keywords = "LeftOrRight"), Category = Game)
    static bool MouseLeftOrRight(float mouseX, float mouseY);
  UFUNCTION(BlueprintPure, meta = (DisplayName = "RandomNumberNoRepeat", CompactNodeTitle = "RandomNumber", Keywords = "RandomNumber"), Category = Math)
    static int RandomNumber(int max, int min);
};
