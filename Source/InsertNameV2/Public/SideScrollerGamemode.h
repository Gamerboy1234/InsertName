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

  UFUNCTION(BlueprintCallable, Category = "ID Function")
  int32 GenID();

  UFUNCTION(BlueprintCallable, Category = "ID Function")
  void RemoveID(int32 IDToRemove);

  UFUNCTION(Blueprintpure, Category = "ID Function")
  bool bDoesIDAlreadyExist(int32 ID);

  UFUNCTION(Blueprintpure, Category = "ID Function")
  const TArray<int32> GetAllIDs();

private:
  TArray<int32> AllIDs;
};
