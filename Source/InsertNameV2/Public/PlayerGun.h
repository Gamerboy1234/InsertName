// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Gun.h"
#include "PlayerGun.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API APlayerGun : public AMaster_Gun
{
	GENERATED_BODY()

public:

  virtual void AttackKeyPressed() override;

  virtual void AttackKeyReleased() override;

private:

  void LightAttack();

  void HeveyAttack();
};
