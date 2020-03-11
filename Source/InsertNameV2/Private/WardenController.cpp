// Fill out your copyright notice in the Description page of Project Settings.


#include "WardenController.h"
#include "PaperWarden.h"
#include "Master_Gun.h"
#include "InsertNameV2.h"

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
