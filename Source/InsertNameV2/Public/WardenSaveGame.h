// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PickSaveInfo.h"
#include "WardenSaveGame.generated.h"

class APaperWarden;
class AMaster_Pickup;

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UWardenSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

  UWardenSaveGame();

  void SaveInventoryItem(AMaster_Pickup* ItemToSave, int32 Index);

  void SaveActionbarItem(AMaster_Pickup* ItemToSave, int32 Index);

  UPROPERTY(EditAnywhere, Category = "Save Game")
  TArray<FSavedItemInfo> PlayerInventory;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  TArray<FSavedItemInfo> PlayerActionbar;
	
  UPROPERTY(EditAnywhere, Category = "Save Game")
  AMaster_Pickup* CurrentGun;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  bool bIsGunEquipped;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  FVector GunOffset;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  int32 AmountOfInventorySlots;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  int32 ActionBarSlotsPerRow;

  FSavedItemInfo ItemInfo;

  TArray<AMaster_Pickup*> LoadInventory();

  TArray<AMaster_Pickup*> LoadActionbar();
};
