// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Master_Enemy.generated.h"

class UBlueprint;
class UBehaviorTree;
class AMaster_AIController;
class UFloatingCombatTextComponent;

UCLASS()
class INSERTNAMEV2_API AMaster_Enemy : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

  AMaster_Enemy();
  
  UPROPERTY(EditAnywhere, Category = "HP Values")
  float CurrentHP;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float MaxHP;

  /* The delay before a actor despawns */
  UPROPERTY(EditAnywhere, Category = "HP Values", meta = (ClampMin="1"))
  float ActorDespawnDelay;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  float HPBarHideDelay;

  UPROPERTY(EditAnywhere, Category = "HP Values")
  bool bCanBeStunned;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UFloatingCombatTextComponent* CombatTextComp;

  UPROPERTY(EditAnywhere, Category = "AI", meta = (EditCondition = "bUseBT"))
  UBehaviorTree* BehaviorTreeToUse;

  UPROPERTY(EditAnywhere, Category = "AI")
  bool bUseBT;

  UPROPERTY(EditAnywhere, Category = "AI")
  bool bAddToKillCount;

  UPROPERTY(EditAnywhere, Category = "AI")
  TSubclassOf <AMaster_AIController> ControllerToUse;

  UPROPERTY(BlueprintReadOnly, Category = "AI")
  bool bAggroed;

  UPROPERTY(EditAnywhere, Category = "Damage")
  float DamageToPlayer;

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const FVector GetHomeLocation();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const int32 GetID();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetTakenDamage();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetIsStunned();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetWasKnockedBacked();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetIsPlayerOnEnemy();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetHitPlayer();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetDefaultSpeed();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetDefaultGravityScale();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetDefaultMaxAcceleration();

  /* Apply damage to enemy */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
  void DamageEnemy(float Damage);
  virtual void DamageEnemy_Implementation(float Damage);

  /* What to do after enemy is killed */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
  void OnDeath();
  virtual void OnDeath_Implementation();

  /* Is called after all default values are set in EventBeginPlay */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Utility")
  void AfterBeginPlay();
  virtual void AfterBeginPlay_Implementation();

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
  
private:

  int32 AssignID();

  void RemoveIDFromGamemode();

  int32 ID;

  bool bIsDead;

  bool bTakenDamage;

  // Home location is the location the actor is the point the actor first spawned
  FVector HomeLocation;

  bool bIsStunned;

  float StunDuration;

  bool bIsJumping;

  float DefaultSpeed;

  float DefaultGravityScale;

  float DefaultMaxAcceleration;

  bool bWasKnockedBack;

  bool bOverlapedPlayer;

  bool bHitPlayer;

  bool bIsPlayerOnEnemy;

  
};
