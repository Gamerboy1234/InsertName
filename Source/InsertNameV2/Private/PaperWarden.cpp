// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperWarden.h"
#include "Master_Pickup.h"
#include "PaperSpriteComponent.h"
#include "Engine.h"
#include "GeneralFunctions.h"
#include "Components/InputComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"

APaperWarden::APaperWarden()
{
  PrimaryActorTick.bCanEverTick = true;

  BarkInnerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Bark Inner Collision"));
  BarkInnerCollision->SetupAttachment(RootComponent);
  BarkOuterCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Bark Outer Collision"));
  BarkOuterCollision->SetupAttachment(RootComponent);

  AmountofInventorySlots = 8;
  ActionBarSlotsPerRow = 10;
}

void APaperWarden::BeginPlay()
{
  Super::BeginPlay();

  BarkInnerCollision->OnComponentBeginOverlap.AddDynamic(this, &APaperWarden::OnOverlapBegin);
  BarkOuterCollision->OnComponentBeginOverlap.AddDynamic(this, &APaperWarden::BeginOverlap);

  InventoryItems.Empty();
  InventoryItems.Init(0, AmountofInventorySlots);

  ActionBarItems.Empty();
  ActionBarItems.Init(0, ActionBarSlotsPerRow);
}

int32 APaperWarden::AddToKillCount(int32 AmountToadd)
{
  return KillCount += AmountToadd;
}

const int32 APaperWarden::GetCurrentKillCount()
{
  return KillCount;
}

void APaperWarden::LoadKillCount(int32 KillCountToLoad)
{
  KillCount = KillCountToLoad;
}

void APaperWarden::PickedUpItem_Implementation(class UTexture2D* PickUpTexture)
{
  UE_LOG(LogTemp, Warning, TEXT("Player Pickup event has no Implementation"))
}

void APaperWarden::HealPlayer_Implementation(float HealAmount)
{
  UE_LOG(LogTemp, Warning, TEXT("Player Heal event has no Implementation"))
}

void APaperWarden::KillPlayer_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("Kill Player event has no Implementation"))
}

void APaperWarden::UpgradeHP_Implementation(float UpgradeAmount, float NewMaxHP)
{
  UE_LOG(LogTemp, Warning, TEXT("Upgrade HP event has no Implementation"))
}

void APaperWarden::Damage_Implementation(float DamageAmount, bool bShowCombatText, AActor* DamageInstigator)
{
  UE_LOG(LogTemp, Warning, TEXT("Damage event has no Implementation"))
}

void APaperWarden::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    OnBarkInnerOverlap(OtherActor);
  }
}

void APaperWarden::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    OnBarkOuterOverlap(OtherActor);
  }
}

