// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Enemy.h"
#include "E_Charger.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API AE_Charger : public AMaster_Enemy
{
	GENERATED_BODY()
	
public:

  AE_Charger();
  /* Multiply enemy's base speed by this number */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  float ChargeSpeedMultiplier;
  /* Delay between enemy charging */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  float ChargeDelay;
  /* This is how close the enemy should get to it's target location the math is this Enemies X - Targets X if it's less than the error tolerance it stops */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  float ErrorTolerance;
  /* The range of the charger's trace calculated like so Actor's Location + Actor's froward vector x TraceRange */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  float TraceRange;
  /* If true enemy will always look towards player before moving towards it traced location */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  bool bDefaultToPlayer;
  /* Whether or not the enemy should be passive towards the player after it's first hit only applies once if the enemy is hit will become hostile again */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  bool bPassiveAfterHit;
  /* If true enemy will stop charging when it overlaps the player */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  bool bStopChargeOnPlayerOverlap;
  /* Specify which target to look at before charge if default to player is set to true disregard this value */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings", meta = (EditCondition = "!bDefaultToPlayer"))
  AActor* TargetActor;
};
