// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Enemy.h"
#include "Components/TimelineComponent.h"
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
  /* The range of the charger's trace calculated like so Actor's Location + Actor's froward vector x TraceRange */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  float TraceRange;
  /* Knockback to apply when player is hit */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  float KnockBackMultipler;
  /* The amount of time the beetle should charge for */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  float ChargeTime;
  /* If true enemy will always look towards player before moving towards it traced location */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings")
  bool bDefaultToPlayer;
  /* Specify which target to look at before charge if default to player is set to true disregard this value */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charge Settings", meta = (EditCondition = "!bDefaultToPlayer"))
  AActor* TargetActor;
  /* When not aggroed this enemy will try to find a random within this radius to move to radius moves with enemy */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wandering Settings")
  float WanderRadius;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UBoxComponent* HitBox;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UAggroComponent* AggroComp;

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wandering Settings")
  float WaitDelay;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

  /* Reads the value of bAggro */
  UFUNCTION(BlueprintPure, Category = "Charge Functions")
  const bool GetAggro();

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  FTimeline MovementStateTimline;

  UPROPERTY()
  UCurveFloat* StateTimeline;

  FTimeline ChargeTimeline;

  UPROPERTY()
  UCurveFloat* ChargerFloat;

  UFUNCTION()
  void StartCharge();

  UFUNCTION()
  void ChargeToTarget(float Value);

  UFUNCTION()
  void OnChargeFinish();

  UFUNCTION()
  void ChargerMovmentState(float Value);

private:

  bool bIsMoving;

  bool bAggro;

  bool bOnDelay;

  bool bIsTimelinePlaying;

  FVector TargetLocation;

  FVector StartLocation;

  FVector TargetDirection;

  void UpdateMovement();

  void FindTargetRotation();

  void RotateToPoint(FVector Location);

  void RotateToPoint(AActor* ActorToRotateTo);

  FVector GetDirection();

  FVector GetLocation();

  void MoveToRandomPoint();

  bool GetRandomPoint(float RandomPointDeviation, FVector& OutResult);

  void CreateDelay(float Delay);

  void CreateDelay(float Delay, bool UpdateRotation);

  void OnDelayEnd();

  bool CheckAggro();
};
