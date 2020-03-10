// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Gun.h"
#include "PaperSpriteComponent.h"
#include "GeneralFunctions.h"

AMaster_Gun::AMaster_Gun()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Set Default Values
  TraceMultipler = 125.0f;
  TrailDespawn = 0.08f;
  GunScale = FVector(0.05);
  GunOffset = FVector(2.0f, 0, 0);
  TrailScale = FVector(0.04);
  TrailColor = FLinearColor(0.5, 0.023501, 0.0, 1.0);
  TrailGlowAmount = 1;
  KnockBackMultipler = 1000;
  KnockbackRangeMultipler = 200;
  FireRate = 1.0f;
  bFadeOut = true;
  SocketName = "Gun";

  // TODO Setup Timeline
}

void AMaster_Gun::BeginPlay()
{
  Super::BeginPlay();


}

void AMaster_Gun::RotateGun()
{

}

void AMaster_Gun::FireGun_Implementation()
{

}

void AMaster_Gun::StopGunFire_Implementation()
{

}

void AMaster_Gun::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);


}
