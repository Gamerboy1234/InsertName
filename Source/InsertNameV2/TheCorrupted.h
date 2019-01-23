// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheCorrupted.generated.h"

UCLASS()
class INSERTNAMEV2_API ATheCorrupted : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheCorrupted();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  UPROPERTY(EditAnywhere,BlueprintReadWrite)
   float velocity;
  UPROPERTY(EditAnywhere)
    float idlespeed;
  UPROPERTY(EditAnywhere)
    bool leftturn;
  UPROPERTY(EditAnywhere)
    bool rightturn; 
  UPROPERTY(BlueprintReadWrite)
    bool ag; 

};
