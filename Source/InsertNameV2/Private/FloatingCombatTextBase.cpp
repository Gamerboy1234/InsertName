// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingCombatTextBase.h"

void AFloatingCombatTextBase::SpawnFloatingCombatText_Implementation(float DamageApplied, float UpTime, AActor* HitActor)
{
  UE_LOG(LogTemp, Log, TEXT("DamageApplied: %f, UpTime: %f, HitActor: %s"), DamageApplied, UpTime, *HitActor->GetName())
}
