// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Magnet.h"
#include "Components/SphereComponent.h"
#include "GeneralFunctions.h"
#include "PaperWarden.h"
#include "TimerManager.h"
#include "InsertNameV2.h"
#include "PaperSpriteComponent.h"

// Sets default values
AMaster_Magnet::AMaster_Magnet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  GravityStrength = 20.0f;
  bActive = true;

  SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
  RootComponent = SphereComp;

  CurrentSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  CurrentSprite->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMaster_Magnet::BeginPlay()
{
	Super::BeginPlay();

  if (bActive)
  {
    CurrentSprite = ActiveSprite;
  }
  else
  {
    CurrentSprite = DeactivatedSprite;
  }

  SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMaster_Magnet::OnOverlapBegin);
  SphereComp->OnComponentEndOverlap.AddDynamic(this, &AMaster_Magnet::OnOverlapEnd);
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

}

void AMaster_Magnet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AMaster_Magnet::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void AMaster_Magnet::UpdateSprite(UPaperSpriteComponent* Sprite)
{
  CurrentSprite = Sprite;
}
