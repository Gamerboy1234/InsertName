// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BoxMovement.h"
#include "PaperBoxCharacter.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API APaperBoxCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
  // Sets default values for this character's properties
  APaperBoxCharacter(const FObjectInitializer& ObjectInitializer);

  UFUNCTION(BlueprintCallable, Category = "Movement")
    FORCEINLINE class UBoxMovement* GetMyMovementComponent() const { return BoxMovement; }

public: 
  virtual void PostInitializeComponents() override;

private:
  UBoxMovement* BoxMovement;
};
