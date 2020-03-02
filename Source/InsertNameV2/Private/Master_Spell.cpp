// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Spell.h"
#include "GeneralFunctions.h"
#include "InsertNameV2.h"

AMaster_Spell::AMaster_Spell()
{
  ItemInfo.bIsSpell = true;
  ItemInfo.bCanBeStacked = false;
}

void AMaster_Spell::BeginPlay()
{
  Super::BeginPlay();

  this->ShowPickup(false);

  DefaultCoolDownTime = CoolDownTime;
}

void AMaster_Spell::UseItem_Implementation()
{
  OnSpellCastStart();
}

void AMaster_Spell::UnpackSpellInfo(FSavedPlayerSpell NewSpellInfo)
{
  bCurrentlyOnCooldown = NewSpellInfo.SavedbWasOnCooldown;
  bCoolDownPaused = NewSpellInfo.SavedbWasPaused;
  CoolDownTime = NewSpellInfo.SavedCoolDownTime;
  CurrentTimeLinePostion = NewSpellInfo.SavedCurrentTimeLinePostion;
  CurrentScalerValue = NewSpellInfo.SavedCurrentScalerValue;
}

void AMaster_Spell::OnSpellCastStart_Implementation()
{
  if (!bCurrentlyCasting && !bCurrentlyOnCooldown)
  {
    bCurrentlyCasting = true;
    BeginSpellCast();
  }
}

void AMaster_Spell::BeginSpellCast_Implementation()
{
  UE_LOG(LogSpellEvents, Log, TEXT("Spell %s Casted"), *this->GetName())

  OnCastComplete();
}

void AMaster_Spell::PauseCoolDown_Implementation()
{
  SetupPause();
}

void AMaster_Spell::ResumeCoolDown_Implementation()
{
  SetupResume();
}

void AMaster_Spell::OnCastComplete_Implementation()
{
  bCurrentlyOnCooldown = true;
  OnCoolDown(false, CoolDownTime);
  UGeneralFunctions::CheckPlayerCooldowns(this);
}

void AMaster_Spell::ResetSpell()
{
  bCurrentlyCasting = false;
  bCurrentlyOnCooldown = false;
  bCoolDownPaused = false;
  CoolDownTime = DefaultCoolDownTime;
  ResumeCoolDown();
}

void AMaster_Spell::SetupPause()
{
  bContinueFromLastCoolDown = true;
  bCoolDownPaused = true;
  bCurrentlyOnCooldown = true;
  bCurrentlyCasting = false;
}

void AMaster_Spell::SetupResume()
{
  bCoolDownPaused = false;
  bCurrentlyOnCooldown = true;
  bCurrentlyCasting = false;
  OnCoolDown(true, CoolDownTime);
}

const bool AMaster_Spell::GetCurrentlyOnCooldown()
{
  return bCurrentlyOnCooldown;
}

const bool AMaster_Spell::GetCurrentlyCasting()
{
  return bCurrentlyCasting;
}

const float AMaster_Spell::GetDefaultCoolDownTime()
{
  return DefaultCoolDownTime;
}
