// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Blueprint.h"
#include "Master_AIController.h"
#include "SideScrollerGamemode.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"
#include "PaperWarden.h"
#include "TimerManager.h"
#include "FloatingCombatTextBase.h"

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

  bAddToKillCount = true;
}

// Setup default values for enemy when game starts
void AMaster_Enemy::BeginPlay()
{
  Super::BeginPlay();

  bIsDead = false;

  HomeLocation = GetActorLocation();

  ID = AssignID();

  AFloatingCombatTextBase* FloatingCombatTextBP = LoadObject<AFloatingCombatTextBase>(NULL, TEXT("/Game/2DPlatformingKit/Blueprints/Player/Functions/FloatingCombatManager"), NULL, LOAD_None, NULL);

  if (FloatingCombatManager)
  {
    
  }

  auto MovementComp = this->GetCharacterMovement();
  DefaultSpeed = MovementComp->GetMaxSpeed();
  DefaultGravityScale = MovementComp->GravityScale;
  DefaultMaxAcceleration = MovementComp->GetMaxAcceleration();

  // All defaults values are now set the enemy can now do stuff
  AfterBeginPlay();
}

// Assign a unique ID to an enemy 
int32 AMaster_Enemy::AssignID()
{
  ASideScrollerGamemode* LocalGameMode = Cast<ASideScrollerGamemode>(GetWorld()->GetAuthGameMode());

  if (LocalGameMode)
  {
    return LocalGameMode->GenID();
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Unable to assing ID to enemy cast to ASideScrollerGamemode failed in AssignID()"))
    return 0;
  }
}

void AMaster_Enemy::DamageEnemy_Implementation(float Damage)
{
  if (!bIsDead)
  {
    CurrentHP = FMath::Clamp<float>(CurrentHP - Damage, 0.0f, MaxHP);

    UE_LOG(LogTemp, Log, TEXT("Current HP is : %f"), CurrentHP)

    bTakenDamage = true;

    if (CurrentHP <= 0.0f)
    {
      bIsDead = true;

      SetActorEnableCollision(false);

      if (bAddToKillCount)
      {
        auto PlayerCharacter = Cast<APaperWarden>(UGameplayStatics::GetPlayerCharacter(this, 0));
        PlayerCharacter->AddToKillCount(1);
      }

      RemoveIDFromGamemode();
      OnDeath();
    }
  }
}

void AMaster_Enemy::OnDeath_Implementation()
{
  // Despawn the actor after a set delay
  SetLifeSpan(ActorDespawnDelay);
}

void AMaster_Enemy::RemoveIDFromGamemode()
{
  ASideScrollerGamemode* LocalGameMode = Cast<ASideScrollerGamemode>(GetWorld()->GetAuthGameMode());

  if (LocalGameMode)
  {
    LocalGameMode->RemoveID(ID);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Cast to ASideScrollerGamemode failed in RemoveIDFromGamemode() unable to remove ID"))
  }
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

const bool AMaster_Enemy::GetWasKnockedBacked()
{
  return bWasKnockedBack;
}

const bool AMaster_Enemy::GetIsPlayerOnEnemy()
{
  return bIsPlayerOnEnemy;
}

const bool AMaster_Enemy::GetHitPlayer()
{
  return bHitPlayer;
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
