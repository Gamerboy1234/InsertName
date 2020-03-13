// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterDamageEffect.generated.h"

class AMaster_Enemy;
class UFloatingCombatTextComponent;

UCLASS()
class INSERTNAMEV2_API AMasterDamageEffect : public AActor
{
	GENERATED_BODY()
	
public:	

  AMasterDamageEffect();
  
  UFUNCTION(BlueprintNativeEvent , BlueprintCallable , Category = "Effect Setup")
  void SetEffect(AActor* CurrentActor);
  void SetEffect_Implementation(AActor* CurrentActor);

  UFUNCTION(BlueprintNativeEvent , BlueprintCallable , Category = "Effect Setup")
  void RemoveEffect();
  void RemoveEffect_Implementation();

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect Setup")
  void DamageActor(float Damage, bool bShowText, AActor* DamageInstigator);
  void DamageActor_Implementation(float Damage, bool bShowText, AActor* DamageInstigator);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect Setup")
  void OnDeath();
  void OnDeath_Implementation();

  UFUNCTION(BlueprintCallable , Category = "CleanUp")
  void CleanUpEffect(TSubclassOf<AMasterDamageEffect> EffectToCleanUp);

  UFUNCTION(BlueprintPure, Category = "Effect Getter Functions")
  const bool GetIsDead();

  UFUNCTION(BlueprintPure, Category = "Effect Getter Functions")
  const bool GetTakenDamage();

  UFUNCTION(BlueprintPure, Category = "Effect Getter Functions")
  const int32 GetID();

  UPROPERTY(BlueprintReadWrite , Category = "Effect Setup")
  FVector EffectScale;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UFloatingCombatTextComponent* CombatTextComp;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "Effect Setup")
  bool bAbleToTakeDamage;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bAbleToTakeDamage") , Category = "Effect Setup")
  float CurrentHP;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bAbleToTakeDamage") , Category = "Effect Setup")
  float MaxHP;

  bool bTakenDamage;

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:

  bool bIsDead;

  int32 ID;

};
