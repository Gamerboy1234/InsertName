// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Master_PressurePlate.generated.h"

UCLASS()
class INSERTNAMEV2_API AMaster_PressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_PressurePlate();

  /* Visual representation of the platform */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UPaperSpriteComponent* SpriteComp;
   
  /* Overlap trigger when player overlaps this the CurrentPlatform will start moving */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UBoxComponent* BoxTrigger;
  
  /* Platform to trigger */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate Settings")
  class AMaster_MoveablePlatform* CurrentPlatform;

  /* Whether or not this trigger can used multiple times */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plate Settings")
  bool bOneShot;

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

  bool bAlreadyUsed;
};
