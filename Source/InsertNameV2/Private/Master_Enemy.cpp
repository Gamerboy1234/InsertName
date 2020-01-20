// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Enemy.h"
#include "UObject/ConstructorHelpers.h"

AMaster_Enemy::AMaster_Enemy(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
  static ConstructorHelpers::FClassFinder<AActor> ClassFinder(TEXT("/Game/2DPlatformingKit/Blueprints/BP_Combat/Spells/SpellEffects/Particles/Warlust_Effect_BP"));
  if (ClassFinder.Class)
    WarlustEffect = ClassFinder.Class;
}
