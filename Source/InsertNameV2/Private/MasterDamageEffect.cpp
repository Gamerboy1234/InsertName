// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterDamageEffect.h"
#include "FloatingCombatTextComponent.h"
#include "GeneralFunctions.h"
#include "Kismet/GameplayStatics.h"


AMasterDamageEffect::AMasterDamageEffect()
{
  PrimaryActorTick.bCanEverTick = false;

  CombatTextComp = CreateDefaultSubobject<UFloatingCombatTextComponent>(TEXT("FloatingCombatTextComponent"));
  if (!ensure(CombatTextComp != nullptr)) { return; }
}

void AMasterDamageEffect::SetEffect_Implementation(AActor* CurrentActor)
{
  UE_LOG(LogTemp, Warning, TEXT("Set Effect has no blueprint event"))
}

void AMasterDamageEffect::RemoveEffect_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("Remove Effect has no blueprint event"))
}

void AMasterDamageEffect::DamageActor_Implementation(float Damage, bool bShowText, AActor* DamageInstigator)
{
  if (bAbleToTakeDamage)
  {
    if (!bIsDead)
    {
      CurrentHP = FMath::Clamp<float>(CurrentHP - Damage, 0.0f, MaxHP);

      bTakenDamage = true;

      if (bShowText && Damage > 0)
      {
        if (CombatTextComp)
        {
          CombatTextComp->SpawnCombatText(Damage, this);
        }
      }

      if (CurrentHP <= 0.0f)
      {
        bIsDead = true;

        SetActorEnableCollision(false);

        UGeneralFunctions::RemoveIDFromGamemode(this, ID, this);
        OnDeath();
      }
    }
  }
}

void AMasterDamageEffect::OnDeath_Implementation()
{
  Destroy();
}

void AMasterDamageEffect::CleanUpEffect(TSubclassOf<AMasterDamageEffect> EffectToCleanUp)
{
  TArray<AActor*> FoundActors;

  UGameplayStatics::GetAllActorsOfClass(this, EffectToCleanUp, FoundActors);

  for (AActor* Actor : FoundActors)
  {
    if (Actor)
    {
      Actor->Destroy();
    }
  }
}

void AMasterDamageEffect::BeginPlay()
{
  Super::BeginPlay();

  ID = UGeneralFunctions::GetIDFromGamemode(this, this);
}

const bool AMasterDamageEffect::GetIsDead()
{
  return bIsDead;
}

const bool AMasterDamageEffect::GetTakenDamage()
{
  return bTakenDamage;
}

const int32 AMasterDamageEffect::GetID()
{
  return ID;
}
