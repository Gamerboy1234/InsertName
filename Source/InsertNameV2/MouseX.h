// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MouseX.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UMouseX : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
private:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "MouseX", CompactNodeTitle = "MouseX", Keywords = "MouseX"), Category = Game)
		static int MouseX();
	
	
};
