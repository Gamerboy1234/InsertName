// Fill out your copyright notice in the Description page of Project Settings.


#include "WardenSaveGame.h"
#include "Engine/World.h"
#include "Master_Pickup.h"

UWardenSaveGame::UWardenSaveGame()
{
  bIsGunEquipped = false;
  CurrentGun = nullptr;
}

void UWardenSaveGame::SaveInventoryItem(AMaster_Pickup* ItemToSave, int32 Index)
{
  if (ItemToSave)
  {
    ItemInfo.ItemToSave = ItemToSave;
    ItemInfo.ItemIndex = Index;
    PlayerInventory.Add(ItemInfo);
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
    ItemInfo.ItemToSave = ItemToSave;
    ItemInfo.ItemIndex = Index;
    PlayerActionbar.Add(ItemInfo);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to save ActionbarItem ItemToSave was not valid"))
  }
}

TArray<AMaster_Pickup*> UWardenSaveGame::LoadInventory()
{
  TArray<AMaster_Pickup*> LocalInventory;

  LocalInventory.Empty();

  LocalInventory.Init(0, AmountOfInventorySlots + 1);

  for (int32 Index = 0; Index < PlayerInventory.Num(); Index++)
  {
    FSavedItemInfo CurrentIndex = PlayerInventory[Index];

    if (CurrentIndex.ItemToSave)
    {
      LocalInventory[CurrentIndex.ItemIndex] = CurrentIndex.ItemToSave;
    }
  }
  return LocalInventory;
}

TArray<AMaster_Pickup*> UWardenSaveGame::LoadActionbar()
{
  TArray<AMaster_Pickup*> LocalActionbar;

  LocalActionbar.Empty();

  LocalActionbar.Init(0, ActionBarSlotsPerRow);

  for (int32 Index = 0; Index < PlayerActionbar.Num(); Index++)
  {
    FSavedItemInfo CurrentIndex = PlayerActionbar[Index];

    if (CurrentIndex.ItemToSave)
    {
      LocalActionbar[CurrentIndex.ItemIndex] = CurrentIndex.ItemToSave;
    }
  }
  return LocalActionbar;
}
