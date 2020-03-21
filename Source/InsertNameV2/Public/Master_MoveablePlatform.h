// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Master_MoveablePlatform.generated.h"

UCLASS()
class INSERTNAMEV2_API AMaster_MoveablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_MoveablePlatform();

  /* Visual representation of the platform */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UPaperSpriteComponent* SpriteComp;

  /* Location to move to */
  UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true), Category = "Platform Settings")
  FVector TargetLocation;

  /* The speed of this platform */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
  float MovementSpeed;

  /* Whether or not the platform should move to target location then stop or should it bounce back to the starting location */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
  bool bOneShot;

  /* Updates the movement of the platform make it so that it either can move or disable movement */
  UFUNCTION(BlueprintCallable, Category = "Movement Functions")
  void SetCanMove(bool bShouldMove);
  
  /* Reads the value of bCanMove */
  UFUNCTION(BlueprintPure, Category = "Movement Functions")
  const bool GetCanMove();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

  FVector GlobalTargetLocation;

  FVector GlobalStartLocation;

  bool bCanMove;
};
