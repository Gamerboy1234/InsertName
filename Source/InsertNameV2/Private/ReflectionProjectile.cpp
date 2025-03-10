// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GeneralFunctions.h"
#include "PaperFlipBookComponent.h"
#include "InsertNameV2.h"
#include "PaperWarden.h"
#include "Components/SphereComponent.h"

static int32 DebugReflectionHit = 0;
FAutoConsoleVariableRef CVARDebugReflectionProjectile(
  TEXT("Reflection.DebugHit"),
  DebugReflectionHit,
  TEXT("Prints reflection projectile hit actor"),
  ECVF_Cheat);


// Sets default values
AReflectionProjectile::AReflectionProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  // Collision Setup
  SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere Component"));
  SphereComponent->SetSphereRadius(130.0f);
  SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
  RootComponent = SphereComponent;
  // Flipbook Setup
  FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("FlipBook"));
  FlipBook->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  FlipBook->SetupAttachment(SphereComponent);
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

  KnockbackMultiplier = 100;
}

// Called when the game starts or when spawned
void AReflectionProjectile::BeginPlay()
{
  Super::BeginPlay();
  SphereComponent->OnComponentHit.AddDynamic(this, &AReflectionProjectile::OnHit);
  SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AReflectionProjectile::OnOverlapBegin);

  ID = UGeneralFunctions::GetIDFromGamemode(this, this);
}

void AReflectionProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  OnObjectOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

  if (OtherActor)
  {
    if (OtherActor)
    {
      if (DebugReflectionHit)
      {
        UE_LOG(LogMasterEnemy, Log, TEXT("%s Overlapped %s"), *this->GetName(), *OtherActor->GetName())
      }
    }

    APaperCharacter* HitPlayer = Cast<APaperWarden>(OtherActor);

    if (HitPlayer)
    {
      UGeneralFunctions::LaunchCharacterAwayFromActor(HitPlayer, this, KnockbackMultiplier);

      ReflectProjectile(SweepResult);
    }
  }
}

void AReflectionProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  ReflectProjectile(Hit);

  if (OtherActor)
  {
    if (DebugReflectionHit)
    {
      UE_LOG(LogMasterEnemy, Log, TEXT("%s Hit %s"), *this->GetName(), *OtherActor->GetName())
    }
  }
}

void AReflectionProjectile::ReflectProjectile(const FHitResult& Hit)
{
  FVector ReflectedVelocity = BounceSpeedLoss * (-2 * FVector::DotProduct(MyVelocity, Hit.Normal) * Hit.Normal + MyVelocity);
  MyVelocity = ReflectedVelocity;
  ReflectedVelocity.Normalize();
  SetActorRotation(ReflectedVelocity.Rotation());
  bReflected = true;
  OnObjectHit(Hit);
}

// Called every frame
void AReflectionProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  // Updated Velocity
  SetActorLocation(GetActorLocation() + MyVelocity * DeltaTime, true);
}

// Called when Firewall spell collision hits this projectile can be overridden in Blueprints
void AReflectionProjectile::OnFireWallHit_Implementation()
{
  Destroy();
}

const int32 AReflectionProjectile::GetID()
{
  return ID;
}
