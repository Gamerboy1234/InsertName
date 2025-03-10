// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SideScrollerGamemode.generated.h"

class AMaster_Pickup;

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API ASideScrollerGamemode : public AGameMode
{
	GENERATED_BODY()
	
public:

  /* Generates a random number to be assigned to an actor as a ID */
  UFUNCTION(BlueprintCallable, Category = "ID Function")
  int32 GenID();

  /* Create an Item obtained message and add to screen */
  UFUNCTION(BlueprintNativeEvent, Category = "HUD Events")
  void DisplayItemObtainedMessage(AMaster_Pickup* Pickup, int32 Amount);
  void DisplayItemObtainedMessage_Implementation(AMaster_Pickup* Pickup, int32 Amount);

  /* Create a text message and add it to screen */
  UFUNCTION(BlueprintNativeEvent, Category = "HUD Events")
  void DisplayTextMessage(const FText& Message);
  void DisplayTextMessage_Implementation(const FText& Message);

  /* Removes given ID from AllIDs Array */
  UFUNCTION(BlueprintCallable, Category = "ID Function")
  void RemoveID(int32 IDToRemove);

  /* Returns an array of all actor IDs */
  UFUNCTION(Blueprintpure, Category = "ID Function")
  const TArray<int32> GetAllIDs();

  /* Console command that will reset all current spell cooldowns */
  UFUNCTION(Exec, Category = "Console Commands")
  void ResumeAllCoolDowns();

private:
  /* A list of all actor IDs */
  TArray<int32> AllIDs;

  /* Looks to see if given ID is already assigned to an actor */
  bool DoesIDAlreadyExist(int32 ID);
};
