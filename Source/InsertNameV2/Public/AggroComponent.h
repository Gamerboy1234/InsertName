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

  UFUNCTION(BlueprintPure, Category = "Aggro Functions")
  const bool GetAggro();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aggro Settings")
  float AggroRange;

private:

  bool bAggro;

  void TraceRight();

  void TraceLeft();

};
