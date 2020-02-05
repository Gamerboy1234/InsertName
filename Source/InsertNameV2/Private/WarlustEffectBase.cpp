// Fill out your copyright notice in the Description page of Project Settings.


#include "WarlustEffectBase.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AWarlustEffectBase::AWarlustEffectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  BeamEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Beam Effect"));
  if (!ensure(BeamEffect != nullptr)) { return; }
  RootComponent = BeamEffect;
}

void AWarlustEffectBase::AddLine_Implementation(APaperWarden* PlayerRef, AMaster_Enemy* EnemyRef)
{
  if (BeamEffect)
  {
    if (PlayerRef)
    {
      if (EnemyRef)
      {
        BeamEffect->SetActorParameter(TEXT("Beam Source"), PlayerRef);
        BeamEffect->SetActorParameter(TEXT("Beam Target"), EnemyRef);
      }
      else
      {
        UE_LOG(LogTemp, Error, TEXT("Unable to draw line to enemy. Enemy is not valid."))
        return;
      }
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Unable to draw line from player. Player is not valid."))
      return;
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Beam effect not set"))
    return;
  }
}

void AWarlustEffectBase::RemoveLine_Implementation()
{
  Destroy();
}


