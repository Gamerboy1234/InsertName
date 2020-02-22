// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerDebuffInfo.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FPlayerDebuffData
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
  FVector EffectScale = FVector(1);

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  bool bUseTicks = true;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UTexture2D* DebuffIcon;
};


UENUM(BlueprintType)
enum class EPlayerDebuffType : uint8
{
  PD_Fire UMETA(DisplayName = "Fire"),

  PD_Stun UMETA(DisplayName = "Stun")
};
