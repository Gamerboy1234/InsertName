// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Master_Magnet.generated.h"

class USphereComponent;
class UPaperSpriteComponent;
class APaperWarden;
class UPaperSprite;

UCLASS()
class INSERTNAMEV2_API AMaster_Magnet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_Magnet();
  /* When player enters this collision will pull player if current active */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USphereComponent* OuterSphereComp;
  /* When player shoots this collision the magnet will deactivate */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USphereComponent* InnerSphereComp;
  /* The sprite to show if the magnet is currently active */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet Settings")
  UPaperSprite* ActiveSprite;
  /* The sprite to show if the magnet is currently deactivated */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet Settings")
  UPaperSprite* DeactivatedSprite;
  /* The magnets current sprite */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UPaperSpriteComponent* CurrentSprite;
  /* The strength at which to pull towards the magnet */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet Settings")
  float GravityStrength;
  /* If the magnet can currently pull the player */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet Settings")
  bool bActive;
  /* Updates the magnets current sprite to given sprite */
  UFUNCTION(BlueprintCallable, Category = "Magnet Functions")
  void UpdateSprite(UPaperSprite* Sprite);
  /* Called to activate the magnet and start player pull */
  UFUNCTION(BlueprintCallable, Category = "Magnet Functions")
  void Activate();
  /* Called to stop the magnet from pulling the player */
  UFUNCTION(BlueprintCallable, Category = "Magnet Functions")
  void Deactivate();
  /* Called when magnet stops pull the player */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Magnet Functions")
  void OnPullStop();
  void OnPullStop_Implementation();
  /* Called to stop pull timer */
  UFUNCTION(BlueprintCallable, Category = "Magnet Functions")
  void StopTimer();

  UFUNCTION()
  void OnOuterOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  UFUNCTION()
  void OnOuterOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

  UFUNCTION()
  void OnSpriteHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  /* The actually timer that is pulling the player */
  UPROPERTY(BlueprintReadOnly, Category = "Magnet Settings")
  FTimerHandle PullTimer;

private:

  APaperWarden* PlayerRef;

  void PullPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
