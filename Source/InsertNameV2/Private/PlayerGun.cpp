// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGun.h"
#include "TimerManager.h"
#include "Engine.h"

APlayerGun::APlayerGun()
{
  // Setup Timeline curve
  static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/2DPlatformingKit/Blueprints/Player/MouseCurve"));
  check(Curve.Succeeded());

  CDFloat = Curve.Object;
}

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
  if (!bOnCooldown)
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

void APlayerGun::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);

  // Update Cooldown Timeline
  CooldownTimeline.TickTimeline(DeltaSeconds);
}

void APlayerGun::TimelineCallback(float Value)
{
  UE_LOG(LogTemp, Log, TEXT("CD %f"), Value)

  // TODO Update CD Widget
}

void APlayerGun::TimelineFinishedCallback()
{
  bOnCooldown = false;
}

void APlayerGun::StopGunFire_Implementation()
{
  bOnCooldown = true;

  // Start CD Timeline
  FOnTimelineFloat CDTimelineCallback;
  FOnTimelineEventStatic CDTimelineFinishedCallback;

  if (CDFloat)
  {
    CDTimelineCallback.BindUFunction(this, FName("TimelineCallback"));
    CDTimelineFinishedCallback.BindUFunction(this, FName("TimelineFinishedCallback"));
    CooldownTimeline.SetTimelineFinishedFunc(CDTimelineFinishedCallback);
    CooldownTimeline.AddInterpFloat(CDFloat, CDTimelineCallback);
    CooldownTimeline.SetLooping(false);
    CooldownTimeline.SetPlayRate(1.0f);
    CooldownTimeline.SetTimelineLength(FireRate);
    CooldownTimeline.PlayFromStart();
  }
}
