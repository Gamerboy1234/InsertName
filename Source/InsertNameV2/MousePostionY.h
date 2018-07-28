// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MousePostionY.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UMousePostionY : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
private:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "MouseY", CompactNodeTitle = "MouseY", Keywords = "MouseY"), Category = Game)
		static int MouseY();
	
	
};
