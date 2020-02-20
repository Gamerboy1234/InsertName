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
  TArray<FSavedItemInfo> SavedInventory;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  TArray<FSavedItemInfo> SavedActionBar;
	
  UPROPERTY(EditAnywhere, Category = "Save Game")
  UClass* SavedGunClass;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  FVector SavedGunScale;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  bool SavedbIsGunEquipped;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  FVector SavedGunOffset;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  int32 SavedAmountOfInventorySlots;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  int32 SavedActionBarSlotsPerRow;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  float SavedPlayerCurrentHP;

  UPROPERTY(EditAnywhere, Category = "Save Game")
  float SavedPlayerMaxHP;


  FSavedItemInfo ItemInfo;

};
