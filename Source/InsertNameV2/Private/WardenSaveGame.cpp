// Fill out your copyright notice in the Description page of Project Settings.


#include "WardenSaveGame.h"
#include "Engine/World.h"
#include "PaperWarden.h"
#include "Master_Pickup.h"

UWardenSaveGame::UWardenSaveGame()
{
  SavedbIsGunEquipped = false;
  SavedGunClass = nullptr;
}

void UWardenSaveGame::SaveInventoryItem(AMaster_Pickup* ItemToSave, int32 Index)
{
  if (ItemToSave)
  {
    ItemInfo.ItemToSave = ItemToSave->GetClass();
    ItemInfo.ItemIndex = Index;
    SavedInventory.Add(ItemInfo);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to save InventoryItem ItemToSave was not valid"))
  }
}

void UWardenSaveGame::SaveActionbarItem(AMaster_Pickup* ItemToSave, int32 Index)
{
  if (ItemToSave)
  {
    ItemInfo.ItemToSave = ItemToSave->GetClass();
    ItemInfo.ItemIndex = Index;
    SavedActionBar.Add(ItemInfo);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to save ActionbarItem ItemToSave was not valid"))
  }
}
