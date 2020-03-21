// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_PressurePlate.h"
#include "Master_MoveablePlatform.h"
#include "PaperWarden.h"
#include "InsertNameV2.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMaster_PressurePlate::AMaster_PressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  RootComponent = SpriteComp;

  BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
  BoxTrigger->SetupAttachment(RootComponent);

  bOneShot = true;
}

// Called when the game starts or when spawned
void AMaster_PressurePlate::BeginPlay()
{
	Super::BeginPlay();

  BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMaster_PressurePlate::OnOverlapBegin);
}

void AMaster_PressurePlate::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    if (!bAlreadyUsed)
    {
      APaperWarden* Player = Cast<APaperWarden>(OtherActor);

      if (Player)
      {
        if (CurrentPlatform)
        {
          CurrentPlatform->SetCanMove(true);

          bAlreadyUsed = (bOneShot) ? true : false;
        }
        else
        {
          UE_LOG(LogGameplaySystem, Error, TEXT("%s is unable to move platform, CurrentPlatform is not set"), *this->GetName())
        }
      }
    }
  }
}
