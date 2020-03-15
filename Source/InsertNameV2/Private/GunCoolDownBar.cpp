// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCoolDownBar.h"
#include "Math/UnrealMathUtility.h"

void UGunCoolDownBar::SetUpWidget(float NewCurrent, float NewMax)
{
  CurrentCDPercent = NewCurrent;
  MaxCDPercent = NewMax;
  ShowWidget(false);
}

void UGunCoolDownBar::UpdatePercent(float Playback, float Length)
{
  CurrentCDPercent = Length - Playback;
}

void UGunCoolDownBar::ShowWidget(bool bShow)
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
