// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Pickup.h"
#include "Master_Gun.generated.h"

class UPaperSprite;

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API AMaster_Gun : public AMaster_Pickup
{
	GENERATED_BODY()


public:

  AMaster_Gun();

  /* The socket to attach the gun to */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  FName SocketName;
  /* The actual transform to place the gun relative to the player */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  FTransform RealativeTransform;
  /* Whether or the the gun is actually equipped */
  UPROPERTY(BlueprintReadWrite, Category = "Gun Settings")
  bool bIsGunEquipped;
  /* Scale of the gun in world */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  FVector GunScale;
  /* How much to offset the gun position in world */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  FVector GunOffset;
  /* The scale of the laser beam in world */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  FVector TrailScale;
  /* The multiplier used to multiply the length of the Multi line ray trace equation is Trace Start * TraceMultipler */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float TraceMultipler;
  /* Color of the gun's laser beam */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  FLinearColor TrailColor;
  /* Amount of time it takes for the the laser beam to despawn */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float TrailDespawn;
  /* The glow intensity of the gun laser beam */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float TrailGlowAmount;
  /* The multiplier used to determine how much the gun will knock an enemy back equation is Trace Impact Point * KnockbackRange */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float KnockBackMultipler;
  /* The multiplier used to multiply the length of the Multi line ray trace equation is Trace Start * KnockbackRangeMultipler */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float KnockbackRangeMultipler;
  /* Whether or the should faded out of the scene */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  bool bFadeOut;
  /* The rate of fire the gun is shooting at */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float FireRate;

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gun Functions")
  void FireGun();
  virtual void FireGun_Implementation();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gun Functions")
  void StopGunFire();
  virtual void StopGunFire_Implementation();


  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:

  /* Rotate gun towards the mouse */
  void RotateGun();
	
};
