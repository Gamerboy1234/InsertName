// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Gun.h"
#include "PaperSpriteComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GeneralFunctions.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "PaperWarden.h"
#include "InsertNameV2.h"

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
  Damage = 3.0f;

  // Setup Timeline curve
  static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/2DPlatformingKit/Blueprints/Player/MouseCurve"));
  check(Curve.Succeeded());

  CurveFloat = Curve.Object;
}

void AMaster_Gun::BeginPlay()
{
  Super::BeginPlay();

  // Start Mouse Timeline
  if (CurveFloat)
  {
    FOnTimelineFloat MouseTimelineProgress;
    MouseTimelineProgress.BindUFunction(this, FName("MouseTimelineProgress"));
    MouseTimeline.AddInterpFloat(CurveFloat, MouseTimelineProgress);
    MouseTimeline.SetLooping(true);
    MouseTimeline.SetPlayRate(5.0f);
    MouseTimeline.PlayFromStart();
  }
}

void AMaster_Gun::RotateGunToMouse()
{
  APaperWarden* LocalPlayer = GetPlayerRef();

  if (LocalPlayer)
  {
    FRotator MouseRot = UGeneralFunctions::GetMouseRotation(this);

    LocalPlayer->RotateGun(MouseRot);
  }
  else
  {
    UE_LOG(LogInventorySystem, Error, TEXT("Unable to update mouse rotation Player is not valid"))
  }
}

void AMaster_Gun::FireGun_Implementation()
{

}

void AMaster_Gun::StopGunFire_Implementation()
{
  bOnCooldown = true;
}

void AMaster_Gun::OnInteract_Implementation()
{
  APaperWarden* LocalPlayer = GetPlayerRef();

  if (LocalPlayer)
  {
    LocalPlayer->EquipGun(this, GunOffset, GunScale);
    bIsGunEquipped = true;

    APlayerController* PController = GetWorld()->GetFirstPlayerController();

    this->EnableInput(PController);
  }
  else
  {
    UE_LOG(LogInventorySystem, Error, TEXT("Unable to equip gun Player not valid"))
  }
}

void AMaster_Gun::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);

  // Update Mouse Timeline
  MouseTimeline.TickTimeline(DeltaSeconds);
}


void AMaster_Gun::MouseTimelineProgress(float Value)
{
  RotateGunToMouse();
}

const bool AMaster_Gun::GetGunOnCooldown()
{
  return bOnCooldown;
}
