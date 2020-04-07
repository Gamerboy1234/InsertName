// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySightComponent.generated.h"

/* This component will draw a line in the direction the enemy is facing if anything is in front of the enemy (excluding the player) will return as blocked */
UCLASS( ClassGroup=(AI), meta=(BlueprintSpawnableComponent) )
class INSERTNAMEV2_API UEnemySightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemySightComponent();

  /* Checks to see if enemy sight is currently blocked */
  UFUNCTION(BlueprintPure, Category = "Sight Functions")
  const bool GetSightBlocked();

  /* Returns the hit location of the sight trace */
  UFUNCTION(BlueprintPure, Category = "Sight Functions")
  FVector GetHitLocation();

  /* The range of the sight trace */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sight Settings")
  float SightRange;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:

  FVector HitLocation;

  class APaperWarden* PlayerRef;

};
