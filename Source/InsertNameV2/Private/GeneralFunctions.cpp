// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralFunctions.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

bool UGeneralFunctions::IsNumberNegative(float number)
{
  if (number >= 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

float UGeneralFunctions::TickDamage(float Tick, float GunDamage, float BuffAmount)
{
  float temp1 = Tick * BuffAmount + 1;
  float temp2 = temp1 * GunDamage;
  return temp2;
}

FVector UGeneralFunctions::CalcReflectionVector(FVector VectorToReflect, FVector Normal, float Bounciness)
{
  Bounciness = FMath::Clamp<float>(Bounciness, 0, 1);
  float DotProduct = FVector::DotProduct(VectorToReflect, Normal);
  FVector NewVector = Bounciness * -2 * DotProduct * Normal + VectorToReflect;
  return NewVector;
}

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
bool UGeneralFunctions::MouseLeftOrRight(float mouseX, float mouseY)
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

int UGeneralFunctions::RandomNumber(int max, int min)
{
  if (min > max) {
    int temp = max;
    max = min;
    min = temp;
  }

  static bool first = true;
  if (first)
  {
    srand(time(NULL)); //seeding for the first time only!
    first = false;
  }
  return min + rand() % ((max + 1) - min);
}
