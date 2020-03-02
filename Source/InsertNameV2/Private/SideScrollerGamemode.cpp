// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScrollerGamemode.h"
#include "InsertNameV2.h"
#include "Master_Spell.h"
#include "GeneralFunctions.h"

int32 ASideScrollerGamemode::GenID()
{
  int32 ID = UGeneralFunctions::RandomNumber(1, 100000);
  if (DoesIDAlreadyExist(ID))
  {
    ID = UGeneralFunctions::RandomNumber(1, 100000);
    AllIDs.AddUnique(ID);
    return ID;
  }
  else
  {
    AllIDs.AddUnique(ID);
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
  TArray<int32> LocalIDs = AllIDs;

  return LocalIDs;
}

void ASideScrollerGamemode::ResumeAllCoolDowns()
{
  TArray<AActor*> FoundActors;

  UGameplayStatics::GetAllActorsOfClass(this, AMaster_Spell::StaticClass(), FoundActors);

  for (AActor* Actor : FoundActors)
  {
    if (Actor)
    {
      AMaster_Spell* LocalSpell = Cast<AMaster_Spell>(Actor);

      if (LocalSpell)
      {
        if (LocalSpell->bCoolDownPaused)
        {
          LocalSpell->ResumeCoolDown();
        }
      }
    }
  }
}

void ASideScrollerGamemode::RemoveID(int32 IDToRemove)
{
  AllIDs.Remove(IDToRemove);
}
