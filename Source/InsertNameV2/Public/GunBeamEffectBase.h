// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBeamEffectBase.generated.h"

class UParticleSystemComponent;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class INSERTNAMEV2_API AGunBeamEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBeamEffectBase();

  UPROPERTY(VisibleAnywhere, Category = "Components")
  USceneComponent* RootComp;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent* BeamStart;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent* BeamEnd;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UParticleSystemComponent* BeamEffect;

  UPROPERTY(EditAnywhere, Category = "Beam Settings")
  FLinearColor BeamColor;

  UPROPERTY(EditAnywhere, Category = "Beam Settings")
  float BeamExponent;

  UPROPERTY(EditAnywhere, Category = "Beam Settings")
  float BeamBrightness;

  /* Set BeamStart and BeamEnd location and actor life span */
  void SetupBeam(FVector StartLocation, FVector EndLocation, float LifeSpan, FLinearColor ColorToSet, float BeamBrightnessToSet, float BeamExponentToSet);

  /* Change the location of the beam end point */
  void UpdateBeamEndPoint(FVector NewLocation);

};
