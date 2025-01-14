// Fill out your copyright notice in the Description page of Project Settings.


#include "E_Charger.h"
#include "Curves/CurveFloat.h"
#include "GeneralFunctions.h"
#include "CollisionQueryParams.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "AggroComponent.h"
#include "WanderComponent.h"
#include "PaperFlipbookComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "InsertNameV2.h"
#include "PaperWarden.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"

AE_Charger::AE_Charger()
{
  bDefaultToPlayer = true;

  HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
  HitBox->SetupAttachment(RootComponent);

  if (!ensure(HitBox != nullptr)) { return; }

  AggroComp = CreateDefaultSubobject<UAggroComponent>(TEXT("Aggro Comp"));

  if (!ensure(AggroComp != nullptr)) { return; }

  WanderComp = CreateDefaultSubobject<UWanderComponent>(TEXT("Wander Comp"));

  if (!ensure(WanderComp != nullptr)) { return; }

  static ConstructorHelpers::FObjectFinder<UCurveFloat> StateCurve(TEXT("/Game/2DPlatformingKit/Blueprints/Player/MouseCurve"));
  check(StateCurve.Succeeded());

  StateFloat = StateCurve.Object;

  static ConstructorHelpers::FObjectFinder<UCurveFloat> ChargeCurve(TEXT("/Game/2DPlatformingKit/Blueprints/Player/MouseCurve"));
  check(ChargeCurve.Succeeded());

  ChargerFloat = ChargeCurve.Object;

  ChargeSpeedMultiplier = 3.0f;
  ChargeDelay = 2.0f;
  ChargeTime = 2.0f;
  TraceRange = 1000;
  KnockBackMultipler = 100;
}

void AE_Charger::BeginPlay()
{
  Super::BeginPlay();

  HitBox->OnComponentBeginOverlap.AddDynamic(this, &AE_Charger::OnOverlapBegin);

  bOnDelay = false;
  bSetupFirstCharge = true;

  // Create movement state timeline
  if (StateFloat)
  {
    FOnTimelineFloat TimelineProgress;
    TimelineProgress.BindUFunction(this, FName("ChargerMovmentState"));
    MovementStateTimline.AddInterpFloat(StateFloat, TimelineProgress);
    MovementStateTimline.SetLooping(true);
    MovementStateTimline.SetPlayRate(1.0f);
    MovementStateTimline.PlayFromStart();
  }
  // Create charge timeline
  if (ChargerFloat)
  {
    FOnTimelineFloat TimelineProgress;
    FOnTimelineEventStatic onTimelineFinishedCallback;
    TimelineProgress.BindUFunction(this, FName("ChargeToTarget"));
    onTimelineFinishedCallback.BindUFunction(this, FName("OnChargeFinish"));
    ChargeTimeline.SetTimelineFinishedFunc(onTimelineFinishedCallback);
    ChargeTimeline.AddInterpFloat(StateFloat, TimelineProgress);
    ChargeTimeline.SetTimelineLength(ChargeTime);
    ChargeTimeline.SetLooping(false);
    ChargeTimeline.SetPlayRate(1.0f);
  }
}

void AE_Charger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    APaperWarden* PlayerRef = Cast<APaperWarden>(OtherActor);

    if (PlayerRef)
    {
      if (!bOnDelay)
      {
        UGeneralFunctions::LaunchCharacterAwayFromActor(PlayerRef, this, KnockBackMultipler);

        PlayerRef->Damage(DamageToPlayer, true, this);

        CreateDelay(ChargeTime);
      }
    }
  }
}

void AE_Charger::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);

  MovementStateTimline.TickTimeline(DeltaSeconds);

  ChargeTimeline.TickTimeline(DeltaSeconds);
}

AActor* AE_Charger::GetCurrentTarget()
{
  if (!bDefaultToPlayer)
  {
    if (TargetActor)
    {
      return TargetActor;
    }
    else
    {
      UE_LOG(LogMasterEnemy, Error, TEXT("Failed to GetCurrentTarget TargetActor was not valid"))
      return nullptr;
    }
  }
  else
  {
    APaperWarden* Player = UGeneralFunctions::GetPlayer(this);

    if (Player)
    {
      return Player;
    }
    else
    {
      UE_LOG(LogMasterEnemy, Error, TEXT("Failed to GetCurrentTarget Player was not valid"))
      return nullptr;
    }
  }
}

void AE_Charger::ChargerMovmentState(float Value)
{
  if (AggroComp->GetAggro())
  {
    StartCharge();
  }
  else
  {
    WanderComp->SetInUse(true);
    WanderComp->MoveOwnerToRandomPoint();
  }
}

void AE_Charger::UpdateMovement()
{
  TargetDirection = GetDirection();
  TargetLocation = GetLocation();
}

