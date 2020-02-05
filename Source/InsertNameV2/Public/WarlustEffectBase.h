// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperWarden.h"
#include "Master_Enemy.h"
#include "GameFramework/Actor.h"
#include "WarlustEffectBase.generated.h"

class UParticleSystemComponent;

UCLASS()
class INSERTNAMEV2_API AWarlustEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarlustEffectBase();

  UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
  UParticleSystemComponent* BeamEffect;

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BeamFunctions")
  void AddLine(APaperWarden* PlayerRef, AMaster_Enemy* EnemyRef);
  void AddLine_Implementation(APaperWarden* PlayerRef, AMaster_Enemy* EnemyRef);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BeamFunctions")
  void RemoveLine();
  void RemoveLine_Implementation();
};
