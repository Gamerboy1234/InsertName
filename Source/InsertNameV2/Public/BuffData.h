// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffData.generated.h"

class AMasterDamageEffect;
class UTexture2D;

USTRUCT(BlueprintType)
struct FBuffData
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float BuffAmount;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float BuffDuration;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TSubclassOf<AMasterDamageEffect> BuffEffect;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FVector EffectScale = FVector(1);

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UTexture2D* BuffIcon;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FText BuffName;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FText BuffDescription;

};


UENUM(BlueprintType)
enum class EBuffType : uint8
{
  Leeched UMETA(DisplayName = "Leeched")
};
