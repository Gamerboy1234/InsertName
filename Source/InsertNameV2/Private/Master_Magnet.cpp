// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Magnet.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SphereComponent.h"
#include "GeneralFunctions.h"
#include "PaperWarden.h"
#include "TimerManager.h"
#include "PaperSprite.h"
#include "InsertNameV2.h"
#include "PaperSpriteComponent.h"

// Sets default values
AMaster_Magnet::AMaster_Magnet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  GravityStrength = 30.0f;
  bActive = true;
  AccelerationMultiplyer = 20.0f;
  AccelerationCap = 2000.0f;
  AccelerationDelay = 1.0f;

  OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereCollision"));
  RootComponent = OuterSphereComp;
  OuterSphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  OuterSphereComp->SetCollisionResponseToChannel(ECC_GameTraceChannel12, ECollisionResponse::ECR_Ignore);
  OuterSphereComp->SetCollisionObjectType(ECC_GameTraceChannel15);

  CurrentSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  CurrentSprite->SetupAttachment(RootComponent);
  CurrentSprite->SetCollisionResponseToAllChannels(ECR_Ignore);

  InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereCollision"));
  InnerSphereComp->SetupAttachment(RootComponent);
  InnerSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
  InnerSphereComp->SetCollisionResponseToChannel(ECC_GameTraceChannel14, ECR_Block);
  InnerSphereComp->SetCollisionResponseToChannel(ECC_GameTraceChannel17, ECR_Block);
  InnerSphereComp->SetCollisionResponseToChannel(ECC_GameTraceChannel18, ECR_Block);

  // Setup Timeline curve
  static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/2DPlatformingKit/Blueprints/Player/MouseCurve"));
  check(Curve.Succeeded());

  CurveFloat = Curve.Object;
}

// Called when the game starts or when spawned
void AMaster_Magnet::BeginPlay()
{
	Super::BeginPlay();

  BuiltMomentum = 10.0f;
  DefaultMomentum = BuiltMomentum;

  bBuildMomentumStarted = false;

  if (bActive)
  {
    UpdateSprite(ActiveSprite);
  }
  else
  {
    UpdateSprite(DeactivatedSprite);
  }

  OuterSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMaster_Magnet::OnOuterOverlapBegin);
  OuterSphereComp->OnComponentEndOverlap.AddDynamic(this, &AMaster_Magnet::OnOuterOverlapEnd);
  InnerSphereComp->OnComponentHit.AddDynamic(this, &AMaster_Magnet::OnInnerCompHit);
}

void AMaster_Magnet::Activate()
{
  bActive = true;

  UpdateSprite(ActiveSprite);

  // Start Pull Timeline
  if (CurveFloat)
  {
    FOnTimelineFloat PullTimelineProgress;
    PullTimelineProgress.BindUFunction(this, FName("PullTimelineProgress"));
    PullTimeline.AddInterpFloat(CurveFloat, PullTimelineProgress);
    PullTimeline.SetLooping(true);
    PullTimeline.SetPlayRate(1.0f);
    PullTimeline.PlayFromStart();
  }
}

void AMaster_Magnet::Deactivate(FVector HitLocation, bool bUseMomentum)
{
  bActive = false;

  UpdateSprite(DeactivatedSprite);

  PullTimeline.Stop();

  OnPullStop(HitLocation, bUseMomentum);
}

void AMaster_Magnet::PullPlayer()
{
  PlayerRef = UGeneralFunctions::GetPlayer(this);

  if (PlayerRef)
  {
    FVector PullDirection = UGeneralFunctions::GetUnitVector(PlayerRef->GetActorLocation(), GetActorLocation());

    PullDirection.Y = 0.0f; // Filter out Pull Y

    FVector PullVelocity = PullDirection * GravityStrength;

    PlayerRef->LaunchCharacter(PullVelocity, false, false);

    if (!bBuildMomentumStarted)
    {
      CreateMomentumTimer();

      bBuildMomentumStarted = true;
    }
  }
  else
  {
    UE_LOG(LogGameplaySystem, Error, TEXT("Unable to pull player PlayerRef is not valid"))
    OnPullStop(FVector(0), false);
  }
}

