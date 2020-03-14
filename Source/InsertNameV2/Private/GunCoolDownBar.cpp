// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCoolDownBar.h"
#include "Math/UnrealMathUtility.h"

void UGunCoolDownBar::SetUpWidget(float NewCurrent, float NewMax)
{
  CurrentCDPercent = NewCurrent;
  MaxCDPercent = NewMax;
  ToggleWidget(true);
}

void UGunCoolDownBar::UpdatePercent(float Value)
{
  CurrentCDPercent = FMath::Clamp<float>(CurrentCDPercent - Value, 0.0f, MaxCDPercent);
}

void UGunCoolDownBar::ToggleWidget(bool bShow)
{
  if (bShow)
  {
    SetVisibility(ESlateVisibility::Visible);
  }
  else
  {
    SetVisibility(ESlateVisibility::Hidden);
  }
}
