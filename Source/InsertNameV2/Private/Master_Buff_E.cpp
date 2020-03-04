// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Buff_E.h"
#include "Master_Enemy.h"
#include "InsertNameV2.h"
#include "GeneralFunctions.h"


void AMaster_Buff_E::UnPackSettings()
{
  BuffAmount = BuffSettings.BuffAmount;
  BuffDuration = BuffSettings.BuffDuration;
  EffectScale = BuffSettings.EffectScale;
  BuffEffect = BuffSettings.BuffEffect;
}

AMaster_Buff_E::AMaster_Buff_E()
{
  PrimaryActorTick.bCanEverTick = false;

  bStack = true;
  bRefresh = false;

  CurrentStackCount = 1;
}

void AMaster_Buff_E::StartBuff_Implementation()
{
  UE_LOG(LogEnemyBuffs, Warning, TEXT("Start buff has implementation"))
}

void AMaster_Buff_E::StopBuff_Implementation()
{
  UE_LOG(LogEnemyBuffs, Warning, TEXT("Stop buff has implementation"))
}

void AMaster_Buff_E::SetUpBuff_Implementation(AMaster_Enemy* Target, AMaster_Buff_E* BuffToApply)
{
  UnPackSettings();

  TargetEnemy = Target;

  if (Target)
  {
    if (!IsBuffAlreadyApplied(BuffToApply, TargetEnemy))
    {
      ID = UGeneralFunctions::GetIDFromGamemode(this, this);
      SpawnEffect(TargetEnemy);
      StartBuff();
    }
    else if (bStack)
    {
      AddToBuffStack(BuffToApply, TargetEnemy);
    }
    else if (bRefresh)
    {
      RefreshBuff(BuffToApply, TargetEnemy);
    }
  }
  else
  {
    UE_LOG(LogEnemyBuffs, Error, TEXT("Buff target was not valid"))
  }
}

void AMaster_Buff_E::AddToBuffStack(AMaster_Buff_E* BuffToAddTo, AMaster_Enemy* CurrentActor)
{
  if (CurrentActor)
  {
    if (BuffToAddTo)
    {
      AMaster_Buff_E* BuffToFind = CurrentActor->FindBuffByType(BuffToAddTo->BuffType);

      if (BuffToFind)
      {
        BuffToFind->AddToStack(BuffToFind);
        BuffToAddTo->Destroy();
      }
      else
      {
        UE_LOG(LogEnemyBuffs, Error, TEXT("Was unable to add buff to stack couldn't find buff in stack"))
      }
    }
    else
    {
      UE_LOG(LogEnemyBuffs, Error, TEXT("Unable to add debuff to stack BuffToAddTo was not valid"))
    }
  }
  else
  {
    UE_LOG(LogEnemyBuffs, Error, TEXT("Unable to add buff to stack CurrentActor was not valid"))
  }
}

void AMaster_Buff_E::RefreshBuff(AMaster_Buff_E* BuffToRefresh, AMaster_Enemy* CurrentActor)
{
  if (CurrentActor)
  {
    if (BuffToRefresh)
    {
      AMaster_Buff_E* BuffToFind = CurrentActor->FindBuffByType(BuffToRefresh->BuffType);

      if (BuffToFind)
      {
        BuffToFind->RemoveBuff(BuffToFind, CurrentActor);
        CurrentActor->ApplyBuff(BuffToRefresh->GetClass());
        BuffToRefresh->Destroy();
      }
      else
      {
        UE_LOG(LogEnemyBuffs, Error, TEXT("Was unable to refresh buff couldn't find buff in stack"))
      }
    }
    else
    {
      UE_LOG(LogEnemyBuffs, Error, TEXT("Unable to refresh buff BuffToRefresh was not valid"))
    }
  }
  else
  {
    UE_LOG(LogEnemyBuffs, Error, TEXT("Unable to refresh buff CurrentActor was not valid"))
  }
}

void AMaster_Buff_E::SpawnEffect(AMaster_Enemy* CurrentActor)
{
  if (BuffEffect)
  {
    // Spawn buff effect to current enemy actor
    auto SpawnTransform = FTransform(FRotator(0), FVector(0), EffectScale);
    CurrentEffect = GetWorld()->SpawnActor<AMasterDamageEffect>(BuffEffect, SpawnTransform);
    if (CurrentEffect)
    {
      CurrentEffect->EffectScale = EffectScale;
      CurrentEffect->SetEffect(CurrentActor);
    }
    else
    {
      UE_LOG(LogEnemyBuffs, Error, TEXT("Unable to spawn buff Effect"))
    }
  }
  else
  {
    UE_LOG(LogEnemyBuffs, Warning, TEXT("No damage effect was selected"))
  }
}

const bool AMaster_Buff_E::IsBuffAlreadyApplied(AMaster_Buff_E* Buff, AMaster_Enemy* CurrentActor)
{
  bool LocalBool = false;

  if (CurrentActor)
  {
    if (Buff)
    {
      TArray<AMaster_Buff_E*> CurrentEnemyBuffs = CurrentActor->CurrentBuffs;

      for (AMaster_Buff_E* CurrentBuff : CurrentEnemyBuffs)
      {
        if (CurrentBuff->BuffType == Buff->BuffType)
        {
          LocalBool = true;
          break;
        }
        else
        {
          LocalBool = false;
          continue;
        }
      }

      return LocalBool;
     }
    else
    {
      LocalBool = false;
      UE_LOG(LogEnemyBuffs, Error, TEXT("Buff in IsBuffAlreadyApplied is not valid"))
      return LocalBool;
    }
  }
  else
  {
    LocalBool = false;
    UE_LOG(LogEnemyBuffs, Error, TEXT("Current Actor in IsBuffAlreadyApplied is not valid"))
    return LocalBool;
  }
}

void AMaster_Buff_E::RemoveBuff(AMaster_Buff_E* BuffToRemove, AMaster_Enemy* CurrentActor)
{
  if (CurrentActor)
  {
    if (CurrentEffect)
    {
      CurrentEffect->RemoveEffect();
      CurrentActor->CurrentBuffs.Remove(BuffToRemove);
      UGeneralFunctions::RemoveIDFromGamemode(this, BuffToRemove->ID, BuffToRemove);
      BuffToRemove->Destroy();
    }
    else
    {
      CurrentActor->CurrentBuffs.Remove(BuffToRemove);
      UGeneralFunctions::RemoveIDFromGamemode(this, BuffToRemove->ID, BuffToRemove);
      BuffToRemove->Destroy();
    }
  }
}

void AMaster_Buff_E::AddToStack(AMaster_Buff_E* BuffToAddTo)
{
  BuffToAddTo->CurrentStackCount++;
}

const int32 AMaster_Buff_E::GetID()
{
  return ID;
}

const int32 AMaster_Buff_E::GetCurrentStack()
{
  return CurrentStackCount;
}
