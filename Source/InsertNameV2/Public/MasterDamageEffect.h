// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterDamageEffect.generated.h"

class AMaster_Enemy;

UCLASS()
class INSERTNAMEV2_API AMasterDamageEffect : public AActor
{
	GENERATED_BODY()
	
public:	
  
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect Setup")
  void SetEffect(AActor* CurrentActor);
  void SetEffect_Implementation(AActor* CurrentActor);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect Setup")
  void RemoveEffect();
  void RemoveEffect_Implementation();

  UFUNCTION(BlueprintCallable, Category = "CleanUp")
  void CleanUpEffect(TSubclassOf<AMasterDamageEffect> EffectToCleanUp);

  UPROPERTY(BlueprintReadWrite, Category = "Effect Setup")
  FVector EffectScale;

};
