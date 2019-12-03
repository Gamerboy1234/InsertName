// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReflectionProjectile.generated.h"

class UProjectileMovementComponent;
class UPaperFlipbookComponent;

UCLASS()
class INSERTNAMEV2_API AReflectionProjectile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AReflectionProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  UPaperFlipbookComponent* PaperFlipBook = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
  UProjectileMovementComponent* ProjectialMovement = nullptr;
 
};
