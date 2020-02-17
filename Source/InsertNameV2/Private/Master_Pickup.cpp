// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Pickup.h"
#include "PaperSpriteComponent.h"
#include "Engine/Texture2D.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GeneralFunctions.h"
#include "PaperWarden.h"

// Sets default values
AMaster_Pickup::AMaster_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  MaxItemAmount = 99;
  AmountAtIndex = 1;
  UPROPERTY(VisibleAnywhere, Category = "Components")

  BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
  if (!ensure(BoxTrigger != nullptr)) { return; }
  RootComponent = BoxTrigger;

  Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ItemSprite"));
  Sprite->SetupAttachment(BoxTrigger);
}

// Called when the game starts or when spawned
void AMaster_Pickup::BeginPlay()
{
	Super::BeginPlay();

  ID = UGeneralFunctions::GetIDFromGamemode(this, this);

  PlayerRef = Cast<APaperWarden>(UGameplayStatics::GetPlayerCharacter(this, 0));

  BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMaster_Pickup::OnOverlapBegin);
}

void AMaster_Pickup::OnInteract_Implementation()
{
  if (PlayerRef)
  {
    bool bAddToInventory = PlayerRef->AddItem(this, ItemInfo.Amount, true);
    if (bAddToInventory)
    {
      if (bAddedToStack)
      {
        this->DestroyPickup();
      }
      else
      {
        this->ShowPickup(false);
      }
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Unable to add item to inventory player is not valid"))
  }
}

void AMaster_Pickup::ShowPickup(bool Show)
{
  ECollisionEnabled::Type Collision = Show ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;

  this->SetActorHiddenInGame(Show);

  this->BoxTrigger->SetCollisionEnabled(Collision);
}

void AMaster_Pickup::AddToStack()
{
  AmountAtIndex += ItemInfo.Amount;
}

void AMaster_Pickup::UseItem_Implementation()
{
  UE_LOG(LogTemp, Log, TEXT("Item %s has no Implementation"), *this->ConvertItemNameToString())
}

void AMaster_Pickup::DestroyPickup()
{
  UGeneralFunctions::RemoveIDFromGamemode(this, this->ID, this);
  this->Destroy();
}

void AMaster_Pickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    if (OtherActor && PlayerRef)
    {
      if (OtherActor == PlayerRef)
      {
        PlayerRef->PickedUpItem(ItemInfo.Icon);
        OnInteract();
      }
    }
  }
}

FString AMaster_Pickup::ConvertItemNameToString()
{
  return this->ItemInfo.ItemName.ToString();
}

const int32 AMaster_Pickup::GetID()
{
  return ID;
}
