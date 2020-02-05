// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_AIController.h"
#include "Master_Enemy.h"

void AMaster_AIController::BeginPlay()
{
  auto CurrentPawn = Cast<AMaster_Enemy>(GetPawn());

  if (CurrentPawn)
  {
    if (CurrentPawn->bUseBT)
    {
      RunBehaviorTree(CurrentPawn->BehaviorTreeToUse);
    }
  }
}
