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
  void AddToInventory(class AMaster_Pickup* ItemToAdd);
  /* Inventory Debug Function prints out all current inventory items */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void PrintInventory();
  /* Returns all items in player's inventory */
  UFUNCTION(BlueprintPure, Category = "Inventory Functions")
  const TArray<class AMaster_Pickup*> GetPlayerInventory();
  /* Sends update to player inventory widget */
  UFUNCTION(BlueprintCallable, Category = "Inventory Functions")
  void UpdateInventory();
  UPROPERTY(BlueprintAssignable, Category = "Inventory")
  FUpdateInventoryDelegate OnUpdateInventory;

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:

  int32 KillCount;

  TArray<class AMaster_Pickup*> InventoryItems;

};
