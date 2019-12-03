// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AReflectionProjectile::AReflectionProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  // Collsion Setup
  SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere Component"));
  RootComponent = SphereComponent;
  // Movement Setup
  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectialMovement"));
  ProjectileMovement->UpdatedComponent = SphereComponent;
  ProjectileMovement->bRotationFollowsVelocity = true;
  ProjectileMovement->bShouldBounce = true;
  // Get Current Velocity of Actor
  MyVelocity = GetActorForwardVector() * CurrentSpeed;
}

// Called when the game starts or when spawned
void AReflectionProjectile::BeginPlay()
{
  Super::BeginPlay();
  SphereComponent->OnComponentHit.AddDynamic(this, &AReflectionProjectile::OnHit);
}

void AReflectionProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  // Reflect the projectile because we hit a non-physics object
  FVector ReflectedVelocity = BounceSpeedLoss * (-2 * FVector::DotProduct(MyVelocity, Hit.Normal) * Hit.Normal + MyVelocity);
  MyVelocity = ReflectedVelocity;
  CurrentReflection = ReflectedVelocity;
  ReflectedVelocity.Normalize();
  SetActorRotation(ReflectedVelocity.Rotation());
  bReflected = true;
 
}


// Called every frame
void AReflectionProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  // Debug Info
  FColor LineColor = bReflected ? FColor::Red : FColor::Green;
  DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + MyVelocity * DeltaTime, LineColor, false, 2.f, 0, 1.f);
  // Updated Velocity
  SetActorLocation(GetActorLocation() + MyVelocity * DeltaTime, true);
}
