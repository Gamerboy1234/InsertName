// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBeamEffectBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGunBeamEffectBase::AGunBeamEffectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  
  RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
  RootComponent = RootComp;

  BeamStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeamStart"));
  BeamStart->SetupAttachment(RootComp);

  BeamEnd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeamEnd"));
  BeamEnd->SetupAttachment(RootComp);

  BeamEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BeamEffect"));
  BeamEffect->SetupAttachment(RootComp);
}

void AGunBeamEffectBase::SetupBeam(FVector StartLocation, FVector EndLocation, float LifeSpan, FLinearColor ColorToSet, float BeamBrightnessToSet, float BeamExponentToSet)
{
  BeamColor = ColorToSet;
  BeamBrightness = BeamBrightnessToSet;
  BeamExponent = BeamExponentToSet;

  BeamStart->SetWorldLocation(StartLocation);
  BeamStart->SetCollisionEnabled(ECollisionEnabled::NoCollision);

  BeamEnd->SetWorldLocation(EndLocation);
  BeamEnd->SetCollisionEnabled(ECollisionEnabled::NoCollision);

  if (BeamEffect)
  {
    UMaterialInterface* LocalMateral = BeamEffect->GetMaterial(0);
    UMaterialInstanceDynamic* LocalMatInstance = BeamEffect->CreateDynamicMaterialInstance(0, LocalMateral, FName(""));
    LocalMatInstance->SetVectorParameterValue(FName("Color"), BeamColor);
    LocalMatInstance->SetScalarParameterValue(FName("Brightness"), BeamBrightness);
    LocalMatInstance->SetScalarParameterValue(FName("Exponent"), BeamExponent);

    BeamEffect->SetBeamSourcePoint(0, BeamStart->GetComponentLocation(), 0);
    BeamEffect->SetBeamEndPoint(0, BeamEnd->GetComponentLocation());
  }

  SetLifeSpan(LifeSpan);
}

void AGunBeamEffectBase::UpdateBeamEndPoint(FVector NewLocation)
{
  BeamEnd->SetWorldLocation(NewLocation);

  if (BeamEffect)
  {
    BeamEffect->SetBeamSourcePoint(0, BeamStart->GetComponentLocation(), 0);
    BeamEffect->SetBeamEndPoint(0, BeamEnd->GetComponentLocation());
  }
}

