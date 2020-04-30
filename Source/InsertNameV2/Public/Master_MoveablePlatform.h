// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InterpToMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Master_MoveablePlatform.generated.h"

UCLASS()
class INSERTNAMEV2_API AMaster_MoveablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_MoveablePlatform();

  /* Whether or not the platform should wait for pressure pate input to start moving */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
  bool bStartWithPlate;

  /* Function called to start platform movement */
  UFUNCTION(BlueprintImplementableEvent, Category = "Platform Events")
  void StartMovement();
};
