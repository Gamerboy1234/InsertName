// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingCombatTextComponent.generated.h"

class AFloatingCombatTextBase;

/*
  This component will spawn floating combat text on the damaged actor
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INSERTNAMEV2_API UFloatingCombatTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatingCombatTextComponent();

  UPROPERTY(EditDefaultsOnly, Category = "Text Settings")
  float UpTime;

  UPROPERTY(EditDefaultsOnly, Category = "Text Settings")
  TSubclassOf<AFloatingCombatTextBase> TextManger;

  UFUNCTION(BlueprintCallable, Category = "Combat Text")
  void SpawnCombatText(float DamageApplied, AActor* DamagedActor);
};
