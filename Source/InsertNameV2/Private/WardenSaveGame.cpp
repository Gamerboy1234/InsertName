// Fill out your copyright notice in the Description page of Project Settings.


#include "WardenSaveGame.h"
#include "Engine/World.h"
#include "InsertNameV2.h"
#include "Master_Spell.h"
#include "GeneralFunctions.h"
#include "PaperWarden.h"
#include "Master_Pickup.h"

UWardenSaveGame::UWardenSaveGame()
{
  SavedbIsGunEquipped = false;
  SavedGunClass = nullptr;
  bFoundSpellInfo = false;

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

void UWardenSaveGame::SaveSpellCoolDowns(APaperWarden* Player)
{
  TArray<AMaster_Spell*> LocalSpells = Player->GetPlayerSpellsOnActionbar();

  for (AMaster_Spell* Spell : LocalSpells)
  {
    if (Spell)
    {
      SpellInfo.SpellToSave = Spell->GetClass();
      SpellInfo.SavedCurrentTimeLinePostion = Spell->CurrentTimeLinePostion;
      SpellInfo.SavedCurrentScalerValue = Spell->CurrentScalerValue;
      SpellInfo.SavedbWasOnCooldown = Spell->bCurrentlyOnCooldown;
      SpellInfo.SavedbWasPaused = Spell->bCoolDownPaused;
      SpellInfo.SavedCoolDownTime = Spell->CoolDownTime;

      SavedPlayerSpells.Add(SpellInfo);
    }
  }
}

FSavedPlayerSpell UWardenSaveGame::GetSavedSpellInfo(AMaster_Spell* SpellToFind)
{
  FSavedPlayerSpell LocalInfo;
  
  if (SpellToFind)
  {
    for (FSavedPlayerSpell CurrentInfo : SavedPlayerSpells)
    {
      if (SpellToFind->GetClass() == CurrentInfo.SpellToSave)
      {
        LocalInfo = CurrentInfo;
        bFoundSpellInfo = true;
        break;
      }
      else
      {
        bFoundSpellInfo = false;
        LocalInfo.SpellToSave = nullptr;
        continue;
      }
    }
    return LocalInfo;
  }
  else
  {
    UE_LOG(LogSaveGame, Error, TEXT("Failed to FindSavedSpell SpellToFind was not valid"))
    bFoundSpellInfo = false;
    LocalInfo.SpellToSave = nullptr;
    return LocalInfo;
  }
}

