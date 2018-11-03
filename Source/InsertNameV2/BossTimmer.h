// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BossTimmer.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UBossTimmer : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private: 
	
		UFUNCTION(BlueprintPure, meta = (DisplayName = "BossTimer", CompactNodeTitle = "BossTimer", Keywords = "BossTimer"), Category = Game)
		static bool BossTimmer(float secondsToDelay);
	
	
};
