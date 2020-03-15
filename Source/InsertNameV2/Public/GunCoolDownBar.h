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

  /* Set default percent values */
  void SetUpWidget(float NewCurrent, float NexMax);

  void UpdatePercent(float Playback, float Length, float CDTime);

  /* Hide or show widget */
  UFUNCTION(BlueprintCallable, Category = "Animation Events")
  void ShowWidget(bool bShow);
};
