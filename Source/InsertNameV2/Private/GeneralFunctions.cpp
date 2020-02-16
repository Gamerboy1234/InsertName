// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralFunctions.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "SideScrollerGamemode.h"
#include "Master_Pickup.h"
#include "PaperZDCharacter.h"
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

FVector UGeneralFunctions::CalcReflectionVector(FVector VectorToReflect, FVector Normal)
{
  float DotProduct = FVector::DotProduct(VectorToReflect, Normal);
  FVector NewVector = 1 * -2 * DotProduct * Normal + VectorToReflect;
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

int32 UGeneralFunctions::RandomNumber(int32 max, int32 min)
{
  if (min > max) {
    int32 temp = max;
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

int32 UGeneralFunctions::GetIDFromGamemode(UObject* WorldContextObject, AActor* ActorToAssign)
{
  ASideScrollerGamemode* LocalGameMode = Cast<ASideScrollerGamemode>(WorldContextObject->GetWorld()->GetAuthGameMode());

  if (LocalGameMode)
  {
    return LocalGameMode->GenID();
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Unable to assing ID cast to ASideScrollerGamemode failed assign ID to : %s"), *ActorToAssign->GetName())
    return 0;
  }
}

void UGeneralFunctions::RemoveIDFromGamemode(UObject* WorldContextObject, int32 ID, AActor* ActorToRemove)
{
  ASideScrollerGamemode* LocalGameMode = Cast<ASideScrollerGamemode>(WorldContextObject->GetWorld()->GetAuthGameMode());

  if (LocalGameMode)
  {
    LocalGameMode->RemoveID(ID);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Unable to assing ID cast to ASideScrollerGamemode failed to remove ID from : %s"), *ActorToRemove->GetName())
  }
}

void UGeneralFunctions::DisplayItemObtainMessage(UObject* WorldContextObject, AMaster_Pickup* Pickup, int32 Amount)
{
  ASideScrollerGamemode* LocalGameMode = Cast<ASideScrollerGamemode>(WorldContextObject->GetWorld()->GetAuthGameMode());

  if (LocalGameMode)
  {
    LocalGameMode->DisplayItemObtainedMessage(Pickup, Amount);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Unable to create message cast to ASideScrollerGamemode failed to display item : %s"), *Pickup->GetName())
  }
}

void UGeneralFunctions::RemoveActorsY(UObject* WorldContextObject, AActor* ActorRef)
{
  if (WorldContextObject && ActorRef)
  {
    float ActorsX = ActorRef->GetActorLocation().X;
    float ActorsZ = ActorRef->GetActorLocation().Z;
    FVector FilterdLocation = FVector(ActorsX, 0, ActorsZ);
    ActorRef->SetActorLocation(FilterdLocation);
  }
}
