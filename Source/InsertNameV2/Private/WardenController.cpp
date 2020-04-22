// Fill out your copyright notice in the Description page of Project Settings.


#include "WardenController.h"
#include "PaperWarden.h"
#include "Master_Gun.h"
#include "InsertNameV2.h"

AWardenController::AWardenController()
{
  bIsUsingGamepad = false;
  bResetGamepadDetectionAfterNoInput = true;
  GamepadTimeout = 5.f;
}

void AWardenController::BuildInputStack(TArray< UInputComponent* >& InputStack)
{
  APaperWarden* LocalPlayer = Cast<APaperWarden>(GetPawnOrSpectator());

  if (LocalPlayer)
  {
    AMaster_Gun* CurrentGun = Cast<AMaster_Gun>(LocalPlayer->GunRef);

    if (CurrentGun)
    {
      if (CurrentGun->InputComponent)
      {
        InputStack.Push(CurrentGun->InputComponent);
      }
    }
  }

  Super::BuildInputStack(InputStack);
}

bool AWardenController::InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
  bool ret = Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
  _UpdateGamepad(bGamepad);
  return ret;
}

bool AWardenController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
  bool ret = Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
  _UpdateGamepad(bGamepad);
  return ret;
}

void AWardenController::PlayerTick(float DeltaTime)
{
  Super::PlayerTick(DeltaTime);
  if (IsLocalController() && bResetGamepadDetectionAfterNoInput && bIsUsingGamepad)
  {
    float now = GetWorld()->TimeSeconds;
    if (now > LastGamepadInputTime + GamepadTimeout)
    {
      bIsUsingGamepad = false;
      ControllerDisconnected();
    }
  }
}
