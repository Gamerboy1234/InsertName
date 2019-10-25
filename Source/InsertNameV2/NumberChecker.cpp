// Fill out your copyright notice in the Description page of Project Settings.


#include "NumberChecker.h"
#include<iostream>


using namespace std;
bool UNumberChecker::IsNumberNegative(float number)
{
  if (number >= 0)
    return false;
  else
    return true;
  return false;
}
