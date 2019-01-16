// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JN_Ranged.generated.h"

UCLASS()
class INSERTNAMEV2_API AJN_Ranged : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJN_Ranged();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
		bool dead;
	UPROPERTY(BlueprintReadWrite)
		bool isRight;
	UPROPERTY(BlueprintReadWrite)
		bool isLeft;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
		int SpearAmmount;
	UPROPERTY(BlueprintReadWrite)
		bool SpearFound;
	UPROPERTY(BlueprintReadWrite)
		FVector SpearLocation; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int maxSpearAmount; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int agRadius; 
	UPROPERTY(BlueprintReadWrite)
		bool isFiring;
	UPROPERTY(BlueprintReadWrite)
		bool aggro;
	UPROPERTY(BlueprintReadWrite)
		bool finished1;
	
};
