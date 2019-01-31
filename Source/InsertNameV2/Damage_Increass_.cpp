// Fill out your copyright notice in the Description page of Project Settings.

#include "Damage_Increass_.h"
#include <iostream>

float UDamage_Increass_::IncreaseDamage(float Damage, float DamageAmount)
{
  float temp = Damage * .3; 
  float temp2 = temp + 1; 
  float temp3 = temp2 + DamageAmount; 
  return temp3; 
}
