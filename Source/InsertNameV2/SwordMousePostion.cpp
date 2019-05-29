// Fill out your copyright notice in the Description page of Project Settings.

#include "SwordMousePostion.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"


FVector2D GetGameViewportSize()
{
  FVector2D Result = FVector2D(1, 1);

  if (GEngine && GEngine->GameViewport)
  {
    GEngine->GameViewport->GetViewportSize(Result);
  }

  return Result;
}


float x = 0;
float resX = 0;
bool USwordMousePostion::SwordMousePosition(float mouseX, float mouseY)
{
  resX = GetGameViewportSize().X;
  resX = resX / 2;
  if (mouseX < resX)
  {
    return false;
  }
  else
  {
    return true;
  }
 
  
 
}



