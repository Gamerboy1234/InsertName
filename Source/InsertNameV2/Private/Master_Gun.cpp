// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Gun.h"
#include "PaperSpriteComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GeneralFunctions.h"
#include "MasterDamageEffect.h"
#include "Master_Magnet.h"
#include "Components/WidgetComponent.h"
#include "GunCoolDownBar.h"
#include "Master_Enemy.h"
#include "Components/BoxComponent.h"
#include "GunBeamEffectBase.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Components/InputComponent.h"
#include "Engine/InputDelegateBinding.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperWarden.h"
#include "InsertNameV2.h"

AMaster_Gun::AMaster_Gun()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Create front barrel collision
  BarrelCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BarrelCollision"));
  BarrelCollision->SetupAttachment(RootComponent);

  // Create gun cooldown widget component
  WidgetCompFront = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetCompFront"));
  WidgetCompFront->SetupAttachment(RootComponent);
  WidgetCompBack = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetCompBack"));
  WidgetCompBack->SetupAttachment(RootComponent);

  // Set Default Values
  TraceMultipler = 125.0f;
  GunScale = FVector(0.05);
  GunOffset = FVector(2.0f, 0, 0);
  BeamColor = FLinearColor(0.5, 0.023501, 0.0, 1.0);
  BeamBrightness = 20.0f;
  BeamExponent = 4;
  BeamDespawnDelay = 0.08f;
  KnockBackMultipler = 1000;
  KnockbackRangeMultipler = 200;
  GunCoolDown = 1.0f;
  SocketName = "Gun";
  Damage = 3.0f;

  // Setup Timeline curve
  static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/2DPlatformingKit/Blueprints/Player/MouseCurve"));
  check(Curve.Succeeded());

  CurveFloat = Curve.Object;

  // Get gun cooldown widget class
  ConstructorHelpers::FClassFinder<UUserWidget> LocalCDWidget(TEXT("/Game/2DPlatformingKit/Widgets/Player_Widgets/GunCoolDown"));
  check(LocalCDWidget.Succeeded());

  CDClass = LocalCDWidget.Class;

  WidgetCompFront->SetWidgetClass(CDClass);
  WidgetCompBack->SetWidgetClass(CDClass);
}

void AMaster_Gun::BeginPlay()
{
  Super::BeginPlay();

  SetupCDWidget();

  DefaultDamage = Damage;
  bCanFireTrace = true;

  BarrelCollision->OnComponentBeginOverlap.AddDynamic(this, &AMaster_Gun::OnOverlapBegin);
  BarrelCollision->OnComponentEndOverlap.AddDynamic(this, &AMaster_Gun::OnOverlapEnd);

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
   bool bCanSetRot = LocalPlayer->CanSetMouseRot();

   if (bCanSetRot)
   {
     FRotator NewRotation = GetMouseRotation();

     APlayerController* PC = GetWorld()->GetFirstPlayerController();

     if (PC)
     {
        float MouseX = 0;
        float MouseY = 0;

        if (PC->GetMousePosition(MouseX, MouseY))
        {
          // Keep gun on Y level 1 and adjust gun rotation
          if (!UGeneralFunctions::MouseLeftOrRight(MouseX, MouseY))
          {
            FRotator AdjustedRot = FRotator(NewRotation.Pitch, NewRotation.Yaw, -180);

            LocalPlayer->EquippedGun->SetActorRotation(AdjustedRot);
            LocalPlayer->GunRef->SetActorRotation(AdjustedRot);

            FVector CurrentLocation = LocalPlayer->EquippedGun->GetActorLocation();
            FVector AdjustedLocation = FVector(CurrentLocation.X, 1, CurrentLocation.Z);

            LocalPlayer->EquippedGun->SetActorLocation(AdjustedLocation);

            LocalPlayer->RotatePlayer(FRotator(0, 180, 0));
          }
          else
          {
            FVector CurrentLocation = LocalPlayer->EquippedGun->GetActorLocation();
            FVector AdjustedLocation = FVector(CurrentLocation.X, 1, CurrentLocation.Z);

            LocalPlayer->EquippedGun->SetActorLocation(AdjustedLocation);
            LocalPlayer->EquippedGun->SetActorRotation(NewRotation);
            LocalPlayer->GunRef->SetActorRotation(NewRotation);

            LocalPlayer->RotatePlayer(FRotator(0));
          }
        }
     }
     else
     {
       UE_LOG(LogInventorySystem, Error, TEXT("Unable to RotateGunToMouse Player Controller is not valid"))
     }
   }
  }
  else
  {
    UE_LOG(LogInventorySystem, Error, TEXT("Unable to update mouse rotation Player is not valid"))
  }
}

