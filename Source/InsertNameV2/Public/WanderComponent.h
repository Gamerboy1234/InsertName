// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WanderComponent.generated.h"

/* This component will generate a random FVector within in a radius and moves it's owner to that location */
UCLASS( ClassGroup=(AI), meta=(BlueprintSpawnableComponent) )
class INSERTNAMEV2_API UWanderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWanderComponent();

public:	
	
  /* When not aggroed this enemy will try to find a random within this radius to move to radius moves with enemy */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wandering Settings")
  float WanderRadius;

  /* The minimum amount of time the charger waits to move to a random location */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wandering Settings")
  float WaitDelayMin;

  /* The maximum amount of time the charger waits to move to a random location */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wandering Settings")
  float WaitDelayMax;

  /* Generates a random wait time */
  UFUNCTION(BlueprintPure, Category = "Wander Functions")
  float CreateRandomWaitTime();

  /* Checks to see if the component is currently in use */
  UFUNCTION(BlueprintPure, Category = "Wander Functions")
  const bool GetInUse();

  /* Sets the value of bComponentInUse */
  UFUNCTION(BlueprintCallable, Category = "Wander Functions")
  void SetInUse(bool Value);

  /* Returns the current owners controller */
  UFUNCTION(BlueprintPure, Category = "Wander Functions")
  class AMaster_AIController* GetOwnerController();
  
  /* Returns the current target location */
  UFUNCTION(BlueprintPure, Category = "Wander Functions")
  FVector GetTargetLocation();

  /* Will move owning actor to a random location */
  UFUNCTION(BlueprintCallable, Category = "Wander Functions")
  void MoveOwnerToRandomPoint();

private:

  bool bComponentInUse;

  bool bOnDelay;

  FVector TargetLocation;

  void CreateDelay(float Delay);

  bool GetRandomPoint(float RandomPointDeviation, FVector& OutResult);

  void OnDelayEnd();

  class AMaster_AIController* FindOwnerController();
};
