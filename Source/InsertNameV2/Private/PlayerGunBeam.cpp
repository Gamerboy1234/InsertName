// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGunBeam.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

APlayerGunBeam::APlayerGunBeam()
{
  ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("/Game/2DPlatformingKit/Blueprints/Inventory/Blueprints/GunEffects/Lasers/PS_GunLaser"));
  check(ParticleSystem.Succeeded());

  BeamEffect->Template = ParticleSystem.Object;
}
