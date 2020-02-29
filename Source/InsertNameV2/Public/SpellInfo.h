// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellInfo.generated.h"


USTRUCT(BlueprintType)
struct FSpellData
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Spell Info")
  bool bHasCastTime;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Info", meta = (EditCondition = "bHasCastTime"))
  float CastTime;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Info")
  float Cooldown;
};
