// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScrollerGamemode.h"
#include "GeneralFunctions.h"

int32 ASideScrollerGamemode::GenID()
{
  int32 ID = UGeneralFunctions::RandomNumber(1, 10000);
  if (bDoesIDAlreadyExist(ID))
  {
    ID = UGeneralFunctions::RandomNumber(1, 1000);
    AllIDs.Add(ID);
    return ID;
  }
  else
  {
    AllIDs.Add(ID);
    return ID;
  }
}

bool ASideScrollerGamemode::bDoesIDAlreadyExist(int32 ID)
{
  bool bExist;
  for (int32 IDs : AllIDs)
  {
    if (ID == IDs)
    {
      bExist = true;
      break;
    }
    bExist = false;
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
