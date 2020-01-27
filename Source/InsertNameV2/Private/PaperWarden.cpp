// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperWarden.h"

int32 APaperWarden::AddToKillCount(int32 AmountToadd)
{
  return KillCount += AmountToadd;
}

const int32 APaperWarden::GetCurrentKillCount()
{
  return KillCount;
}

void APaperWarden::LoadKillCount(int32 KillCountToLoad)
{
  KillCount = KillCountToLoad;
}

void APaperWarden::HealPlayer_Implementation(float HealAmount)
{
  UE_LOG(LogTemp, Warning, TEXT("Player Heal event has no Implementation"))
}
