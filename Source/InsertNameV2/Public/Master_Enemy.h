// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DebuffData.h"
#include "Master_Enemy.generated.h"

class UBlueprint;
class UBehaviorTree;
class AMaster_AIController;
class UFloatingCombatTextComponent;
class AMaster_Debuff_E;

UCLASS()
class INSERTNAMEV2_API AMaster_Enemy : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

  AMaster_Enemy();

  UPROPERTY(BlueprintReadOnly, Category = "Debuffs")
  TArray<AMaster_Debuff_E*> CurrentDebuffs;

  UPROPERTY(BlueprintReadWrite, Category = "Debuffs")
  bool bIsCurrentlyOnFire;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP Values")
  float CurrentHP;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP Values")
  float MaxHP;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP Values")
  bool bTakenDamage;

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

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
  bool bUseBT;

  UPROPERTY(EditAnywhere, Category = "AI")
  bool bAddToKillCount;

  UPROPERTY(EditAnywhere, Category = "AI")
  TSubclassOf <AMaster_AIController> ControllerToUse;

  UPROPERTY(BlueprintReadWrite, Category = "AI")
  bool bAggroed;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
  float DamageToPlayer;

  UPROPERTY(BlueprintReadWrite, Category = "AI")
  bool bWasKnockedBack;

  UPROPERTY(BlueprintReadWrite, Category = "AI")
  bool bOverlapedPlayer;

  UPROPERTY(BlueprintReadWrite, Category = "AI")
  bool bHitPlayer;

  UPROPERTY(BlueprintReadWrite, Category = "AI")
  bool bIsPlayerOnEnemy;

  UFUNCTION(BlueprintCallable, Category = "Debuffs")
  AActor* ApplyDebuff(TSubclassOf<AMaster_Debuff_E> DebuffToApply, FDebuffData DebuffData, AActor* Target);

  UFUNCTION(BlueprintCallable, Category = "Debuffs")
  void RemoveAllDebuffs();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const FVector GetHomeLocation();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const int32 GetID();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetTakenDamage();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetIsStunned();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetDefaultSpeed();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetDefaultGravityScale();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetDefaultMaxAcceleration();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetIsDead();

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

  int32 ID;

  bool bIsDead;

  // Home location is the location the actor is the point the actor first spawned
  FVector HomeLocation;

  bool bIsStunned;

  float StunDuration;

  bool bIsJumping;

  float DefaultSpeed;

  float DefaultGravityScale;

  float DefaultMaxAcceleration;

  AMaster_Debuff_E* MostRecentDebuff;
};
