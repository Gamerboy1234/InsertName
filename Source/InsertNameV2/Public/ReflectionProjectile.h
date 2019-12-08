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

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SpellFunction)
  void OnFireWallHit();
  void OnFireWallHit_Implementation();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Collision)
  void OnObjectHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Projectile)
  UProjectileMovementComponent* ProjectileMovement = nullptr;

  UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Projectile)
  USphereComponent* SphereComponent = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = Projectile)
  FHitResult HitResult;

  UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Projectile)
  UPaperFlipbookComponent* FlipBook = nullptr;

  // Speed loss after reflection
  UPROPERTY(BlueprintReadWrite, Category = Projectile)
  float BounceSpeedLoss = 0;
  // How fast the projectile movess
  UPROPERTY(BlueprintReadWrite, Category = Projectile)
  float CurrentSpeed = 0;

private:
  // Sets default values for this actor's properties
  AReflectionProjectile();

  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
