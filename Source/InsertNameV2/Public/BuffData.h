// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffData.generated.h"

class AMasterDamageEffect;

USTRUCT(BlueprintType)
struct FBuffData
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  float BuffAmount;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  float BuffDuration;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  TSubclassOf<AMasterDamageEffect> DamageEffect;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  FVector EffectScale = FVector(1);

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "!bRefresh"))
  bool bTower = true;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "!bTower"))
  bool bRefresh = false;
};


UENUM(BlueprintType)
enum class EBuffType : uint8
{
  Leeched UMETA(DisplayName = "Leeched")
};