bool APaperWarden::AddItem(AMaster_Pickup* ItemToAdd, int32 Amount)
{
  if (!IsInventoryFull())
  {
    if (ItemToAdd)
    {
      if (!ItemToAdd->ItemInfo.bIsSpell)
      {
        if (ItemToAdd->ItemInfo.bCanBeStacked)
        {
          AMaster_Pickup* StackToAddTo = SearchForFreeStack(ItemToAdd);

          if (StackToAddTo)
          {
            StackToAddTo->AddToStack();
            ItemToAdd->bAddedToStack = true;
            UpdateInventory();
            return true;
          }
          else
          {
            if (Amount > ItemToAdd->MaxItemAmount)
            {
              int32 Index = FindEmptySlotInInventory();

              if (bFoundSlot)
              {
                int32 Overflow = Amount - ItemToAdd->MaxItemAmount;
                InventoryItems[Index] = ItemToAdd;
                ItemToAdd->bAddedToStack = false;
                UpdateInventory();
                AddItem(ItemToAdd, Overflow);
                return true;
              }
              else
              {
                return false;
              }
            }
            else
            {
              int32 Index = FindEmptySlotInInventory();

              if (bFoundSlot)
              {
                InventoryItems[Index] = ItemToAdd;
                ItemToAdd->bAddedToStack = false;
                UpdateInventory();
                return true;
              }
              else
              {
                return false;
              }
            }
          }
        }
        else
        {
          int32 Index = FindEmptySlotInInventory();

          if (bFoundSlot)
          {
            InventoryItems[Index] = ItemToAdd;
            ItemToAdd->bAddedToStack = false;
            UpdateInventory();

            if (Amount > 1)
            {
              Amount--;
              AddItem(ItemToAdd, Amount);
              return true;
            }
            else
            {
              return true;
            }
          }
          else
          {
            return false;
          }
        }
      }
      else
      {
        return false;
      }
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("failed to add item. Item was not valid"))
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool APaperWarden::RemoveItemFromInventory(AMaster_Pickup* ItemToRemove, int32 Amount)
{
  if (ItemToRemove)
  {
    AMaster_Pickup* LocalItem = FindItemByName(ItemToRemove, InventoryItems);

    if (LocalItem)
    {
      LocalItem->AmountAtIndex -= Amount;

      if (LocalItem->AmountAtIndex <= 0)
      {
        int32 Index = InventoryItems.Find(LocalItem);
        if (InventoryItems.IsValidIndex(Index))
        {
          InventoryItems[Index] = nullptr;
          ItemToRemove->DestroyPickup();
          UpdateInventory();
          return true;
        }
        else
        {
          UE_LOG(LogTemp, Error, TEXT("failed to find item in Inventory not a vaild index"))
          return false;
        }
      }
      else
      {
        UpdateInventory();
        return true;
      }
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("failed to find item in Inventory"))
      return false;
    }   
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Item to remove was not valid"))
    return false;
  }
}

bool APaperWarden::SplitItemStack(AMaster_Pickup* ItemToSplit, int32 Amount)
{
  if (ItemToSplit)
  {
    if (ItemToSplit->ItemInfo.bCanBeStacked && ItemToSplit->AmountAtIndex > Amount)
    {
      int32 EmptySlot = FindEmptySlotInInventory();
      AMaster_Pickup* LocalItem = FindItemByName(ItemToSplit, InventoryItems);

      if (bFoundSlot)
      {
        FTransform SpawnLocation = FTransform(FRotator(1), FVector(1), FVector(1));

        UClass* ItemClass = LocalItem->GetClass();

        AMaster_Pickup* SplitActor = GetWorld()->SpawnActor<AMaster_Pickup>(ItemClass, SpawnLocation);

        if (SplitActor)
        {
          int32 NewAmount = LocalItem->AmountAtIndex - Amount;
          LocalItem->AmountAtIndex = NewAmount;

          SplitActor->AmountAtIndex = Amount;
          SplitActor->ShowPickup(false);

          InventoryItems[EmptySlot] = SplitActor;
          UpdateInventory();
          return true;
        }
        else
        {
          UE_LOG(LogTemp, Error, TEXT("Couldn't split item SplitActor was not vaild"))
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Couldn't split item ItemToSplit was not vaild"))
    return false;
  }
}

bool APaperWarden::DropItemsOnActionBar(AMaster_Pickup* Pickup, int32 Index)
{
  if (!IsActionBarFull())
  {
    ActionBarItems[Index] = Pickup;
    InventoryItems[Index] = nullptr;

    UpdateInventory();
    UpdateActionBar();

    return true;
  }
  else
  {
    return false;
  }
}

void APaperWarden::UpdateInventory()
{
  OnUpdateInventory.Broadcast(InventoryItems);
}

void APaperWarden::UpdateActionBar()
{
  OnUpdateActionBar.Broadcast(ActionBarItems);
}

bool APaperWarden::IsInventoryFull()
{
  int32 LocalCounter = 0;

  for (AMaster_Pickup* Pickup : InventoryItems)
  {
    if (Pickup)
    {
      LocalCounter++;
    }
  }

  if (LocalCounter >= AmountofInventorySlots)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool APaperWarden::IsActionBarFull()
{
  return false;
}

AMaster_Pickup* APaperWarden::FindItemByName(AMaster_Pickup* ItemToFind, const TArray<AMaster_Pickup*> ArrayToUse)
{
  AMaster_Pickup* LocalItem = nullptr;

  for (AMaster_Pickup* Item : ArrayToUse)
  {
    if (Item)
    {
      FString Name1 = Item->ConvertItemNameToString();
      FString Name2 = ItemToFind->ConvertItemNameToString();

      if (Name1 == Name2)
      {
        LocalItem = Item;
        break;
      }
      else
      {
        LocalItem = nullptr;
        continue;
      }
    }
  }
  return LocalItem;
}

AMaster_Pickup* APaperWarden::SearchForFreeStack(AMaster_Pickup* ItemClass)
{
  if (ItemClass)
  {
    AMaster_Pickup* LocalPickUp = nullptr;

    for (AMaster_Pickup* Pickup : InventoryItems)
    {
      if (Pickup)
      {
        auto CurrentPickup = FindItemByName(Pickup, InventoryItems);

        if (CurrentPickup->GetClass() == ItemClass->GetClass())
        {
          if (CurrentPickup->AmountAtIndex < CurrentPickup->MaxItemAmount)
          {
            LocalPickUp = CurrentPickup;
            break;
          }
          else
          {
            LocalPickUp = nullptr;
            continue;
          }
        }
        else
        {
          LocalPickUp = nullptr;
          continue;
        }
      }
      else
      {
        LocalPickUp = nullptr;
        continue;
      }
    }
    return LocalPickUp;
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("SearchForFreeStack failed ItemClass was not vailded"))
    return false;
  }
}

int32 APaperWarden::FindEmptySlotInInventory()
{
  int32 LocalIndex = 0;

  for (int32 Index = 0; Index < InventoryItems.Num(); Index++)
  {
    AMaster_Pickup* CurrentIndex = Cast<AMaster_Pickup>(InventoryItems[Index]);

    if (!CurrentIndex)
    {
      LocalIndex = Index;
      bFoundSlot = true;
      break;
    }
    else
    {
      LocalIndex = 0;
      bFoundSlot = false;
      continue;
    }
  }

  return LocalIndex;
}

int32 APaperWarden::FindEmptySlotOnActionBar()
{
  int32 LocalIndex = 0;

  for (int32 Index = 0; Index < ActionBarItems.Num(); Index++)
  {
    AMaster_Pickup* CurrentIndex = Cast<AMaster_Pickup>(ActionBarItems[Index]);

    if (!CurrentIndex)
    {
      LocalIndex = Index;
      bFoundSlot = true;
      break;
    }
    else
    {
      LocalIndex = 0;
      bFoundSlot = false;
      continue;
    }
  }

  return LocalIndex;
}

bool APaperWarden::IsItemAtIndex(int32 Index)
{
  if (ActionBarItems.IsValidIndex(Index))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void APaperWarden::SwapItemsInInventory(AMaster_Pickup* ItemOne, AMaster_Pickup* ItemTwo)
{
  if (ItemOne)
  {
    if (ItemTwo)
    {
      int32 Index1 = InventoryItems.Find(ItemOne);
      
      if (InventoryItems.IsValidIndex(Index1))
      {
        int32 Index2 = InventoryItems.Find(ItemTwo);

        if (InventoryItems.IsValidIndex(Index2))
        {

          if (InventoryItems[Index1]->GetClass() == InventoryItems[Index2]->GetClass() && InventoryItems[Index2]->AmountAtIndex < InventoryItems[Index1]->MaxItemAmount)
          {
            InventoryItems[Index1]->AmountAtIndex += InventoryItems[Index2]->AmountAtIndex;
            InventoryItems[Index2]->DestroyPickup();
            InventoryItems[Index2] = nullptr;
            UpdateInventory();
          }
          else
          {
            InventoryItems.Swap(Index1, Index2);
            UpdateInventory();
          }
        }
        else
        {
          UE_LOG(LogTemp, Error, TEXT("Couldn't swap items ItemTwo was not found in Inventory"))
        }
      }
      else
      {
        UE_LOG(LogTemp, Error, TEXT("Couldn't swap items ItemOne was not found in Inventory"))
      }
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Couldn't swap items ItemTwo was not vaild"))
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Couldn't swap items ItemOne was not vaild"))
  }
}

bool APaperWarden::UpdateItemIndexInInventory(AMaster_Pickup* ItemToMove, int32 NewIndex)
{
  if (ItemToMove)
  {
    int32 OldIndex = InventoryItems.Find(ItemToMove);

    if (InventoryItems.IsValidIndex(OldIndex))
    {
      InventoryItems[NewIndex] = ItemToMove;
      InventoryItems[OldIndex] = nullptr;
      UpdateInventory();
      return true;
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Failed to find item ItemIndex was not found"))
      return false;
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to find item IndexToMove was not vaild"))
    return false;
  }
}


AMaster_Pickup* APaperWarden::FindItemByIndex(int32 Index, const TArray<AMaster_Pickup*> ArrayToUse)
{
  AMaster_Pickup* LocalItem = nullptr;

  if (ArrayToUse.IsValidIndex(Index))
  {
    for (int32 LocalIndex = 0; LocalIndex < ArrayToUse.Num(); LocalIndex++)
    {
      AMaster_Pickup* CurrentItem = ArrayToUse[LocalIndex];

      if (CurrentItem)
      {
        AMaster_Pickup* ItemToFind = ArrayToUse[Index];

        if (CurrentItem->GetID() == ItemToFind->GetID())
        {
          LocalItem = CurrentItem;
          break;
        }
        else
        {
          LocalItem = nullptr;
          continue;
        }
      }
      else
      {
        LocalItem = nullptr;
        continue;
      }
    }

    return LocalItem;
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to find item by Index. Index was not Valid."))
    return LocalItem;
  }
}

const TArray<AMaster_Pickup*> APaperWarden::GetPlayerInventory()
{
  return InventoryItems;
}

const TArray<AMaster_Pickup*> APaperWarden::GetActionBarItems()
{
  return ActionBarItems;
}
