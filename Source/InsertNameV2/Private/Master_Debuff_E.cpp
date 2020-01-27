// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Debuff_E.h"
#include "SideScrollerGamemode.h"
#include "GeneralFunctions.h"
#include "Master_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MasterDamageEffect.h"
#include "TimerManager.h"
#include "Engine/World.h"

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

    SpawnEffect(CurrentActor);
   
    // Create Debuff timer
    GetWorldTimerManager().SetTimer(DebuffTimer, this, &AMaster_Debuff_E::StartDebuff, Occurrence, true);
  }
}

void AMaster_Debuff_E::RemoveDebuff(AMaster_Debuff_E* DebuffToRemove)
{
  if (CurrentEnemy)
  {
    if (CurrentEffect)
    {
      CurrentEffect->RemoveEffect();
      
      auto IndexToRemove = CurrentEnemy->CurrentDebuffs.Find(DebuffToRemove);
      CurrentEnemy->CurrentDebuffs.RemoveAt(IndexToRemove);
      GetWorldTimerManager().ClearTimer(DebuffTimer);
      DebuffToRemove->Destroy();
    }
    else
    {
      auto IndexToRemove = CurrentEnemy->CurrentDebuffs.Find(DebuffToRemove);
      CurrentEnemy->CurrentDebuffs.RemoveAt(IndexToRemove);
      GetWorldTimerManager().ClearTimer(DebuffTimer);
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

    CurrentEffect->SetEffect(CurrentActor);
    CurrentEffect->AttachToComponent(CurrentEnemy->GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Unable to Spawn Effect"))
  }
}

AMaster_Debuff_E* AMaster_Debuff_E::FindDebuffByID(AMaster_Debuff_E* Debuff)
{
  TArray<AActor*> FoundDebuffs;

  AMaster_Debuff_E* DebuffToFind = nullptr;

  UGameplayStatics::GetAllActorsOfClass(GetWorld(), Debuff->GetClass(), FoundDebuffs);

  for (AActor* CurrentDebuff : FoundDebuffs)
  {
    auto DebuffID = Cast<AMaster_Debuff_E>(CurrentDebuff->GetClass());
    if (DebuffID->ID == Debuff->ID)
    {
      DebuffToFind = DebuffID;
      break;
    }
    else
    {
      DebuffToFind = nullptr;
      continue;
    }
  }
  return DebuffToFind;
}

const bool AMaster_Debuff_E::IsDebuffAlreadyApplied(AMaster_Debuff_E* Debuff, AMaster_Enemy* CurrentActor)
{
  if (CurrentActor)
  {
    CurrentEnemy = CurrentActor;

    auto CurrentEnemyDebuffs = CurrentEnemy->CurrentDebuffs;

    if (CurrentEnemyDebuffs.Contains(Debuff))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Current Enemy is not Vaild"))
    return false;
  }
}

void AMaster_Debuff_E::StartDebuff_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("Debuff %s has no implementation"), *this->GetName())
}

float AMaster_Debuff_E::GetCurrentTickCount()
{
  return Ticks;
}

void AMaster_Debuff_E::SetupDebuffInfo(FDebuffData DebuffInfo)
{
}


const float AMaster_Debuff_E::GetTotalTime()
{
  return Ticks * Occurrence;
}
