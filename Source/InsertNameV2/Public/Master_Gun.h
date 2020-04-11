// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Pickup.h"
#include "Components/TimelineComponent.h"
#include "Master_Gun.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;
class UGunCoolDownBar;
class AGunBeamEffectBase;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API AMaster_Gun : public AMaster_Pickup
{
	GENERATED_BODY()


public:

  AMaster_Gun();

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UWidgetComponent* WidgetCompFront;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UWidgetComponent* WidgetCompBack;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UBoxComponent* BarrelCollision;
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
  /* The laser beam to spawn */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  TSubclassOf<AGunBeamEffectBase> BeamEffectToUse;
  /* Color of the gun's laser beam */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  FLinearColor BeamColor;
  /* Amount of time it takes for the the laser beam to Despawn */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float BeamDespawnDelay;
  /* The glow intensity of the gun laser beam */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float BeamBrightness;
  /* The beam exponent the higher this number is the less thick it is */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float BeamExponent;
  /* The multiplier used to determine how much the gun will knock an enemy back equation is Trace Impact Point * KnockbackRange */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float KnockBackMultipler;
  /* The multiplier used to multiply the length of the Multi line ray trace equation is Trace Start * KnockbackRangeMultipler */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float KnockbackRangeMultipler;
  /* Time it takes for the player to be able to fire the gun again */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float GunCoolDown;
  /* How much damage the gun will deal to the given enemy */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gun Settings")
  float Damage;
  /* Will fire a multi line ray cast to look for enemies to damage */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gun Functions")
  void FireMultiLineTrace(bool bApplyKnockback);
  virtual void FireMultiLineTrace_Implementation(bool bApplyKnockback);
  /* Will stop the gun from firing it's raycast and apply the gun cooldown */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gun Functions")
  void StopGunFire();
  virtual void StopGunFire_Implementation();
  /* Will spawn a laser beam across the raytrace of the gun */
  UFUNCTION(BlueprintCallable, Category = "Gun Functions")
  void SpawnLaserBeam(FVector StartLocation, FVector EndLocation);
  /* Reads the value of bOnCooldown */
  UFUNCTION(BlueprintPure, Category = "Gun Functions")
  const bool GetGunOnCooldown();
  /* Gets the default damage */
  UFUNCTION(BlueprintPure, Category = "Gun Functions")
  const float GetDefaultDamage();
  /* Reads the value of bCanFireTrace */
  UFUNCTION(BlueprintPure, Category = "Gun Functions")
  const bool GetCanFireTrace();
  /* Reads the value of TraceStart */
  UFUNCTION(BlueprintPure, Category = "Gun Functions")
  const FVector GetTraceStart();
  /* Reads the value of TraceEnd */
  UFUNCTION(BlueprintPure, Category = "Gun Functions")
  const FVector GetTraceEnd();
  /* Gets the current front cooldown widget */
  UFUNCTION(BlueprintPure, Category = "Gun Functions")
  UGunCoolDownBar* GetFrontCDWidget();
  /* Gets the current back cooldown widget */
  UFUNCTION(BlueprintPure, Category = "Gun Functions")
  UGunCoolDownBar* GetBackCDWidget();

  /* Upon player interacting with this object call player equip gun function */
  virtual void OnInteract_Implementation() override;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

  UFUNCTION()
  void MouseTimelineProgress(float Value);

  virtual void AttackKeyPressed();

  virtual void AttackKeyReleased();

  /* Setup the initialize gun input state */
  UFUNCTION(BlueprintCallable, Category = "Gun Functions")
  void SetupInput();

  /* Will disable Input on Gun */
  UFUNCTION(BlueprintCallable, Category = "Gun Functions")
  void DisableGunInput();

  /* Will enable Input on Gun */
  UFUNCTION(BlueprintCallable, Category = "Gun Functions")
  void EnableGunInput();

  /* Update the current Cooldown bar percent */
  UFUNCTION(BlueprintCallable, Category = "Gun Functions")
  void UpdateCDBar(float Playback, float Length, float CDTime);

  bool bOnCooldown;

  bool bDisabledGun;

  virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

  UFUNCTION()
  void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  FTimeline MouseTimeline;

  UPROPERTY()
  UCurveFloat* CurveFloat;

private:

  void SetupCDWidget();

  FRotator GetMouseRotation();

  bool bCanFireTrace;

  FVector TraceStart;
  
  FVector TraceEnd;

  /* Rotate gun towards the mouse */
  void RotateGunToMouse();

  float DefaultDamage;

  TArray<AActor*> HitActors;

  void DamageOrKnockHitActors(bool bApplyKnockback);

  bool DidTraceHitEnemy(AActor* HitActor);

  bool DidTraceHitMagnet(AActor* HitActor);

  bool DidTraceHitDamageEffect(AActor* HitActor);

  UGunCoolDownBar* CDWidgetFront;

  UGunCoolDownBar* CDWidgetBack;

  TSubclassOf<UGunCoolDownBar> CDClass;
};
