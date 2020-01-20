// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Master_Enemy.generated.h"

class UBlueprint;

UCLASS()
class INSERTNAMEV2_API AMaster_Enemy : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

  AMaster_Enemy();
  
  UPROPERTY(EditAnywhere, Category = "HP Values")
  float CurrentHP;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float MaxHP;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float ActorDespawnDelay;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float HPBarHideDelay;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  bool bCanBeStunned;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  UBlueprint* WarlustEffect;

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
  
private:

  
};
