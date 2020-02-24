// Fill out your copyright notice in the Description page of Project Settings.


#include "WardenSaveGame.h"
#include "Engine/World.h"
#include "InsertNameV2.h"
#include "GeneralFunctions.h"
#include "PaperWarden.h"
#include "Master_Pickup.h"

UWardenSaveGame::UWardenSaveGame()
{
  SavedbIsGunEquipped = false;
  SavedGunClass = nullptr;

  SavedActionBarSlotsPerRow = 0;
  SavedAmountOfInventorySlots = 0;
  SavedPlayerCurrentHP = 0;
  SavedPlayerMaxHP = 0;
}

void UWardenSaveGame::SaveInventoryItem(AMaster_Pickup* ItemToSave, int32 Index)
{
  if (ItemToSave)
  {
    ItemInfo.ItemToSave = ItemToSave->GetClass();
    ItemInfo.ItemIndex = Index;
    ItemInfo.AmountAtIndex = ItemToSave->AmountAtIndex;
    ItemInfo.PickupLocation = ItemToSave->GetActorLocation();
    SavedInventory.Add(ItemInfo);
  }
  else
  {
    UE_LOG(LogSaveGame, Error, TEXT("Failed to save InventoryItem ItemToSave was not valid"))
  }
}

void UWardenSaveGame::SaveActionbarItem(AMaster_Pickup* ItemToSave, int32 Index)
{
  if (ItemToSave)
  {
    ItemInfo.ItemToSave = ItemToSave->GetClass();
    ItemInfo.ItemIndex = Index;
    ItemInfo.AmountAtIndex = ItemToSave->AmountAtIndex;
    SavedActionBar.Add(ItemInfo);
  }
  else
  {
    UE_LOG(LogSaveGame, Error, TEXT("Failed to save ActionbarItem ItemToSave was not valid"))
  }
}
