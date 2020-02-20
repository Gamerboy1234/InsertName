// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickSaveInfo.generated.h"

class AMaster_Pickup;

USTRUCT(BlueprintType)
struct FSavedItemInfo
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, Category = "Item Save")
  UClass* ItemToSave;

  UPROPERTY(EditDefaultsOnly, Category = "Item Save")
  int32 ItemIndex;

  UPROPERTY(EditDefaultsOnly, Category = "Item Save")
  int32 AmountAtIndex;
};
