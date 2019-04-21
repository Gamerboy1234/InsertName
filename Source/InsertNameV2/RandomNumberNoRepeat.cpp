  // Fill out your copyright notice in the Description page of Project Settings.

#include "RandomNumberNoRepeat.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std; 

int URandomNumberNoRepeat::RandomNumber(int max, int min)
{
  if (min > max) {
    int temp = max; 
    max = min; 
    min = temp; 
  }
  
  static bool first = true;
  if (first)
  {
    srand(time(NULL)); //seeding for the first time only!
    first = false;
  }
  return min + rand() % ((max + 1) - min);
}
