// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PaperWarden.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API APaperWarden : public APaperZDCharacter
{
	GENERATED_BODY()

public:

  APaperWarden();

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UBoxComponent* BarkInnerCollision;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UBoxComponent* BarkOuterCollision;

  UFUNCTION(BlueprintCallable, Category = "Utility")
  int32 AddToKillCount(int32 AmountToadd);

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const int32 GetCurrentKillCount();

  UFUNCTION(BlueprintCallable, Category = "Utility")
  void LoadKillCount(int32 KillCountToLoad);

  UFUNCTION(BlueprintImplementableEvent, Category = "Utility")
  void OnBarkInnerOverlap(AActor* OverlappedActor);

  UFUNCTION(BlueprintImplementableEvent, Category = "Utility")
  void OnBarkOuterOverlap(AActor* OverlappedActor);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Player Events")
  void HealPlayer(float HealAmount);
  virtual void HealPlayer_Implementation(float HealAmount);

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  UFUNCTION()
  void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:

  int32 KillCount;

};
