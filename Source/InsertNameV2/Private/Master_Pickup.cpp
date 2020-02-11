// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Pickup.h"
#include "PaperSpriteComponent.h"
#include "Engine/Texture2D.h"
#include "Components/BoxComponent.h"
#include "GeneralFunctions.h"
#include "PaperWarden.h"

// Sets default values
AMaster_Pickup::AMaster_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  RootComponent = PaperSprite;

  BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
  if (!ensure(BoxTrigger != nullptr)) { return; }
  BoxTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMaster_Pickup::BeginPlay()
{
	Super::BeginPlay();

  ID = UGeneralFunctions::GetIDFromGamemode(this, this);

  BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMaster_Pickup::OnOverlapBegin);
}

void AMaster_Pickup::OnInteract_Implementation()
{
  DestroyPickUp(this);
}

void AMaster_Pickup::DestroyPickUp(AMaster_Pickup* PickupToDestroy)
{
  UGeneralFunctions::RemoveIDFromGamemode(PickupToDestroy, PickupToDestroy->ID, PickupToDestroy);
  PickupToDestroy->Destroy();
}

void AMaster_Pickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    auto PlayerRef = Cast<APaperWarden>(OtherActor);
    if (PlayerRef)
    {
      PlayerRef->PickedUpItem(ItemInfo.Icon);
      OnInteract();
    }
  }
}

const int32 AMaster_Pickup::GetID()
{
  return ID;
}
