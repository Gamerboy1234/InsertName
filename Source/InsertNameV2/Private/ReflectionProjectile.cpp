// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipBookComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AReflectionProjectile::AReflectionProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  // Collsion Setup
  SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere Component"));
  RootComponent = SphereComponent;
  FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("FlipBook"));
  FlipBook->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
  // Movement Setup
  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectialMovement"));
  ProjectileMovement->UpdatedComponent = SphereComponent;
  ProjectileMovement->bRotationFollowsVelocity = true;
  ProjectileMovement->bShouldBounce = true;
  ProjectileMovement->Bounciness = 1;
  ProjectileMovement->Friction = 0;
  ProjectileMovement->BounceVelocityStopSimulatingThreshold = 0;
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
  FVector ReflectedVelocity = BounceSpeedLoss * (-2 * FVector::DotProduct(MyVelocity, Hit.Normal) * Hit.Normal + MyVelocity);
  MyVelocity = ReflectedVelocity;
  ReflectedVelocity.Normalize();
  SetActorRotation(ReflectedVelocity.Rotation());
  HitResult = Hit;
  bReflected = true;
  OnObjectHit();
}

// Called every frame
void AReflectionProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  // Updated Velocity
  SetActorLocation(GetActorLocation() + MyVelocity * DeltaTime, true);
}

// Called when Firewall spell collision hits this projectile can be overriden in Blueprints
void AReflectionProjectile::OnFireWallHit_Implementation()
{
  Destroy();
}
