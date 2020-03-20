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

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UBoxComponent* BoxTrigger;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class UPaperSpriteComponent* SpriteComp;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Plate Settings")
  class AMaster_Moveable_Platform* CurrentPlatform;

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
