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
  /* Whether or not the given item can be used */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bCanBeUsed = true;
  /* If the item can be stack on other items of the same class */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bCanBeStacked = true;
  /* The amount of the item to be added to the player's inventory */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  int32 Amount = 1;
  /* What the item action button will say on the use button */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FText UseText;
  /* The actual type of the given item */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  EItemType ItemType;
  /* If the item is a weapon this is how much damage it will deal */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  float Damage;
  /* When the the item is sorted in the inventory this name is used to determine where to place it the InventoryArray should have no spaces and in all lower case */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FString InteralName;
  /* Whether or not the given item is used to augment player spells */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bIsSpellAugment;
  /* Whether or not the given item is a spell if true can be added to player inventory and only be used on the actionbar */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  bool bIsSpell;
  /* If bIsSpell is true this struct is used to edit spell settings */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info", meta = (EditCondition = "bIsSpell"))
  FSpellData SpellInfo;
};
