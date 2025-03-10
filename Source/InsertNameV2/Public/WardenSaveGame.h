// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PickSaveInfo.h"
#include "SavedSpellInfo.h"
#include "WardenSaveGame.generated.h"

class APaperWarden;
class AMaster_Pickup;
class AMaster_Spell;

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

  void SaveSpellCoolDowns(APaperWarden* Player);

  FSavedPlayerSpell GetSavedSpellInfo(AMaster_Spell* SpellToFind);

  UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Save Game")
  TArray<FSavedItemInfo> SavedInventory;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  TArray<FSavedItemInfo> SavedActionBar;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  TArray<FSavedPlayerSpell> SavedPlayerSpells;
	
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  UClass* SavedGunClass;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  FVector SavedGunScale;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  bool SavedbIsGunEquipped;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  FVector SavedGunOffset;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  int32 SavedAmountOfInventorySlots;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  int32 SavedActionBarSlotsPerRow;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  float SavedPlayerCurrentHP;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  float SavedPlayerMaxHP;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  FName SavedCurrentCheckpointLevel;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  bool SavedbWasLevelLoaded;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  bool SavedbLoadedCheckpoint;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Save Game")
  FVector SavedCheckpointLocation;

  FSavedItemInfo ItemInfo;

  FSavedPlayerSpell SpellInfo;

  bool bFoundSpellInfo;
};
