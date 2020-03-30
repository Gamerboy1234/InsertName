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

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UBoxComponent* HitBox;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UAggroComponent* AggroComp;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UWanderComponent* WanderComp;

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

  /* Returns the chargers current target */
  UFUNCTION(BlueprintPure, Category = "Charge Functions")
  AActor* GetCurrentTarget();

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  FTimeline MovementStateTimline;

  UPROPERTY()
  UCurveFloat* StateFloat;

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

  bool bOnDelay;

  bool bSetupFirstCharge;

  bool bIsTimelinePlaying;

  FVector TargetLocation;

  FVector StartLocation;

  FVector TargetDirection;

  void UpdateMovement();

  void FindTargetRotation();

  FVector GetDirection();

  FVector GetLocation();

  void CreateDelay(float Delay);

  void CreateDelay(float Delay, bool UpdateRotation);

  void OnDelayEnd();
};
