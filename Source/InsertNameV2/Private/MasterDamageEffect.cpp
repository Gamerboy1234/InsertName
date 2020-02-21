// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterDamageEffect.h"
#include "Kismet/GameplayStatics.h"


void AMasterDamageEffect::SetEffect_Implementation(AActor* CurrentActor)
{
  UE_LOG(LogTemp, Warning, TEXT("Set Effect has no blueprint event"))
}

void AMasterDamageEffect::RemoveEffect_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("Remove Effect has no blueprint event"))
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
