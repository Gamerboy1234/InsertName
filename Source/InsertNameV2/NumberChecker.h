// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NumberChecker.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UNumberChecker : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
  private:

    UFUNCTION(BlueprintPure, meta = (DisplayName = "IsNumberNegative", CompactNodeTitle = "NumberNegative", Keywords = "IsNumberNegative"), Category = Game)
      static bool IsNumberNegative(float number);
};