void AMaster_Gun::DamageOrKnockHitActors(bool bApplyKnockback)
{
  for (AActor* HitActor : HitActors)
  {
    if (HitActor)
    {
      if (bApplyKnockback)
      {
        AMaster_Enemy* HitEnemy = Cast<AMaster_Enemy>(HitActor);

        if (HitEnemy)
        {
          UGeneralFunctions::ApplyKnockbackToEnemy(HitEnemy, KnockBackMultipler);
        }
      }
      else
      {
        UGeneralFunctions::DamageHitActor(HitActor, Damage, GetPlayerRef(), true);
      }
    }
  }

  HitActors.Empty();
}

bool AMaster_Gun::DidTraceHitEnemy(AActor* HitActor)
{
  if (HitActor)
  {
    AMaster_Enemy* HitEnemy = Cast<AMaster_Enemy>(HitActor);

    if (HitEnemy)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool AMaster_Gun::DidTraceHitMagnet(AActor* HitActor)
{
  if (HitActor)
  {
    AMaster_Magnet* HitMagnet = Cast<AMaster_Magnet>(HitActor);

    if (HitMagnet)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool AMaster_Gun::DidTraceHitDamageEffect(AActor* HitActor)
{
  if (HitActor)
  {
    AMasterDamageEffect* HitEffect = Cast<AMasterDamageEffect>(HitActor);

    if (HitEffect)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

void AMaster_Gun::SetupCDWidget()
{
  CDWidgetFront = Cast<UGunCoolDownBar>(WidgetCompFront->GetUserWidgetObject());

  if (CDWidgetFront)
  {
    CDWidgetFront->SetUpWidget(0, GunCoolDown);

    CDWidgetBack = Cast<UGunCoolDownBar>(WidgetCompBack->GetUserWidgetObject());
    
    if (CDWidgetBack)
    {
      CDWidgetBack->SetUpWidget(0, GunCoolDown);
    }
    else
    {
      UE_LOG(LogInventorySystem, Error, TEXT("Unable to SetupCDWidget CDWidgetBack was not valid"))
    }
  }
  else
  {
    UE_LOG(LogInventorySystem, Error, TEXT("Unable to SetupCDWidget CDWidgetFront was not valid"))
  }
}

void AMaster_Gun::FireMultiLineTrace_Implementation(bool bApplyKnockback)
{
  if (bCanFireTrace)
  {
    TraceStart = Sprite->GetSocketLocation(FName("FireTraceStart"));
    TraceEnd = Sprite->GetSocketRotation(FName("FireTraceStart")).Vector() * TraceMultipler + TraceStart;

    TArray<FHitResult> OutHit;
    FCollisionObjectQueryParams ObjectsToTest;
    ObjectsToTest.AddObjectTypesToQuery(ECC_WorldStatic);
    ObjectsToTest.AddObjectTypesToQuery(ECC_WorldDynamic);
    ObjectsToTest.AddObjectTypesToQuery(ECC_Pawn);
    ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel16);
    ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel8);

    FCollisionQueryParams CollisionParms;
    CollisionParms.AddIgnoredActor(this);

    if (GetWorld()->LineTraceMultiByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
    {
      if (OutHit.Num() > 0)
      {
        for (FHitResult HitObject : OutHit)
        {
          if (HitObject.Actor != NULL)
          {
            AActor* HitActor = Cast<AActor>(HitObject.Actor);

            if (HitActor)
            {
              if (DidTraceHitEnemy(HitActor))
              {
                SpawnLaserBeam(TraceStart, TraceEnd);

                HitActors.AddUnique(HitActor);
              }
              else if (DidTraceHitMagnet(HitActor))
              {
                AMaster_Magnet* Magnet = Cast<AMaster_Magnet>(HitActor);

                if (Magnet)
                {
                  SpawnLaserBeam(TraceStart, HitObject.ImpactPoint);

                  Magnet->Deactivate(HitObject.ImpactPoint, true);
                }
              }
              else if (DidTraceHitDamageEffect(HitActor))
              {
                SpawnLaserBeam(TraceStart, TraceEnd);

                HitActors.Add(HitActor);
              }
              else
              {
                SpawnLaserBeam(TraceStart, HitObject.ImpactPoint);
              }

              if (GetPlayerRef()->bDebugGunHit)
              {
                UE_LOG(LogInventorySystem, Log, TEXT("Gun Hit %s"), *HitObject.Actor->GetName())
              }
            }
          }
        }
      }
      else
      {
        SpawnLaserBeam(TraceStart, TraceEnd);
      }
      DamageOrKnockHitActors(bApplyKnockback);
    }
    else
    {
      SpawnLaserBeam(TraceStart, TraceEnd);
    }
  }
}

void AMaster_Gun::StopGunFire_Implementation()
{
  bOnCooldown = true;
}

void AMaster_Gun::SpawnLaserBeam(FVector StartLocation, FVector EndLocation)
{
  AGunBeamEffectBase* Effect = GetWorld()->SpawnActor<AGunBeamEffectBase>(BeamEffectToUse, StartLocation, FRotator(0));
  Effect->SetupBeam(StartLocation, EndLocation, BeamDespawnDelay, BeamColor, BeamBrightness, BeamExponent);
}

void AMaster_Gun::OnInteract_Implementation()
{
  SetupInput();
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

void AMaster_Gun::SetupInput()
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

void AMaster_Gun::DisableGunInput()
{
  APlayerController* PC = GetWorld()->GetFirstPlayerController();

  if (PC)
  {
    this->DisableInput(PC);
  }
}

void AMaster_Gun::EnableGunInput()
{
  APlayerController* PC = GetWorld()->GetFirstPlayerController();

  if (PC)
  {
    this->EnableInput(PC);
  }
}

void AMaster_Gun::UpdateCDBar(float Playback, float Length, float CDTime)
{
  CDWidgetFront = Cast<UGunCoolDownBar>(WidgetCompFront->GetUserWidgetObject());

  if (CDWidgetFront)
  {
    CDWidgetFront->UpdatePercent(Playback, Length, CDTime);

    CDWidgetBack = Cast<UGunCoolDownBar>(WidgetCompBack->GetUserWidgetObject());

    if (CDWidgetBack)
    {
      CDWidgetBack->UpdatePercent(Playback, Length, CDTime);
    }
    else
    {
      UE_LOG(LogInventorySystem, Error, TEXT("Unable to UpdateCDBar CDWidgetBack was not valid"))
    }
  }
  else
  {
    UE_LOG(LogInventorySystem, Error, TEXT("Unable to UpdateCDBar CDWidgetFront was not valid"))
  }
}

void AMaster_Gun::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    AMaster_Magnet* Magnet = Cast<AMaster_Magnet>(OtherActor);
    AMasterDamageEffect* DamageEffect = Cast<AMasterDamageEffect>(OtherActor);

    if (!Magnet && !DamageEffect)
    {
      bCanFireTrace = false;
    }
  }
}

void AMaster_Gun::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  if (OtherActor)
  {
    AMaster_Magnet* Magnet = Cast<AMaster_Magnet>(OtherActor);
    AMasterDamageEffect* DamageEffect = Cast<AMasterDamageEffect>(OtherActor);

    if (!Magnet && !DamageEffect)
    {
      bCanFireTrace = true;
    }
  }
}

FRotator AMaster_Gun::GetMouseRotation()
{
  APaperWarden* LocalPlayer = GetPlayerRef();

  if (LocalPlayer)
  {
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    if (PC)
    {
      FVector MouseWorldLocation;
      FVector MouseWorldDirection;

      if (PC->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection))
      {
        FVector CurrentCameraLocation = LocalPlayer->CameraComp->GetComponentLocation();

        float RotX = MouseWorldLocation.X - CurrentCameraLocation.X;
        float RotZ = MouseWorldLocation.Z - CurrentCameraLocation.Z;

        float NewPitch = UKismetMathLibrary::DegAtan2(RotZ, RotX);

        return FRotator(NewPitch, 0, 0);
      }
      else
      {
        return FRotator(0);
      }
    }
    else
    {
      UE_LOG(LogInventorySystem, Error, TEXT("Unable to GetMouseRotation Player Controller is not valid"))
      return FRotator(0);
    }
  }
  else
  {
    UE_LOG(LogInventorySystem, Error, TEXT("Unable to GetMouseRotation Player is not valid"))
    return FRotator(0);
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

const bool AMaster_Gun::GetCanFireTrace()
{
  return bCanFireTrace;
}

const FVector AMaster_Gun::GetTraceStart()
{
  return TraceStart;
}

const FVector AMaster_Gun::GetTraceEnd()
{
  return TraceEnd;
}

UGunCoolDownBar* AMaster_Gun::GetFrontCDWidget()
{
  return CDWidgetFront;
}

UGunCoolDownBar* AMaster_Gun::GetBackCDWidget()
{
  return CDWidgetBack;
}
