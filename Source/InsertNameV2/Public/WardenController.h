// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WardenController.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API AWardenController : public APlayerController
{
	GENERATED_BODY()

public:

  virtual void BuildInputStack(TArray< UInputComponent* >& InputStack) override;
	
};
