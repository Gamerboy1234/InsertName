// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AggroComponent.generated.h"

/* This component will fire off traces from both sides of actor looking for the player character if found enemy will be aggroed */
UCLASS( ClassGroup=(AI), meta=(BlueprintSpawnableComponent) )
class INSERTNAMEV2_API UAggroComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAggroComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  /* Reads the value of bAggro */
  UFUNCTION(BlueprintPure, Category = "Aggro Functions")
  const bool GetAggro();

  /* Manually set actor aggro */
  UFUNCTION(BlueprintCallable, Category = "Aggro Functions")
  void SetAggro(bool Value);
  /* How far along the trace should go from the actors current position */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro Settings")
  FVector AggroRange;
  /* If true the actor will fire a trace on both sides */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro Settings")
  bool bTwoSided;
  /* whether or not to fire a trace off the actors right side only use sable if bTwoSided is false */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro Settings", meta = (EditCondition = "!bTwoSided"))
  bool bTraceRight;
  /* whether or not to fire a trace off the actors left side only use sable if bTwoSided is false */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro Settings", meta = (EditCondition = "!bTwoSided"))
  bool bTraceLeft;

private:

  bool bAggro;

  void TraceRight();

  void TraceLeft();

};
