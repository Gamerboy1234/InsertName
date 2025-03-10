// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointBase.generated.h"

UCLASS()
class INSERTNAMEV2_API ACheckPointBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPointBase();

  UPROPERTY(BlueprintReadWrite, Category = "Checkpoint Vars")
  bool bPlayerUsedCheckpoint;
};
