// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "ReflectionProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UPaperFlipbookComponent;

UCLASS()
class INSERTNAMEV2_API AReflectionProjectile : public AActor
{
	GENERATED_BODY()

  bool bReflected;
  /** Projectile's velocity vector */
  FVector MyVelocity;

public:	

  /* Called when hit by fire wall collision */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SpellFunction")
  void OnFireWallHit();
  void OnFireWallHit_Implementation();
  /* Called object is Hit returns the Hit struct */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Events")
  void OnObjectHit(FHitResult NewHit);
  /* Called on overlaps */
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Events")
  void OnObjectOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
  /* Gets this objects ID */
  UFUNCTION(BlueprintPure, Category = "Projectile Functions")
  const int32 GetID();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
  UProjectileMovementComponent* ProjectileMovement = nullptr;

  UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
  USphereComponent* SphereComponent = nullptr;

  UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
  UPaperFlipbookComponent* FlipBook = nullptr;

  // Speed loss after reflection
  UPROPERTY(BlueprintReadWrite, Category = "Projectile")
  float BounceSpeedLoss = 0;
  // How fast the projectile moves
  UPROPERTY(BlueprintReadWrite, Category = "Projectile")
  float CurrentSpeed = 0;
  /* When overlapping with the player this is multiplier used to determine knockback */
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
  float KnockbackMultiplier;

private:
  // Sets default values for this actor's properties
  AReflectionProjectile();

  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  int32 ID;

  void ReflectProjectile(const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
