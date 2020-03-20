// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Master_Moveable_Platform.generated.h"

UCLASS()
class INSERTNAMEV2_API AMaster_Moveable_Platform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_Moveable_Platform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
