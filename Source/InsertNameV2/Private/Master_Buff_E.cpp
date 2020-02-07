// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Buff_E.h"
#include "Master_Enemy.h"
#include "GeneralFunctions.h"

void AMaster_Buff_E::StartBuff_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("Start buff has implementation"))
}

void AMaster_Buff_E::StopBuff_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("Stop buff has implementation"))
}

void AMaster_Buff_E::SetUpBuff(FBuffData BuffData, class AMaster_Enemy* Target)
{
  if (Target)
  {
    ID = UGeneralFunctions::GetIDFromGamemode(this, this);
    CurrentStackCount = 0;
    CurrentInfo = BuffData;
    TargetEnemy = Target;
    StartBuff();
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Was unable to get Buff Data"))
    return;
  }
}

void AMaster_Buff_E::RemoveBuff(AMaster_Buff_E* BuffToRemove)
{
  if (BuffToRemove)
  {
    BuffToRemove->StopBuff();
    if (TargetEnemy->CurrentBuffs.Find(BuffToRemove))
    {
      TargetEnemy->CurrentBuffs.Remove(BuffToRemove);
    }
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Buff Not Valid"))
    return;
  }
}

void AMaster_Buff_E::AddToStack()
{
  CurrentStackCount++;
}

const int32 AMaster_Buff_E::GetID()
{
  return ID;
}

const int32 AMaster_Buff_E::GetCurrentStack()
{
  return CurrentStackCount;
}

const FBuffData AMaster_Buff_E::GetCurrentData()
{
  return CurrentInfo;
}
