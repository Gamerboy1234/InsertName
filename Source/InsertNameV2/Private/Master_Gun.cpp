// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Gun.h"
#include "PaperSpriteComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GeneralFunctions.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Components/InputComponent.h"
#include "Engine/InputDelegateBinding.h"
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

  DefaultDamage = Damage;

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

void AMaster_Gun::DamageHitActors()
{
  for (AActor* HitActor : HitActors)
  {
    if (HitActor)
    {
      UGeneralFunctions::DamageHitActor(HitActor, 0.2, Damage, GetPlayerRef());
    }
  }

  HitActors.Empty();
}

void AMaster_Gun::FireGun_Implementation()
{
  FVector TraceStart = Sprite->GetSocketLocation(FName("FireTraceStart"));
  FVector TraceEnd = Sprite->GetSocketRotation(FName("FireTraceStart")).Vector() * TraceMultipler + TraceStart;

  TArray<FHitResult> OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldStatic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldDynamic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_Pawn);
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel17);
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel8);

  FCollisionQueryParams CollisionParms;

  DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1, 0, 1);

  if (GetWorld()->LineTraceMultiByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
  {
    for (FHitResult HitObject : OutHit)
    {
      if (HitObject.Actor != NULL)
      {
        AActor* HitActor = Cast<AActor>(HitObject.Actor);

        if (HitActor)
        {
          HitActors.AddUnique(HitActor);
        }
      }
    }
    DamageHitActors();
  }
}

void AMaster_Gun::StopGunFire_Implementation()
{
  bOnCooldown = true;
}

void AMaster_Gun::OnInteract_Implementation()
{
  UpdateGunInput();
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

void AMaster_Gun::AttackKeyPressed()
{
  // for use in children called when attack is pressed
  UE_LOG(LogInventorySystem, Warning, TEXT("AttackKeyPressed on gun %s has no implementation"), *this->GetName())
}

void AMaster_Gun::AttackKeyReleased()
{
  // for use in children called when attack released
  UE_LOG(LogInventorySystem, Warning, TEXT("AttackKeyReleased on gun %s has no implementation"), *this->GetName())
}

void AMaster_Gun::UpdateGunInput()
{
  APaperWarden* LocalPlayer = GetPlayerRef();

  if (LocalPlayer)
  {
    if (!LocalPlayer->GunRef)
    {
      LocalPlayer->EquipGun(this, GunOffset, GunScale);
      bIsGunEquipped = true;
    }

    if (!InputComponent)
    {
      InputComponent = NewObject<UInputComponent>(this);
      InputComponent->RegisterComponent();
      InputComponent->bBlockInput = bBlockInput;
      InputComponent->Priority = InputPriority;

      UBlueprintGeneratedClass* BGClass = Cast<UBlueprintGeneratedClass>(GetClass());

      if (BGClass != NULL)
      {
        UInputDelegateBinding::BindInputDelegates(BGClass, InputComponent);
      }
    }

    InputComponent->BindAction("Attack", IE_Pressed, this, &AMaster_Gun::AttackKeyPressed);
    InputComponent->BindAction("Attack", IE_Released, this, &AMaster_Gun::AttackKeyReleased);
  }
  else
  {
    UE_LOG(LogInventorySystem, Error, TEXT("Unable to equip gun Player not valid"))
  }
}

const bool AMaster_Gun::GetGunOnCooldown()
{
  return bOnCooldown;
}

const float AMaster_Gun::GetDefaultDamage()
{
  return DefaultDamage;
}
