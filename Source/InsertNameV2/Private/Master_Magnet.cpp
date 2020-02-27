// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Magnet.h"
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
	PrimaryActorTick.bCanEverTick = false;

  GravityStrength = 30.0f;
  bActive = true;

  OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereCollision"));
  RootComponent = OuterSphereComp;
  OuterSphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  OuterSphereComp->SetCollisionResponseToChannel(ECC_GameTraceChannel12, ECollisionResponse::ECR_Ignore);
  OuterSphereComp->SetCollisionObjectType(ECC_GameTraceChannel15);

  CurrentSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  CurrentSprite->SetupAttachment(RootComponent);
  CurrentSprite->SetCollisionResponseToAllChannels(ECR_Ignore);
  CurrentSprite->SetCollisionResponseToChannel(ECC_GameTraceChannel13, ECR_Block);
  CurrentSprite->SetCollisionResponseToChannel(ECC_GameTraceChannel17, ECR_Block);
  CurrentSprite->SetCollisionResponseToChannel(ECC_GameTraceChannel18, ECR_Block);
}

// Called when the game starts or when spawned
void AMaster_Magnet::BeginPlay()
{
	Super::BeginPlay();

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
  CurrentSprite->OnComponentHit.AddDynamic(this, &AMaster_Magnet::OnSpriteHit);
}

void AMaster_Magnet::Activate()
{
  bActive = true;

  UpdateSprite(ActiveSprite);

  // Create pull timer
  GetWorldTimerManager().SetTimer(PullTimer, this, &AMaster_Magnet::PullPlayer, 0.01f, true);
}

void AMaster_Magnet::Deactivate()
{
  bActive = false;

  UpdateSprite(DeactivatedSprite);

  StopTimer();

  OnPullStop();
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
  }
  else
  {
    UE_LOG(LogGameplaySystem, Error, TEXT("Unable to pull player PlayerRef is not valid"))
    OnPullStop();
  }
}

void AMaster_Magnet::OnPullStop_Implementation()
{
  StopTimer();
}

void AMaster_Magnet::StopTimer()
{
  GetWorldTimerManager().ClearTimer(PullTimer);
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
      OnPullStop();
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
      Deactivate();
    }
  }
}

void AMaster_Magnet::UpdateSprite(UPaperSprite* Sprite)
{
  CurrentSprite->SetSprite(Sprite);
}
