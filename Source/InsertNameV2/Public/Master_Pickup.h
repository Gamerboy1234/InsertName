// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "Master_Pickup.generated.h"

UCLASS()
class INSERTNAMEV2_API AMaster_Pickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_Pickup();

  bool bAddedToStack;

  bool bInInventory;

  UPROPERTY(BlueprintReadOnly, Category = "ItemInfo")
  int32 AmountAtIndex;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInfo")
  int32 MaxItemAmount;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UPaperSpriteComponent* Sprite;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UBoxComponent* BoxTrigger;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FItemData ItemInfo;
  /* Called when player overlaps box trigger by default it will add the given pickup to the player's inventory */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Events")
  void OnInteract();
  virtual void OnInteract_Implementation();
  /* Will hide pickup and disable collision or show picked and enable collision base on show bool */
  UFUNCTION(BlueprintCallable, Category = "Pickup Functions")
  void ShowPickup(bool Show);
  /* Add to CurrentItemAmount */
  UFUNCTION(BlueprintCallable, Category = "Pickup Functions")
  void AddToStack(int32 AmountToAdd);
  /* This event is called to make the item actually do things */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory Events")
  void UseItem();
  virtual void UseItem_Implementation();

  UFUNCTION(BlueprintCallable, Category = "Pickup Functions")
  void DestroyPickup();

  UFUNCTION(BlueprintPure, Category = "Pickup Functions")
  const int32 GetID();

  UFUNCTION()
  virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  FString ConvertItemNameToString();

  /* Reads the value of PlayerRef */
  UFUNCTION(BlueprintPure, Category = "Pickup Functions")
  class APaperWarden* GetPlayerRef();

private:

  int32 ID;

  class APaperWarden* PlayerRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
