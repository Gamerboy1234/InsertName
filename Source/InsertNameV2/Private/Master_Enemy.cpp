// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Blueprint.h"
#include "Master_AIController.h"
#include "SideScrollerGamemode.h"
#include "Engine/World.h"

AMaster_Enemy::AMaster_Enemy()
{
  // HP Setup
  CurrentHP = 10;
  MaxHP = 10;
  ActorDespawnDelay = 1.0;
  HPBarHideDelay = 3.0;
  bCanBeStunned = true;

  DamageToPlayer = 1.0;

  ControllerToUse = AMaster_AIController::StaticClass();

  HomeLocation = GetActorLocation();
}

void AMaster_Enemy::BeginPlay()
{
  Super::BeginPlay();

  ID = AssignID();

  UE_LOG(LogTemp, Log, TEXT("Enemy ID: %i"), ID) 
}

int32 AMaster_Enemy::AssignID()
{
  ASideScrollerGamemode* LocalGameMode = Cast<ASideScrollerGamemode>(GetWorld()->GetAuthGameMode());

  if (LocalGameMode)
  {
    return LocalGameMode->GenID();
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Unable to assing ID to enemy"))
    return 0;
  }
}

void AMaster_Enemy::DamageEnemy_Implementation(float Damage)
{
  CurrentHP = FMath::Clamp<float>(CurrentHP - Damage, 0.0f, MaxHP);

  bTakenDamage = true;

  UE_LOG(LogTemp, Log, TEXT("Enemy taken damage amount: %f CurrentHP is at: %f"), Damage, CurrentHP)

  if (CurrentHP <= 0.0f)
  {
    RemoveIDFromGamemode();
    OnDeath();
  }
}

void AMaster_Enemy::OnDeath_Implementation()
{
  Destroy();
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
    UE_LOG(LogTemp, Warning, TEXT("Cast to ASideScrollerGamemode failed in RemoveIDFromGamemode()"))
  }
}

const FVector AMaster_Enemy::GetHomeLocation()
{
  return HomeLocation;
}

const int32 AMaster_Enemy::GetID()
{
  return ID;
}
