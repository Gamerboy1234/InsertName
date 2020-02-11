// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FText ItemName;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
   FText Description;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  class UTexture2D* Icon;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bCanBeUsed = true;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bCanBeStacked = true;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FText UseText;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  float Damage;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FString InteralName;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bIsSpellAugment;
};

USTRUCT(BlueprintType)
struct FSpellData
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, Category = "Spell Info")
  bool bHasCastTime;

  UPROPERTY(EditDefaultsOnly, Category = "Spell Info", meta = (EditCondition = "bHasCastTime"))
  float CastTime;

  UPROPERTY(EditDefaultsOnly, Category = "Spell Info")
  float Cooldown;
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
  IT_Consumables UMETA(DisplayName = "Consumables"),

  IT_Readable UMETA(DisplayName = "Readable"),

  IT_SpellMod UMETA(DisplayName = "Spell Mod"),

  IT_QuestItem UMETA(DisplayName = "Quest Item"),

  IT_Equipment UMETA(DisplayName = "Equipment"),

  IT_Spell UMETA(DisplayName = "Spell"),

  IT_Buff UMETA(DisplayName = "Buff"),

  IT_Debuff UMETA(DisplayName = "Debuff")
};
