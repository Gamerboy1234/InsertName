// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <cstdlib>
#include <iostream>
#include "MouseSword.generated.h"


UCLASS()

class INSERTNAMEV2_API UMouseSword : public UBlueprintFunctionLibrary
{
	
	GENERATED_BODY()
private:
		
		UFUNCTION(BlueprintPure, meta = (DisplayName = "SwordMousePosition", CompactNodeTitle = "SwordMousePosition", Keywords = "Sword"), Category = Game)
			static FString SwordMousePosition();
	
};
