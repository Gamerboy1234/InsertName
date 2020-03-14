// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GunCoolDownBar.generated.h"

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UGunCoolDownBar : public UUserWidget
{
	GENERATED_BODY()

public:

  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  float CurrentCDPercent;

  UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
  float MaxCDPercent;

  UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
  void FadeIn();

  UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
  void FadeOut();

  void SetUpWidget(float NewCurrent, float NexMax);

  void UpdatePercent(float Value);

  void ToggleWidget(bool bShow);
};
