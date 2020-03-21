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

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UPaperSpriteComponent* SpriteComp;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UBoxComponent* PlayerCollision;

  UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true), Category = "Platform Settings")
  FVector TargetLocation;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
  float MovementSpeed;

  /* Whether or not the platform move to target location then stop or should it bounce back to the starting location */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
  bool bOneShot;

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
