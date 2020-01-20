// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Blueprint.h"

AMaster_Enemy::AMaster_Enemy()
{
  CurrentHP = 10;
  MaxHP = 10;

}

void AMaster_Enemy::BeginPlay()
{
  Super::BeginPlay();

  WarlustEffect = LoadObject<UBlueprint>(NULL, TEXT("/Game/2DPlatformingKit/Blueprints/BP_Combat/Spells/SpellEffects/Particles/Warlust_Effect_BP"), NULL, 0, NULL);
}
