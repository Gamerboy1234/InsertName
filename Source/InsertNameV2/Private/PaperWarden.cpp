// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperWarden.h"
#include "Master_Pickup.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

APaperWarden::APaperWarden()
{
  PrimaryActorTick.bCanEverTick = true;

  BarkInnerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Bark Inner Collision"));
  BarkInnerCollision->SetupAttachment(RootComponent);
  BarkOuterCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Bark Outer Collision"));
  BarkOuterCollision->SetupAttachment(RootComponent);
}

void APaperWarden::BeginPlay()
{
  Super::BeginPlay();

  BarkInnerCollision->OnComponentBeginOverlap.AddDynamic(this, &APaperWarden::OnOverlapBegin);
  BarkOuterCollision->OnComponentBeginOverlap.AddDynamic(this, &APaperWarden::BeginOverlap);
}

int32 APaperWarden::AddToKillCount(int32 AmountToadd)
{
  return KillCount += AmountToadd;
}

const int32 APaperWarden::GetCurrentKillCount()
{
  return KillCount;
}

void APaperWarden::LoadKillCount(int32 KillCountToLoad)
{
  KillCount = KillCountToLoad;
}

void APaperWarden::PickedUpItem_Implementation(class UTexture2D* PickUpTexture)
{
  UE_LOG(LogTemp, Warning, TEXT("Player Pickup event has no Implementation"))
}

void APaperWarden::HealPlayer_Implementation(float HealAmount)
{
  UE_LOG(LogTemp, Warning, TEXT("Player Heal event has no Implementation"))
}

void APaperWarden::KillPlayer_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("Kill Player event has no Implementation"))
}

void APaperWarden::UpgradeHP_Implementation(float UpgradeAmount, float NewMaxHP)
{
  UE_LOG(LogTemp, Warning, TEXT("Upgrade HP event has no Implementation"))
}

void APaperWarden::Damage_Implementation(float DamageAmount, bool bShowCombatText, AActor* DamageInstigator)
{
  UE_LOG(LogTemp, Warning, TEXT("Damage event has no Implementation"))
}

void APaperWarden::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    OnBarkInnerOverlap(OtherActor);
  }
}

void APaperWarden::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (OtherActor)
  {
    OnBarkOuterOverlap(OtherActor);
  }
}

void APaperWarden::AddToInventory(AMaster_Pickup* ItemToAdd)
{
  InventoryItems.Add(ItemToAdd);
  UpdateInventory();
}

void APaperWarden::DropItemsOnActionBar(class AMaster_Pickup* Pickup, int32 MaxItems)
{
  // See if hot bar is full
  if (ActionBarItems.Num() == MaxItems)
  {
    return;
  }
  else
  {
    InventoryItems.Remove(Pickup);
    ActionBarItems.Add(Pickup);

    OnUpdateActionBar.Broadcast(ActionBarItems);
  }
}

void APaperWarden::UpdateInventory()
{
  OnUpdateInventory.Broadcast(InventoryItems);
}

void APaperWarden::PrintInventory()
{
  FString sInventory = "";

  for (AMaster_Pickup* actor : InventoryItems)
  {
    sInventory.Append(actor->GetName());
    sInventory.Append(" | ");
  }

  GEngine->AddOnScreenDebugMessage(1, 3, FColor::Blue, *sInventory);
}

const TArray<AMaster_Pickup*> APaperWarden::GetPlayerInventory()
{
  return InventoryItems;
}

const TArray<AMaster_Pickup*> APaperWarden::GetActionBarItems()
{
  return ActionBarItems;
}
