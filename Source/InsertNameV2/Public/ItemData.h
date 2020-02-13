// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemType.h"
#include "SpellInfo.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
  GENERATED_USTRUCT_BODY()
  /* The name of the item */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FText ItemName;
  /* Description of what the item does */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
   FText Description;
  /* Image displayed in the inventory */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  class UTexture2D* Icon;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bCanBeUsed = true;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bCanBeStacked = true;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  int32 Amount = 1;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FText UseText;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  EItemType ItemType;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  float Damage;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FString InteralName;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bIsSpellAugment;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bIsSpell;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info", meta = (EditCondition = "bIsSpell"))
  FSpellData SpellInfo;
};
