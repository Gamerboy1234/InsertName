// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Debuff_E.h"
#include "SideScrollerGamemode.h"
#include "GeneralFunctions.h"
#include "Master_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MasterDamageEffect.h"
#include "TimerManager.h"
#include "Engine/World.h"

void AMaster_Debuff_E::StartDamageTimer_Implementation(AMaster_Debuff_E* DebuffToApply, AActor* CurrentActor, FDebuffData DebuffInfo)
{
  if (!IsDebuffAlreadyApplied(DebuffToApply))
  {
    SetupDebuffInfo(DebuffInfo);

    // Spawn and attach damage effect to current enemy actor
    auto SpawnTransform = FTransform(FRotator(0), FVector(0), EffectScale);
    CurrentEffect = GetWorld()->SpawnActor<AMasterDamageEffect>(DamageEffect, SpawnTransform);
    CurrentEffect->SetEffect(CurrentActor);
    CurrentEffect->AttachToComponent(CurrentEnemy->GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

    // Create Debuff timer
    GetWorldTimerManager().SetTimer(DebuffTimer, this, &AMaster_Debuff_E::StartDebuff, Occurrence);
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

      CleanUpDebuff(DebuffToRemove->GetClass());
    }
    else
    {
      auto IndexToRemove = CurrentEnemy->CurrentDebuffs.Find(DebuffToRemove);
      CurrentEnemy->CurrentDebuffs.RemoveAt(IndexToRemove);

      CleanUpDebuff(DebuffToRemove->GetClass());
    }
  }
}

void AMaster_Debuff_E::CleanUpDebuff(TSubclassOf<AMaster_Debuff_E> DebuffToCleanUp)
{
  TSubclassOf<AMaster_Debuff_E> classToFind;
  
  classToFind = DebuffToCleanUp->GetClass();
  
  TArray<AActor*> FoundDebuffs;
  
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, FoundDebuffs);

  for (AActor* Actor : FoundDebuffs)
  {
    if (Actor)
    {
      Actor->Destroy();
    }
  }
}

const bool AMaster_Debuff_E::IsDebuffAlreadyApplied(AMaster_Debuff_E* Debuff)
{
  if (CurrentEnemy)
  {
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

void AMaster_Debuff_E::SetupDebuffInfo(FDebuffData DebuffInfo)
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
}

const float AMaster_Debuff_E::GetTotalTime()
{
  return Ticks * Occurrence;
}
