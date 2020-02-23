// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScrollerGamemode.h"
#include "InsertNameV2.h"
#include "Master_Pickup.h"
#include "GeneralFunctions.h"

int32 ASideScrollerGamemode::GenID(AActor* ActorToAdd)
{
  if (ActorToAdd)
  {
    int32 ID = UGeneralFunctions::RandomNumber(1, 100000);
    if (DoesIDAlreadyExist(ID))
    {
      ID = UGeneralFunctions::RandomNumber(1, 100000);
      AllActors.AddUnique(ActorToAdd);
      AllIDs.AddUnique(ID);
      return ID;
    }
    else
    {
      AllActors.AddUnique(ActorToAdd);
      AllIDs.AddUnique(ID);
      return ID;
    }
  }
  else
  {
    UE_LOG(LogSideScrollerGameMode, Error, TEXT("Failed to GenID ActorToAdd was not vaild"))
    return 0;
  }
}

void ASideScrollerGamemode::AddActorToGamemode(AActor* ActorToAdd, int32 IDToAdd)
{
  if (ActorToAdd)
  {
    if (!DoesIDAlreadyExist(IDToAdd))
    {
      AllActors.AddUnique(ActorToAdd);
      AllIDs.AddUnique(IDToAdd);
    }
  }
  else
  {
    UE_LOG(LogSideScrollerGameMode, Error, TEXT("Failed to add actor to gamemode ActorToAdd was not vaild"))
  }
}

int32 ASideScrollerGamemode::FindIDInArray(int32 ID)
{
  int32 FoundIndex = 0;

  for (int32 Index = 0; Index < AllIDs.Num(); Index++)
  {
    int32 CurrentIndex = AllIDs[Index];

    if (CurrentIndex)
    {
      if (CurrentIndex == ID)
      {
        FoundIndex = Index;
        break;
      }
      else
      {
        FoundIndex = 0;
        continue;
      }
    }
  }
  return FoundIndex;
}

int32 ASideScrollerGamemode::FindPickupByID(int32 ID)
{
  int32 FoundIndex = 0;

  for (int32 Index = 0; Index < AllActors.Num(); Index++)
  {
    AActor* CurrentIndex = AllActors[Index];

    if (CurrentIndex)
    {
      AMaster_Pickup* CurrentPickup = Cast<AMaster_Pickup>(CurrentIndex);

      if (CurrentPickup)
      {
        FoundIndex = Index;
        break;
      }
      else
      {
        FoundIndex = 0;
        continue;
      }
    }
  }
  return FoundIndex;
}

bool ASideScrollerGamemode::DoesIDAlreadyExist(int32 ID)
{
  bool bExist = false;

  for (int32 IDs : AllIDs)
  {
    if (ID == IDs)
    {
      bExist = true;
      break;
    }
    else
    {
      bExist = false;
      continue;
    }
  }
  return bExist;
}

void ASideScrollerGamemode::RemoveID(int32 IDToRemove)
{
  int32 IndexToRemove = FindIDInArray(IDToRemove);

  if (AllIDs.IsValidIndex(IndexToRemove))
  {
    AllIDs.Remove(IndexToRemove);
  }
  else
  {
    UE_LOG(LogSideScrollerGameMode, Error, TEXT("Failed to remove ID from gamemode unable to find ID : %i"), IDToRemove)
  }
}

void ASideScrollerGamemode::RemovePickupFromGamemode(AMaster_Pickup* PickupToRemove)
{
  if (PickupToRemove)
  {
    int32 IndexToRemove = FindPickupByID(PickupToRemove->GetID());

    if (AllActors.IsValidIndex(IndexToRemove))
    {
      AllActors.RemoveAt(IndexToRemove);
    }
    else
    {
      UE_LOG(LogSideScrollerGameMode, Error, TEXT("Failed to remove Pickup from gamemode unable to find Pickup %s"), *PickupToRemove->GetName())
    }
  }
  else
  {
    UE_LOG(LogSideScrollerGameMode, Error, TEXT("Failed to remove Pickup from gamemode PickupToRemove was not vaild"))
  }
}

void ASideScrollerGamemode::RemoveActorFromGamemode(AActor* ActorToRemove)
{
  if (ActorToRemove)
  {
    if (AllActors.Find(ActorToRemove))
    {
      AllActors.Remove(ActorToRemove);
    }
    else
    {
      UE_LOG(LogSideScrollerGameMode, Error, TEXT("Failed to remove Actor from gamemode unable to find Actor %s"), *ActorToRemove->GetName())
    }
  }
  else
  {
    UE_LOG(LogSideScrollerGameMode, Error, TEXT("Failed to remove actor from gamemode ActorToRemove was not vaild"))
  }
}

void ASideScrollerGamemode::DisplayItemObtainedMessage_Implementation(AMaster_Pickup* Pickup, int32 Amount)
{
  UE_LOG(LogSideScrollerGameMode, Warning, TEXT("DisplayItemObtainedMessage has no implementation"))
}

void ASideScrollerGamemode::DisplayTextMessage_Implementation(const FText& Message)
{
  UE_LOG(LogSideScrollerGameMode, Warning, TEXT("DisplayTextMessage has no implementation"))
}

const TArray<int32> ASideScrollerGamemode::GetAllIDs()
{
  return AllIDs;
}

const TArray<AActor*> ASideScrollerGamemode::GetAllActors()
{
  return AllActors;
}
