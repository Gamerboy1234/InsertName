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
  int32 GenID(AActor* ActorToAdd);

  /* Manually add an Actor to gamemode */
  UFUNCTION(BlueprintCallable, Category = "Actor Function")
  void AddActorToGamemode(AActor* ActorToAdd, int32 IDToAdd);

  /* Remove a given pickup from AllActors array */
  UFUNCTION(BlueprintCallable, Category = "Actor Function")
  void RemovePickupFromGamemode(AMaster_Pickup* PickupToRemove);

  UFUNCTION(BlueprintCallable, Category = "Actor Function")
  void RemoveActorFromGamemode(AActor* ActorToRemove);

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

  /* Returns an array of all actors in gamemode */
  UFUNCTION(Blueprintpure, Category = "Actor Function")
  const TArray<AActor*> GetAllActors();

  /* Find the Index of given ID in AllIDs array */
  UFUNCTION(BlueprintCallable, Category = "ID Function")
  int32 FindIDInArray(int32 ID);

  /* Find the index of Actor in AllActors array */
  UFUNCTION(BlueprintCallable, Category = "Actor Function")
  int32 FindPickupByID(int32 ID);



private:
  /* A list of all actor IDs */
  TArray<int32> AllIDs;

  /* A list of all actors with ID's in the world */
  TArray<AActor*> AllActors;

  /* Looks to see if given ID is already assigned to an actor */
  bool DoesIDAlreadyExist(int32 ID);
};
