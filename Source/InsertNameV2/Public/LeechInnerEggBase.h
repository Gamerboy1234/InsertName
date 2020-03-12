// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeechInnerEggBase.generated.h"

UCLASS()
class INSERTNAMEV2_API ALeechInnerEggBase : public AActor
{
	GENERATED_BODY()
	

public:

  UFUNCTION(BlueprintNativeEvent,  BlueprintCallable, Category = "Leech Egg Functions")
  void SpawnActor();
  void SpawnActor_Implementation();

};
