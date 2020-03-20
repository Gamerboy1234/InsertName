// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_PressurePlate.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Master_Moveable_Platform.h"
#include "PaperWarden.h"

// Sets default values
AMaster_PressurePlate::AMaster_PressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
  RootComponent = BoxTrigger;

  SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  SpriteComp->SetupAttachment(RootComponent);
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
    APaperWarden* Player = Cast<APaperWarden>(OtherActor);

    if (Player)
    {
      // TODO Call platform code here
      UE_LOG(LogTemp, Log, TEXT("Test"))
    }
  }
}
