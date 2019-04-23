// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RandomNumberNoRepeat.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API URandomNumberNoRepeat : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()
    UFUNCTION(BlueprintPure, meta = (DisplayName = "RandomNumberNoRepeat", CompactNodeTitle = "RandomNumber", Keywords = "RandomNumber"), Category = Math)
    static int RandomNumber(int max, int min); 
	
};
