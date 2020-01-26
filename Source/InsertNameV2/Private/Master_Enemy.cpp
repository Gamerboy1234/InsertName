// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Blueprint.h"
#include "Master_AIController.h"
#include "SideScrollerGamemode.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GeneralFunctions.h"
#include "PaperFlipbookComponent.h"
#include "Master_Debuff_E.h"
#include "PaperWarden.h"
#include "FloatingCombatTextComponent.h"


AMaster_Enemy::AMaster_Enemy()
{
  // HP Setup
  CurrentHP = 10;
  MaxHP = 10;
  ActorDespawnDelay = 2.0;
  HPBarHideDelay = 3.0;
  bCanBeStunned = true;

  DamageToPlayer = 1.0;

  ControllerToUse = AMaster_AIController::StaticClass();
  if (!ensure(ControllerToUse != nullptr)) { return; }

  bAddToKillCount = true;

  CombatTextComp = CreateDefaultSubobject<UFloatingCombatTextComponent>(TEXT("FloatingCombatTextComponent"));
  if (!ensure(CombatTextComp != nullptr)) { return; }
}

// Setup default values for enemy when game starts
void AMaster_Enemy::BeginPlay()
{
  Super::BeginPlay();

  bIsDead = false;

  HomeLocation = GetActorLocation();

  ID = UGeneralFunctions::GetIDFromGamemode(this, this);

  auto MovementComp = this->GetCharacterMovement();
  DefaultSpeed = MovementComp->GetMaxSpeed();
  DefaultGravityScale = MovementComp->GravityScale;
  DefaultMaxAcceleration = MovementComp->GetMaxAcceleration();

  // All defaults values are now set the enemy can now do stuff
  AfterBeginPlay();
}

AActor* AMaster_Enemy::ApplyDebuff(TSubclassOf<AMaster_Debuff_E> DebuffToApply, FDebuffData DebuffData, AActor* Target)
{
  if (Target)
  {
    MostRecentDebuff = GetWorld()->SpawnActor<AMaster_Debuff_E>(DebuffToApply, FVector(0), FRotator(0));
    if (MostRecentDebuff)
    {
      MostRecentDebuff->StartDamageTimer(MostRecentDebuff, this, DebuffData);
      return MostRecentDebuff;
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Was unable to apply debuff"))
      return MostRecentDebuff;
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Debuff target is not valid"))
    return nullptr;
  }
}

void AMaster_Enemy::RemoveAllDebuffs()
{
  for (AMaster_Debuff_E* CurrentDebuff : CurrentDebuffs)
  {
    CurrentDebuff->RemoveDebuff(CurrentDebuff);
  }
}

void AMaster_Enemy::DamageEnemy_Implementation(float Damage)
{
  if (!bIsDead)
  {
    CurrentHP = FMath::Clamp<float>(CurrentHP - Damage, 0.0f, MaxHP);

    UE_LOG(LogTemp, Log, TEXT("Current HP is : %f"), CurrentHP)

    bTakenDamage = true;

    if (CombatTextComp)
    {
      CombatTextComp->SpawnCombatText(Damage, this);
    }

    if (CurrentHP <= 0.0f)
    {
      bIsDead = true;

      SetActorEnableCollision(false);

      if (bAddToKillCount)
      {
        auto PlayerCharacter = Cast<APaperWarden>(UGameplayStatics::GetPlayerCharacter(this, 0));
        PlayerCharacter->AddToKillCount(1);
      }

      UGeneralFunctions::RemoveIDFromGamemode(this, ID, this);
      RemoveAllDebuffs();
      OnDeath();
    }
  }
}

void AMaster_Enemy::OnDeath_Implementation()
{
  // Despawn the actor after a set delay
  SetLifeSpan(ActorDespawnDelay);
}

void AMaster_Enemy::AfterBeginPlay_Implementation()
{
  // for use in children
}

// Getter Functions for private var's 
const FVector AMaster_Enemy::GetHomeLocation()
{
  return HomeLocation;
}

const int32 AMaster_Enemy::GetID()
{
  return ID;
}

const bool AMaster_Enemy::GetTakenDamage()
{
  return bTakenDamage;
}

const bool AMaster_Enemy::GetIsStunned()
{
  return bIsStunned;
}

const float AMaster_Enemy::GetDefaultSpeed()
{
  return DefaultSpeed;
}

const float AMaster_Enemy::GetDefaultGravityScale()
{
  return DefaultGravityScale;
}

const float AMaster_Enemy::GetDefaultMaxAcceleration()
{
  return DefaultMaxAcceleration;
}

const bool AMaster_Enemy::GetIsDead()
{
  return bIsDead;
}
