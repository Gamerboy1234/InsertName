// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PaperWarden.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateInventoryDelegate, const TArray<AMaster_Pickup*>&, InventoryItems);

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API APaperWarden : public APaperZDCharacter
{
	GENERATED_BODY()

public:

  APaperWarden();

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UBoxComponent* BarkInnerCollision;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UBoxComponent* BarkOuterCollision;

  UPROPERTY(BlueprintReadWrite, Category = "Spells")
  bool bWasBarkUsed;

  UPROPERTY(BlueprintReadWrite, Category = "Spells")
  bool bFlameMagnetActive;

  UFUNCTION(BlueprintCallable, Category = "Utility")
  int32 AddToKillCount(int32 AmountToadd);
  /* Returns the amount of enemies the player has killed */
  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const int32 GetCurrentKillCount();

  UFUNCTION(BlueprintCallable, Category = "Utility")
  void LoadKillCount(int32 KillCountToLoad);
  /* Event for controller bark spells inner collision setup */
  UFUNCTION(BlueprintImplementableEvent, Category = "Utility")
  void OnBarkInnerOverlap(AActor* OverlappedActor);

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Utility")
  void OnBarkOuterOverlap(AActor* OverlappedActor);
  /* Display a pop up icon when player picks up an item */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player Events")
  void PickedUpItem(class UTexture2D* PickUpTexture);
  virtual void PickedUpItem_Implementation(class UTexture2D* PickUpTexture);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player Events")
  void HealPlayer(float HealAmount);
  virtual void HealPlayer_Implementation(float HealAmount);
  /* Will kill the player instantly */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player Events")
  void KillPlayer();
  virtual void KillPlayer_Implementation();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player Events")
  void UpgradeHP(float NewCurrentHP, float NewMaxHP);
  virtual void UpgradeHP_Implementation(float NewCurrentHP, float NewMaxHP);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player Events")
  void Damage(float DamageAmount, bool bShowCombatText, AActor* DamageInstigator);
  virtual void Damage_Implementation(float DamageAmount, bool bShowCombatText, AActor* DamageInstigator);

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  UFUNCTION()
  void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
  /* Will add the given item to player's inventory */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool AddItem(AMaster_Pickup* ItemToAdd, int32 Amount);
  /* Will try and find given item in inventory and remove it */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool RemoveItemFromInventory(AMaster_Pickup* ItemToRemove, int32 Amount);
  /* Inventory Debug Function prints out all current inventory items */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void PrintInventory();
  /* Swap items at a given index */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void SwapItems(AMaster_Pickup* ItemOne, AMaster_Pickup* ItemTwo);
  /* Returns all items in player's inventory */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  const TArray<class AMaster_Pickup*> GetPlayerInventory();
  /* Gets all items on action bar */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  const TArray<class AMaster_Pickup*> GetActionBarItems();
  /* Places dropped item on action bar and updates ActionBarItems array */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void DropItemsOnActionBar(class AMaster_Pickup* Pickup, int32 MaxItems);
  /* Sends updates to Inventory widget UI */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void UpdateInventory();
  /* Checks to see if inventoryItems array is >= to AmountofInventorySlots */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool IsInventoryFull();
  /* Find item in array by Name */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  class AMaster_Pickup* FindItemByName(AMaster_Pickup* ItemToFind);
  /* Delegate that fires off every time the inventory is updated */
  UPROPERTY(BlueprintAssignable, Category = "Inventory")
  FUpdateInventoryDelegate OnUpdateInventory;
  /* Delegate that fires off every time the actionbar is updated */
  UPROPERTY(BlueprintAssignable, Category = "Inventory")
  FUpdateInventoryDelegate OnUpdateActionBar;
  /* Amount of inventory slots in inventory menu */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InventorySettings")
  int32 AmountofInventorySlots;
  /* If item can stack then this searches for a free stack to add items to */
  AMaster_Pickup* SearchForFreeStack(AMaster_Pickup* ItemClass);
  /* Looks for an empty slot in the inventory to place new item */
  int32 FindEmptySlot();

  UFUNCTION()
  void RestDropItemCollision();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:

  FTimerHandle CollisionReset;

  int32 KillCount;

  AMaster_Pickup* ItemToRest;

  bool bFoundSlot;

  /* Will try to find item in inventory items array */
  int32 FindArrayIndex(AMaster_Pickup* ItemToFind);

  TArray<class AMaster_Pickup*> InventoryItems;

  TArray<class AMaster_Pickup*> ActionBarItems;
};