void AE_Charger::FindTargetRotation()
{
  if (!bDefaultToPlayer)
  {
    UGeneralFunctions::RotateActorToActorLocation(this, TargetActor);
  }
  else
  {
    APaperWarden* PlayerRef = UGeneralFunctions::GetPlayer(this);

    if (PlayerRef)
    {
      UGeneralFunctions::RotateActorToActorLocation(this, PlayerRef);
    }
    else
    {
      UE_LOG(LogMasterEnemy, Error, TEXT("Failed to RotateToPoint PlayerRef was not valid"))
      return;
    }
  }

  TargetLocation = GetLocation();
  TargetDirection = GetDirection();
}

FVector AE_Charger::GetDirection()
{
  FVector TraceStart = GetActorLocation();
  FVector TraceEnd = TraceRange * GetActorForwardVector() + TraceStart;

  FHitResult OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldStatic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldDynamic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel13);

  FCollisionQueryParams CollisionParms;
  CollisionParms.AddIgnoredActor(this);

  APaperWarden* PlayerRef = UGeneralFunctions::GetPlayer(this);

  if (PlayerRef)
  {
    if (PlayerRef->bDebugEnemyCharge)
    {
      DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2);
    }
  }

  if (GetWorld()->LineTraceSingleByObjectType(OutHit, TraceStart, TraceEnd, ObjectsToTest, CollisionParms))
  {
    if (OutHit.bBlockingHit)
    {
      return UGeneralFunctions::GetUnitVector(GetActorLocation(), OutHit.ImpactPoint);
    }
    else
    {
      return UGeneralFunctions::GetUnitVector(GetActorLocation(), OutHit.TraceEnd);
    }
  }
  else
  {
    return UGeneralFunctions::GetUnitVector(GetActorLocation(), TraceEnd);
  }
}

FVector AE_Charger::GetLocation()
{
  StartLocation = GetActorLocation();
  FVector TraceEnd = TraceRange * GetActorForwardVector() + StartLocation;

  FHitResult OutHit;
  FCollisionObjectQueryParams ObjectsToTest;
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldStatic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_WorldDynamic);
  ObjectsToTest.AddObjectTypesToQuery(ECC_GameTraceChannel13);

  FCollisionQueryParams CollisionParms;
  CollisionParms.AddIgnoredActor(this);

  APaperWarden* PlayerRef = UGeneralFunctions::GetPlayer(this);

  if (PlayerRef)
  {
    if (PlayerRef->bDebugEnemyCharge)
    {
      DrawDebugLine(GetWorld(), StartLocation, TraceEnd, FColor::Red, false, 2);
    }
  }

  if (GetWorld()->LineTraceSingleByObjectType(OutHit, StartLocation, TraceEnd, ObjectsToTest, CollisionParms))
  {
    if (OutHit.bBlockingHit)
    {
      return OutHit.ImpactPoint;
    }
    else
    {
      return OutHit.TraceEnd;
    }
  }
  else
  {
    return TraceEnd;
  }
}

void AE_Charger::StartCharge()
{
  if (ChargerFloat)
  {
    if (!bIsTimelinePlaying)
    {
      if (bSetupFirstCharge)
      {
        bSetupFirstCharge = false;
        WanderComp->SetInUse(false);
        CreateDelay(ChargeDelay, true);
      }
      if (!bOnDelay)
      {
        UpdateMovement();
        IncreaseSpeed(ChargeSpeedMultiplier);
        ChargeTimeline.PlayFromStart();
      }
    }
  }
}

void AE_Charger::ChargeToTarget(float Value)
{
  bIsTimelinePlaying = true;
  
  ResetSpriteColor();

  FVector ChargeLocation = FMath::VInterpNormalRotationTo(StartLocation, TargetLocation, Value, ChargeSpeedMultiplier);
  ChargeLocation.Y = 0;

  TargetDirection = UGeneralFunctions::GetUnitVector(StartLocation, ChargeLocation);
  TargetDirection.Y = 0;

  AddMovementInput(TargetDirection);
}

void AE_Charger::OnChargeFinish()
{
  bIsTimelinePlaying = false;

  GetCharacterMovement()->StopActiveMovement();

  ResetSpeed();
  
  ResetSpriteColor();

  CreateDelay(ChargeDelay, true);
}

void AE_Charger::CreateDelay(float Delay)
{
  FTimerHandle DelayTimer;

  bOnDelay = true;

  GetWorldTimerManager().SetTimer(DelayTimer, this, &AE_Charger::OnDelayEnd, Delay, false);
}

void AE_Charger::CreateDelay(float Delay, bool UpdateRotation)
{
  FTimerHandle DelayTimer;

  if (UpdateRotation)
  {
    FindTargetRotation();
    GetSprite()->SetSpriteColor(FLinearColor::Green);
  }

  bOnDelay = true;

  GetWorldTimerManager().SetTimer(DelayTimer, this, &AE_Charger::OnDelayEnd, Delay, false);
}

void AE_Charger::OnDelayEnd()
{
  bOnDelay = false;
}
