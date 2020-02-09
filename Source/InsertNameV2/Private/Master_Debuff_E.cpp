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

void AMaster_Debuff_E::StartDamageTimer_Implementation(AMaster_Debuff_E* DebuffToApply, AMaster_Enemy* CurrentActor, FDebuffData DebuffInfo)
{
  if (!IsDebuffAlreadyApplied(DebuffToApply, CurrentActor))
  {
    // Assign an ID to debuff from gamemode
    ID = UGeneralFunctions::GetIDFromGamemode(this, this);
    // Get Debuff Info from Struct
    Occurrence = DebuffInfo.Occurrence;
    Ticks = DebuffInfo.Ticks;
    Damage = DebuffInfo.Damage;
    DamageEffect = DebuffInfo.DamageEffect;
    EffectScale = DebuffInfo.EffectScale;
    bUseTicks = DebuffInfo.bUseTicks;

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
    RefreshDebuff(DebuffToApply, CurrentActor, DebuffInfo);
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
  TArray<AMaster_Debuff_E*> EnemyDebuffs = CurrentActor->CurrentDebuffs;

  bool LocalBool = false;
  
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

void AMaster_Debuff_E::RefreshDebuff(AMaster_Debuff_E* DebuffToRefresh, AMaster_Enemy* CurrentActor, FDebuffData DebuffInfo)
{
  AMaster_Debuff_E* DebuffToFind = nullptr;

  TArray<AMaster_Debuff_E*> EnemyDebuffs = CurrentActor->CurrentDebuffs;
  // Look for debuff to remove from enemy debuffs array
  for (AMaster_Debuff_E* CurrentDebuff : EnemyDebuffs)
  {
    if (CurrentDebuff->DebuffType == DebuffToRefresh->DebuffType)
    {
      DebuffToFind = CurrentDebuff;
      break;
    }
    else
    {
      DebuffToFind = nullptr;
      continue;
    }
  }

  if (DebuffToFind)
  {
    DebuffToFind->RemoveDebuff(DebuffToFind, CurrentActor);
    CurrentActor->ApplyDebuff(DebuffToRefresh->GetClass(), DebuffInfo, CurrentActor);
    DebuffToRefresh->Destroy();
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Was unable to refresh debuff. Debuff was not found in enemy CurrentDebuffs."))
  }
}

void AMaster_Debuff_E::AddDebuffToStack(AMaster_Debuff_E* DebuffToAdd, AMaster_Enemy* CurrentActor)
{
  for (AMaster_Debuff_E* CurrentDebuff : CurrentActor->CurrentDebuffs)
  {
    if (CurrentDebuff->DebuffType == DebuffToAdd->DebuffType)
    {
      CurrentDebuff->AddToStack(CurrentDebuff);
      break;
    }
  }
  DebuffToAdd->Destroy();
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
  if (Ticks <= 0 || CurrentActor->GetIsDead())
  {
    return false;
  }
  else
  {
    return true;
  }
}
