// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterDamageEffect.h"
#include "DebuffData.generated.h"

class AMasterDamageEffect;

USTRUCT(BlueprintType)
struct FDebuffData
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  float Damage = 0;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  float Ticks = 0;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  float Occurrence = 0;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  TSubclassOf<AMasterDamageEffect> DamageEffect;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  FVector EffectScale = FVector(1);

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
  bool bUseTicks = true;
};


UENUM(BlueprintType)		
enum class EDebuffType : uint8
{
  Fire UMETA(DisplayName = "Fire"),

  Stun UMETA(DisplayName = "Stun")
};
