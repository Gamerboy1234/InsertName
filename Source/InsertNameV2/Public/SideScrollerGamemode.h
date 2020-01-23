// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SideScrollerGamemode.generated.h"

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

  /* Removes given ID from AllIDs Array */
  UFUNCTION(BlueprintCallable, Category = "ID Function")
  void RemoveID(int32 IDToRemove);

  /* Returns an array of all actor IDs */
  UFUNCTION(Blueprintpure, Category = "ID Function")
  const TArray<int32> GetAllIDs();

private:
  /* A list of all actor IDs */
  TArray<int32> AllIDs;

  /* Looks to see if given ID is already assigned to an actor */
  bool DoesIDAlreadyExist(int32 ID);
};
