// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingCombatTextComponent.h"
#include "Engine/World.h"
#include "FloatingCombatTextBase.h"

// Sets default values for this component's properties
UFloatingCombatTextComponent::UFloatingCombatTextComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = false;

  UpTime = 0.2f;
}

void UFloatingCombatTextComponent::SpawnCombatText(float DamageApplied, AActor* DamagedActor)
{
  AFloatingCombatTextBase* TextSpawner = GetWorld()->SpawnActor<AFloatingCombatTextBase>(TextManger, FVector(0), FRotator(0));
  if (TextSpawner)
  {
    TextSpawner->SpawnFloatingCombatText(DamageApplied, UpTime, DamagedActor);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Unable to Spawn Floating Combat Text"))
      return;
  }
}

