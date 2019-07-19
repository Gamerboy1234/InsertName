// Fill out your copyright notice in the Description page of Project Settings.


#include "TickBuff.h"

float UTickBuff::TickDamage(float Tick, float GunDamage, float BuffAmount)
{
  float temp1 = Tick * BuffAmount + 1;
  float temp2 = temp1 * GunDamage;
  return temp2;
}
