// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemType.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
  IT_Consumables UMETA(DisplayName = "Consumables"),

  IT_Readable UMETA(DisplayName = "Readable"),

  IT_Augment UMETA(DisplayName = "Spell Augment"),

  IT_Equipment UMETA(DisplayName = "Equipment"),

  IT_Spell UMETA(DisplayName = "Spell"),

  IT_Buff UMETA(DisplayName = "Buff"),

  IT_Debuff UMETA(DisplayName = "Debuff")
};

