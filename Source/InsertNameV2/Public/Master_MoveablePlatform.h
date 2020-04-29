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

   /* Whether or not the platform should automatically move when game is started */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings", meta = (EditCondition = "!bStartWithPlate"))
  bool bAutoStart;

  /* Whether or not the platform should wait for pressure pate input to start moving */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings", meta = (EditCondition = "!bAutoStart"))
  bool bStartWithPlate;

  /* Function called to start platform movement */
  UFUNCTION(BlueprintCallable, Category = "Platform Functions")
  void StartMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
  
  bool bCanMove;

  FVector GlobalTargetLocation;

  FVector GlobalStartLocation;
};