void AMaster_Magnet::BuildMomentum()
{
  PlayerRef = UGeneralFunctions::GetPlayer(this);

  if (PlayerRef)
  {
    if (PlayerRef->bMovingRight)
    {
      BuiltMomentum = FMath::Clamp<float>(BuiltMomentum * AccelerationMultiplyer, BuiltMomentum, AccelerationCap);

      UE_LOG(LogTemp, Log, TEXT("%f"), BuiltMomentum)
    }
    else if (PlayerRef->bMovingLeft)
    {
      BuiltMomentum = FMath::Clamp<float>(BuiltMomentum * AccelerationMultiplyer, BuiltMomentum, AccelerationCap);

      UE_LOG(LogTemp, Log, TEXT("%f"), BuiltMomentum)
    }
  }
}

void AMaster_Magnet::OnPullStop_Implementation(FVector HitLocation, bool bUseMomentum)
{
  StopMomentumTimer();

  PlayerRef = UGeneralFunctions::GetPlayer(this);

  if (PlayerRef)
  {
    if (bUseMomentum)
    {
      FVector LaunchDirection = UGeneralFunctions::GetUnitVector(PlayerRef->GetActorLocation(), GetActorLocation());
      LaunchDirection.Y = 0.0f;

      FVector LaunchVelocity = LaunchDirection * BuiltMomentum;

      UE_LOG(LogTemp, Log, TEXT("LaunchVelocity %s"), *LaunchVelocity.ToString())

      PlayerRef->LaunchCharacter(LaunchVelocity, false, false);
    }
  }

  ResetMomentum();
}

void AMaster_Magnet::CreateMomentumTimer()
{
  // Create pull timer
  GetWorldTimerManager().SetTimer(MomentumTimer, this, &AMaster_Magnet::BuildMomentum, AccelerationDelay, true);
}

void AMaster_Magnet::StopMomentumTimer()
{
  GetWorldTimerManager().ClearTimer(MomentumTimer);

  bBuildMomentumStarted = false;
}

void AMaster_Magnet::OnOuterOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    PlayerRef = Cast<APaperWarden>(OtherActor);

    if (PlayerRef)
    {
      Activate();
    }
  }
}

void AMaster_Magnet::OnOuterOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  if (OtherActor)
  {
    PlayerRef = Cast<APaperWarden>(OtherActor);

    if (PlayerRef)
    {
      OnPullStop(FVector(0), false);
    }
  }
}

void AMaster_Magnet::OnInnerCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  if (OtherActor)
  {
    APaperWarden* LocalPlayer = Cast<APaperWarden>(OtherActor);

    if (LocalPlayer)
    {
      if (!bMovementStopped)
      {
        bMovementStopped = true;
        LocalPlayer->GetCharacterMovement()->StopMovementImmediately();
      }
    }
  }
}

void AMaster_Magnet::OnSpriteHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  if (OtherActor)
  {
    PlayerRef = UGeneralFunctions::GetPlayer(this);

    if (OtherActor != PlayerRef)
    {
      Deactivate(FVector(0), false);
    }
  }
}

void AMaster_Magnet::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);

  PullTimeline.TickTimeline(DeltaSeconds);
}

void AMaster_Magnet::UpdateSprite(UPaperSprite* Sprite)
{
  CurrentSprite->SetSprite(Sprite);
}

const float AMaster_Magnet::GetMomentum()
{
  return BuiltMomentum;
}

void AMaster_Magnet::ResetMomentum()
{
  BuiltMomentum = DefaultMomentum;
}

void AMaster_Magnet::PullTimelineProgress(float Value)
{
  PullPlayer();
}
