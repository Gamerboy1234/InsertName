// Fill out your copyright notice in the Description page of Project Settings.


#include "E_Charger.h"
#include "Curves/CurveFloat.h"
#include "GeneralFunctions.h"
#include "CollisionQueryParams.h"
#include "AI/NavigationSystemBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include "Master_AIController.h"
#include "AI/NavigationSystemBase.h"
#include "PaperFlipbookComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "InsertNameV2.h"
#include "PaperWarden.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"

AE_Charger::AE_Charger()
{
  bStopChargeOnPlayerOverlap = true;
  bDefaultToPlayer = true;

  static ConstructorHelpers::FObjectFinder<UCurveFloat> ChargerCurve(TEXT("/Game/2DPlatformingKit/Blueprints/Player/MouseCurve"));
  check(ChargerCurve.Succeeded());

  ChargerFloat = ChargerCurve.Object;

  static ConstructorHelpers::FObjectFinder<UCurveFloat> MovementCurve(TEXT("/Game/2DPlatformingKit/Blueprints/Player/MouseCurve"));
  check(ChargerCurve.Succeeded());

  MovementFloat = MovementCurve.Object;

  ChargeSpeedMultiplier = 2.0f;
  WanderRadius = 500.0f;
  WaitDelay = 2.0f;
}

void AE_Charger::BeginPlay()
{
  Super::BeginPlay();

  bAggro = false;
  bOnDelay = false;

  // Setup timeline
  if (ChargerFloat)
  {
    FOnTimelineFloat TimelineProgress;
    TimelineProgress.BindUFunction(this, FName("ChargerMovmentState"));
    ChargerTimeline.AddInterpFloat(ChargerFloat, TimelineProgress);
    ChargerTimeline.SetLooping(true);
    ChargerTimeline.SetPlayRate(5.0f);
    ChargerTimeline.PlayFromStart();
  }

  if (MovementFloat)
  {
    FOnTimelineFloat TimelineProgress;
    FOnTimelineEventStatic onTimelineFinishedCallback;
    TimelineProgress.BindUFunction(this, FName("ChargeToTarget"));
    onTimelineFinishedCallback.BindUFunction(this, FName("OnChargeFinish"));
    MovementTimeline.SetTimelineFinishedFunc(onTimelineFinishedCallback);
    MovementTimeline.AddInterpFloat(ChargerFloat, TimelineProgress);
    MovementTimeline.SetLooping(false);
    MovementTimeline.SetPlayRate(1.0f);
  }
}

void AE_Charger::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);

  ChargerTimeline.TickTimeline(DeltaSeconds);

  MovementTimeline.TickTimeline(DeltaSeconds);
}

void AE_Charger::ChargerMovmentState(float Value)
{
  bAggro = CheckAggro();

  if (bAggro)
  {
    StartCharge();
  }
  else
  {
    MoveToRandomPoint();
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
    RotateToPoint(TargetActor);
  }
  else
  {
    APaperWarden* PlayerRef = UGeneralFunctions::GetPlayer(this);

    if (PlayerRef)
    {
      RotateToPoint(PlayerRef);
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

void AE_Charger::RotateToPoint(FVector Location)
{
  FVector Direction = UGeneralFunctions::GetUnitVector(GetActorLocation(), Location);

  if (UGeneralFunctions::IsNumberNegative(Direction.X))
  {
    SetActorRotation(FRotator(0, 180, 0));
  }
  else
  {
    SetActorRotation(FRotator(0));
  }
}

void AE_Charger::RotateToPoint(AActor* ActorToRotateTo)
{
  if (ActorToRotateTo)
  {
    FVector Direction = UGeneralFunctions::GetUnitVector(GetActorLocation(), ActorToRotateTo->GetActorLocation());

    if (UGeneralFunctions::IsNumberNegative(Direction.X))
    {
      SetActorRotation(FRotator(0, 180, 0));
    }
    else
    {
      SetActorRotation(FRotator(0));
    }
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Failed to RotateToPoint ActorToRotateTo was not valid"))
  }
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
  if (!bOnDelay)
  {
    if (MovementFloat)
    {
      if (!bIsTimelinePlaying)
      {
        UpdateMovement();
        IncreaseSpeed(ChargeSpeedMultiplier);
        MovementTimeline.PlayFromStart();
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

void AE_Charger::MoveToRandomPoint()
{
  bool bGotLocation = false;

  if (!bOnDelay)
  {
    if (!bGotLocation)
    {
      AMaster_AIController* LocalController = Cast<AMaster_AIController>(GetController());

      if (LocalController)
      { 
        if (GetRandomPoint(WanderRadius, TargetLocation))
        {
          RotateToPoint(TargetLocation);
          TargetLocation.Y = 0;
        }
        else
        {
          UE_LOG(LogMasterEnemy, Error, TEXT("Failed to get Random location"))
          return;
        }

        LocalController->MoveToLocation(TargetLocation);
        bGotLocation = true;
        CreateDelay(WaitDelay);
      }
      else
      {
        UE_LOG(LogMasterEnemy, Error, TEXT("Failed to MoveToRandomPoint Controller was not valid"))
        return;
      }
    }
  }
}

bool AE_Charger::GetRandomPoint(float RandomPointDeviation, FVector& OutResult)
{
  UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

  if (NavSystem)
  {
    FNavLocation Result;
    bool bSuccess = NavSystem->GetRandomReachablePointInRadius(GetActorLocation(), RandomPointDeviation, Result);
    OutResult = Result;
    return bSuccess;
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Failed to GetRandomPoint NavSystem was not valid"))
    return false;
  }
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

bool AE_Charger::CheckAggro()
{
  return true;
}

const bool AE_Charger::GetAggro()
{
  return bAggro;
}
