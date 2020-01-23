// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PaperWarden.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API APaperWarden : public APaperZDCharacter
{
	GENERATED_BODY()

public:

  UFUNCTION(BlueprintCallable, Category = "Utility")
  int32 AddToKillCount(int32 AmountToadd);

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const int32 GetCurrentKillCount();

  UFUNCTION(BlueprintCallable, Category = "Utility")
  void LoadKillCount(int32 KillCountToLoad);

private:

  int32 KillCount;

};
