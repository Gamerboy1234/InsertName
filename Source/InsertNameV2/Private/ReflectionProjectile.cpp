// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AReflectionProjectile::AReflectionProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  ProjectialMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectialMovement"));
  PaperFlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("PaperFlipBook;"));
}

// Called when the game starts or when spawned
void AReflectionProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReflectionProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

