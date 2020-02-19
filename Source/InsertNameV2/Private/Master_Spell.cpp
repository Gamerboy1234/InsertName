// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Spell.h"

AMaster_Spell::AMaster_Spell()
{
  ItemInfo.bIsSpell = true;
  ItemInfo.bCanBeStacked = false;
}

void AMaster_Spell::BeginPlay()
{
  Super::BeginPlay();

  this->ShowPickup(false);
}

void AMaster_Spell::UseItem_Implementation()
{
  OnSpellCastStart();
}

void AMaster_Spell::OnSpellCastStart_Implementation()
{
  if (!CurrentlyCasting && !CurrentlyOnCooldown)
  {
    CurrentlyCasting = true;
    BeginSpellCast();
  }
}

void AMaster_Spell::BeginSpellCast_Implementation()
{
  UE_LOG(LogTemp, Log, TEXT("Spell %s Casted"), *this->GetName())

  OnCastComplete();
}

void AMaster_Spell::OnCastComplete_Implementation()
{
  CurrentlyOnCooldown = true;
  OnCoolDown();
}

void AMaster_Spell::ResetSpell()
{
  CurrentlyCasting = false;
  CurrentlyOnCooldown = false;
}

bool AMaster_Spell::GetCurrentlyOnCooldown()
{
  return CurrentlyOnCooldown;
}

bool AMaster_Spell::GetCurrentlyCasting()
{
  return CurrentlyCasting;
}
