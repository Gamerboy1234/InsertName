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

  WarlustEffect = LoadObject<UBlueprint>(NULL, TEXT("/Game/2DPlatformingKit/Blueprints/BP_Combat/Spells/SpellEffects/Particles/Warlust_Effect_BP"), NULL, 0, NULL);
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

const FVector AMaster_Enemy::GetHomeLocation()
{
  return HomeLocation;
}

const int32 AMaster_Enemy::GetID()
{
  return ID;
}
