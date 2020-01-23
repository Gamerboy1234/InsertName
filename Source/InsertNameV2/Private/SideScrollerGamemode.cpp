// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScrollerGamemode.h"
#include "GeneralFunctions.h"

int32 ASideScrollerGamemode::GenID()
{
  int32 ID = UGeneralFunctions::RandomNumber(1, 100000);
  if (DoesIDAlreadyExist(ID))
  {
    ID = UGeneralFunctions::RandomNumber(1, 100000);
    AllIDs.Add(ID);
    return ID;
  }
  else
  {
    AllIDs.Add(ID);
    return ID;
  }
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

const TArray<int32> ASideScrollerGamemode::GetAllIDs()
{
  TArray<int32> LocalIDs = AllIDs;

  return LocalIDs;
}

void ASideScrollerGamemode::RemoveID(int32 IDToRemove)
{
  auto Index = AllIDs.Find(IDToRemove);

  if (Index)
  {
    AllIDs.RemoveAt(Index);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Unable to find ID to remove"))
  }
}
