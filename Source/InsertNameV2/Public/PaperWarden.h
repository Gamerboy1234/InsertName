// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PickSaveInfo.h"
#include "PickLoadInfo.h"
#include "SavedSpellInfo.h"
#include "InputCoreTypes.h"
#include "PaperWarden.generated.h"

class UBoxComponent;
class UWardenSaveGame;
class USpringArmComponent;
class UCameraComponent;

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

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent* SpringArm;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent* CameraComp;

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
  bool AddItem(AMaster_Pickup* ItemToAdd, int32 Amount, bool bDisplayItemObtained);
  /* Will try and find given item in inventory and remove it */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool RemoveItemFromInventory(AMaster_Pickup* ItemToRemove, int32 Amount, bool bDestroyPickup);
  /* Split's the item stack by a given amount */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool SplitItemStack(AMaster_Pickup* ItemToSplit, int32 Amount);
  /* Swap items at a given index */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void SwapItemsInInventory(AMaster_Pickup* ItemOne, AMaster_Pickup* ItemTwo);
  /* Returns all items in player's inventory */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  const TArray<class AMaster_Pickup*> GetPlayerInventory();
  /* Gets all items on ActionBar */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  const TArray<class AMaster_Pickup*> GetActionBarItems();
  /* Places dropped item on action bar and updates ActionBarItems array */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool DropItemsOnActionBar(class AMaster_Pickup* Pickup, int32 Index);
  /* Sends updates to Inventory widget UI */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void UpdateInventory();
  /* Sends updates to Actionbar widget UI */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void UpdateActionBar();
  /* Checks to see if inventoryItems array is >= to AmountofInventorySlots */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  bool IsInventoryFull();
  /* Checks to see if ActionBarItems array is >= to AmountOfActionBarSlots */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool IsActionBarFull();
  /* Find item in array by Name */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  class AMaster_Pickup* FindItemByName(AMaster_Pickup* ItemToFind, const TArray<AMaster_Pickup*> ArrayToUse);
  /* Delegate that fires off every time the inventory is updated */
  UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
  FUpdateInventoryDelegate OnUpdateInventory;
  /* Delegate that fires off every time the actionbar is updated */
  UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
  FUpdateInventoryDelegate OnUpdateActionBar;
  /* Amount of inventory slots in inventory menu */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InventorySettings")
  int32 AmountofInventorySlots;
  /* If item can stack then this searches for a free stack to add items to */
  AMaster_Pickup* SearchForFreeStack(AMaster_Pickup* ItemClass);
  /* Looks for an empty slot in the inventory to place new item */
  int32 FindEmptySlotInInventory();
  /* Looks for an empty slot in the Actionbar to place new item */
  int32 FindEmptySlotOnActionBar();
  /* Checks to see if a item is at given index in ArrayToUse */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  bool IsItemAtIndex(int32 Index, const TArray<AMaster_Pickup*> ArrayToUse);
  /* Will move the given index to new index in the Inventory */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool UpdateItemIndexInInventory(AMaster_Pickup* ItemToMove, int32 NewIndex);
  /* Keys to use on ActionBar */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InventorySettings")
  TArray<FKey> ActionBarKeys;
  /* Amount of ActionBarSlots per row */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InventorySettings")
  int32 ActionBarSlotsPerRow;
  /* Will move the given index to new index on the ActionBar */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool UpdateItemIndexOnActionbar(AMaster_Pickup* ItemToMove, int32 NewIndex);
  /* Swap items at a given index */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void SwapItemsOnActionbar(AMaster_Pickup* ItemOne, AMaster_Pickup* ItemTwo);
  /* Will try to find item on Actionbar and use it */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void UseItemOnActionbar(int32 ItemIndex);
  /* Will try and find given item on the Actionbar and remove it */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool RemoveItemFromActionbar(AMaster_Pickup* ItemToRemove, int32 Amount);
  /* Will look through both the Inventory array and Actionbar array to try and find the item to remove */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool RemoveItemFromPlayer(AMaster_Pickup* ItemToRemove, int32 Amount);
  /* Will find item in world by ID */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  AMaster_Pickup* FindIteminWorld(int32 ID);
  /* Will move action bar items back into the players inventory on right click */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool MoveActionbarItemsToInventory(AMaster_Pickup* ItemToMove);
  /* Will drop Actionbar item into player's inventory */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool DropActionbarItemIntoInventory(AMaster_Pickup* ItemToMove, int32 Index);
  /* Will set the given array index to given item */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  bool SetArrayIndex(int32 Index, TArray<AMaster_Pickup*> ArrayToUse, AMaster_Pickup* ItemToSet);
  /* Checks to see if two given items are the same */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  bool DupCheck(AMaster_Pickup* ItemOne, AMaster_Pickup* ItemTwo);
  /* Will try and find item's index in array will search by ID */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  int32 FindItemIndexByID(int32 ID, const TArray<AMaster_Pickup*> ArrayToUse);
  /* Equips the given gun to player */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon Functions")
  void EquipGun(AMaster_Pickup* GunToEquip, FVector Offset, FVector GunScale);
  /* Called to updated the current rotation of the mouse */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon Functions")
  void UpdateMouseRotation();
  /* Returns the current rotation of the mouse */
  UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Weapon Functions")
  FRotator GetCurrentMouseRotation();
  /* This event will rotate to the player's gun to the given rotation */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon Functions")
  void RotateGun(FRotator NewRotation);
  /* This event will reset the player gun rotation */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon Functions")
  void ResetGunRotation();
  /* Spells to Assign to the player for testing */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spells Info")
  TArray<TSubclassOf<AMaster_Spell>> TestSpells; 
  /* If the amount of enemies in the level is less than this than player CoolDowns will pause */
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spells Info")
  int32 CooldownEnemyTolerance;
  /* Assign a single to spell to Actionbar */
  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  bool AssignSpellToActionBar(class AMaster_Spell* SpellToAdd);
  /* Assign multiple spells to Actionbar */
  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  bool AssignSpellsToActionBar(TArray< class AMaster_Spell* > SpellsToAdd);
  /* Gun values */
  UPROPERTY(BlueprintReadWrite, Category = "Weapon Vars")
  bool bIsGunEquipped;
  UPROPERTY(BlueprintReadWrite, Category = "Weapon Vars")
  FVector GunOffset;
  UPROPERTY(BlueprintReadWrite, Category = "Weapon Vars")
  AMaster_Pickup* GunRef;
  UPROPERTY(BlueprintReadWrite, Category = "Weapon Vars")
  FVector CurrentGunScale;

  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void PauseAllSpellCooldowns();

  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  void ResumeAllSpellCooldowns();

  /* The current value of player HP */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player HP Settings")
  float PlayerCurrentHP;
  /* The max value player HP can be */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player HP Settings")
  float PlayerMaxHP;

  UFUNCTION(BlueprintCallable, Category = "SaveGame")
  void SaveGame(FString SaveSlot);

  UFUNCTION(BlueprintCallable, Category = "SaveGame")
  void LoadGame(FString SaveSlot);

  UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
  bool bLoadedCheckpoint;

  /* The level to respawn the player at */
  UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
  FName CurrentCheckpointLevel;

  UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
  bool bWasLevelLoaded;

  /* Gets all spells on players actionbar */
  UFUNCTION(BlueprintCallable, Category = "Spell Functions")
  TArray<AMaster_Spell*> GetPlayerSpellsOnActionbar();

  void CheckSpellCooldowns();

  UPROPERTY(BlueprintReadWrite, Category = "Weapon Vars")
  FRotator MouseRot;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:

  void AssignTestSpells();

  void SpawnInventory(class UWardenSaveGame* LocalSaveGameObject);

  void SpawnActionbar(class UWardenSaveGame* LocalSaveGameObject);

  TArray<AMaster_Pickup*> LoadInventory(class UWardenSaveGame* LocalSaveGameObject);

  TArray<AMaster_Pickup*> LoadActionbar(class UWardenSaveGame* LocalSaveGameObject);

  void LoadSpellCoolDowns(UWardenSaveGame* LocalSaveGameObject, TArray<AMaster_Pickup*> LocalActionbarItems);

  int32 KillCount;

  AMaster_Pickup* ItemToRest;

  bool bFoundSlot;

  bool bFoundSlotOnActionbar;

  FLoadItemInfo ItemLoadInfo;
  /* When game is loaded this is a temp container for Inventory Items */
  TArray<FLoadItemInfo> InventoryToLoad;
  /* When game is loaded this is a temp container for Actionbar Items */
  TArray<FLoadItemInfo> ActionbarToLoad;
  /* Contains all inventory items */
  TArray<class AMaster_Pickup*> InventoryItems;
  /* Contains all action bar items */
  TArray<class AMaster_Pickup*> ActionBarItems;
};
