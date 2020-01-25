// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingCombatTextBase.generated.h"

UCLASS()
class INSERTNAMEV2_API AFloatingCombatTextBase : public AActor
{
	GENERATED_BODY()
	
public:	

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat Text")
  void SpawnFloatingCombatText(float DamageApplied, float UpTime, AActor* HitActor);
  virtual void SpawnFloatingCombatText_Implementation(float DamageApplied, float UpTime, AActor* HitActor);

};
