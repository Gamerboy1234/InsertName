// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Debuff_E.h"
#include "SideScrollerGamemode.h"
#include "GeneralFunctions.h"
#include "Master_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MasterDamageEffect.h"
#include "TimerManager.h"
#include "Engine/World.h"


AMaster_Debuff_E::AMaster_Debuff_E()
{
  PrimaryActorTick.bCanEverTick = false;

  bTower = true;
  bRefresh = false;

  CurrentStackCount = 1;
}


void AMaster_Debuff_E::UnpackSettings()
{
  // Get Debuff Info from Struct
  Occurrence = DebuffSettings.Occurrence;
  Ticks = DebuffSettings.Ticks;
  Damage = DebuffSettings.Damage;
  DamageEffect = DebuffSettings.DamageEffect;
  EffectScale = DebuffSettings.EffectScale;
  bUseTicks = DebuffSettings.bUseTicks;
}

void AMaster_Debuff_E::StartDamageTimer_Implementation(AMaster_Debuff_E* DebuffToApply, AMaster_Enemy* CurrentActor)
{
  UnpackSettings();

  if (!IsDebuffAlreadyApplied(DebuffToApply, CurrentActor))
  {
    // Assign an ID to debuff from gamemode
    ID = UGeneralFunctions::GetIDFromGamemode(this, this);

    TargetEnemy = CurrentActor;

    CurrentActor->CurrentDebuffs.AddUnique(DebuffToApply);

    SpawnEffect(CurrentActor);
   
    // Create Debuff timer
    GetWorldTimerManager().SetTimer(DebuffTimer, this, &AMaster_Debuff_E::DecrementTick, Occurrence, true);
  }
  else if (bTower)
  {
    AddDebuffToStack(DebuffToApply, CurrentActor);
  }
  else if (bRefresh)
  {
    RefreshDebuff(DebuffToApply, CurrentActor);
  }
}

void AMaster_Debuff_E::DecrementTick()
{
  if (bUseTicks) // Check to see if debuff is using ticks if not debuff will fire off once then remove it's self
  {
    Ticks--;
    if (CanContinueDebuff(TargetEnemy)) // See if enemy is still alive or tick count is above 0
    {
      StartDebuff();
    }
    else
    {
      OnDebuffStop();
      RemoveDebuff(this, TargetEnemy);
    }
  }
  else
  {
    StartDebuff();
    OnDebuffStop();
    RemoveDebuff(this, TargetEnemy);
  }
}

void AMaster_Debuff_E::RemoveDebuff(AMaster_Debuff_E* DebuffToRemove, AMaster_Enemy* CurrentActor)
{
  if (CurrentActor)
  {
    if (CurrentEffect)
    {
      CurrentEffect->RemoveEffect();
      CurrentActor->CurrentDebuffs.Remove(DebuffToRemove);
      GetWorldTimerManager().ClearTimer(DebuffTimer);
      UGeneralFunctions::RemoveIDFromGamemode(this, DebuffToRemove->ID, DebuffToRemove);
      DebuffToRemove->Destroy();
    }
    else
    {
      CurrentActor->CurrentDebuffs.Remove(DebuffToRemove);
      GetWorldTimerManager().ClearTimer(DebuffTimer);
      UGeneralFunctions::RemoveIDFromGamemode(this, DebuffToRemove->ID, DebuffToRemove);
      DebuffToRemove->Destroy();
    }
  }
}

void AMaster_Debuff_E::SpawnEffect(AMaster_Enemy* CurrentActor)
{
  if (DamageEffect)
  {
    // Spawn and attach damage effect to current enemy actor
    auto SpawnTransform = FTransform(FRotator(0), FVector(0), EffectScale);
    CurrentEffect = GetWorld()->SpawnActor<AMasterDamageEffect>(DamageEffect, SpawnTransform);
    if (CurrentEffect)
    {
      CurrentEffect->SetEffect(CurrentActor);
      CurrentEffect->AttachToComponent(CurrentActor->GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Unable to spawn debuff Effect"))
    }
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("No debuff effect was selected"))
  }
}

const bool AMaster_Debuff_E::IsDebuffAlreadyApplied(AMaster_Debuff_E* Debuff, AMaster_Enemy* CurrentActor)
{
  bool LocalBool = false;

  if (CurrentActor)
  {
    if (Debuff)
    {
      TArray<AMaster_Debuff_E*> EnemyDebuffs = CurrentActor->CurrentDebuffs;

      for (AMaster_Debuff_E* LocalDebuff : EnemyDebuffs)
      {
        if (LocalDebuff->DebuffType == Debuff->DebuffType)
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
      UE_LOG(LogTemp, Error, TEXT("Debuff in IsDebuffAlreadyApplied is not valid"))
      return LocalBool;
    }
  }
  else
  {
    LocalBool = false;
    UE_LOG(LogTemp, Error, TEXT("Current Actor in IsDebuffAlreadyApplied is not valid"))
    return LocalBool;
  }
}

void AMaster_Debuff_E::RefreshDebuff(AMaster_Debuff_E* DebuffToRefresh, AMaster_Enemy* CurrentActor)
{
  AMaster_Debuff_E* DebuffToFind = CurrentActor->FindDebuffByType(DebuffToRefresh->DebuffType);

  if (DebuffToFind)
  {
    DebuffToFind->RemoveDebuff(DebuffToFind, CurrentActor);
    CurrentActor->ApplyDebuff(DebuffToRefresh->GetClass(), CurrentActor);
    DebuffToRefresh->Destroy();
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Was unable to refresh debuff. Debuff was not found in enemy CurrentDebuffs."))
  }
}

void AMaster_Debuff_E::AddDebuffToStack(AMaster_Debuff_E* DebuffToAdd, AMaster_Enemy* CurrentActor)
{
  if (CurrentActor)
  {
    if (DebuffToAdd)
    {
      AMaster_Debuff_E* DebuffToFind = CurrentActor->FindDebuffByType(DebuffToAdd->DebuffType);

      if (DebuffToFind)
      {
        DebuffToFind->AddToStack(DebuffToFind);
      }
      else
      {
        UE_LOG(LogTemp, Error, TEXT("Was unable to add debuff to stack couldn't find debuff in stack"))
      }

      DebuffToAdd->Destroy();
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Unable to add debuff to stack DebuffToAdd was not valid"))
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Unable to add debuff to stack CurrentActor was not valid"))
  }
}

void AMaster_Debuff_E::AddToStack(AMaster_Debuff_E* DebuffToAddTo)
{
  DebuffToAddTo->CurrentStackCount++;
}

void AMaster_Debuff_E::StartDebuff_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("Debuff %s has no implementation"), *this->GetName())
}

float AMaster_Debuff_E::GetCurrentTickCount()
{
  return Ticks;
}

const float AMaster_Debuff_E::GetTotalTime()
{
  return Ticks * Occurrence;
}

const bool AMaster_Debuff_E::CanContinueDebuff(AMaster_Enemy* CurrentActor)
{
  if (Ticks < 0 || CurrentActor->GetIsDead())
  {
    return false;
  }
  else
  {
    return true;
  }
}
