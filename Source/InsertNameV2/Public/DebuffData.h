// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterDamageEffect.h"
#include "DebuffData.generated.h"

class AMasterDamageEffect;
class UTexture2D;
class UPaperSpriteComponent;

USTRUCT(BlueprintType)
struct FDebuffData
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FText Name;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FText Description;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float Damage = 0;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float Ticks = 0;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float Occurrence = 0;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TSubclassOf<AMasterDamageEffect> DamageEffect;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FVector EffectScale = FVector(1);

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  bool bUseTicks = true;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UTexture2D* DebuffIcon;
};


UENUM(BlueprintType)		
enum class EDebuffType : uint8
{
  Fire UMETA(DisplayName = "Fire"),

  Stun UMETA(DisplayName = "Stun")
};
