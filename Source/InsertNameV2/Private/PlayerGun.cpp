// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGun.h"
#include "TimerManager.h"
#include "Engine.h"

void APlayerGun::AttackKeyPressed()
{
  if (!bOnCooldown)
  {
    ChargeStarted = true;

    if (GEngine)
    {
      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Charge Started"));
    }

    if (ChargeTimer.IsValid())
    {
      GetWorldTimerManager().ClearTimer(ChargeTimer);
      GetWorldTimerManager().SetTimer(ChargeTimer, this, &APlayerGun::CompleteCharge, ChargeDelay, true);
    }
    else
    {
      GetWorldTimerManager().SetTimer(ChargeTimer, this, &APlayerGun::CompleteCharge, ChargeDelay, true);
    }
  }
}

void APlayerGun::AttackKeyReleased()
{
  StopGunFire();

  if (ChargeTimer.IsValid())
  {
    GetWorldTimerManager().ClearTimer(ChargeTimer);
  }

  if (ChargeDone)
  {
    HeavyAttack();

    ChargeDone = false;
  }
  else
  {
    ChargeDone = false;

    if (ChargeStarted)
    {
      ChargeStarted = false;

      LightAttack();
    }
  }
}

void APlayerGun::LightAttack()
{
  FireGun();
}

void APlayerGun::HeavyAttack()
{
  UE_LOG(LogTemp, Log, TEXT("Heavy Attack"))
}

void APlayerGun::CompleteCharge()
{
  if (ChargeStarted)
  {
    if (GEngine)
    {
      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Charge Done"));
    }

    ChargeDone = true;
  }
}

void APlayerGun::StopGunFire_Implementation()
{
  bOnCooldown = true;
}

