// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperBoxCharacter.h"

APaperBoxCharacter::APaperBoxCharacter(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer.SetDefaultSubobjectClass<UBoxMovement>(APaperCharacter::CharacterMovementComponentName))
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

void APaperBoxCharacter::PostInitializeComponents()
{
  Super::PostInitializeComponents();

  BoxMovement = Cast<UBoxMovement>(Super::GetMovementComponent());
}
