// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "PaperZDCharacter.h"
#include "DebuffData.h"
#include "BuffData.h"
#include "Master_Enemy.generated.h"

class UBlueprint;
class UBehaviorTree;
class AMaster_AIController;
class UFloatingCombatTextComponent;
class AMaster_Debuff_E;
class USplineComponent;
class AMasterDamageEffect;
class AMaster_Buff_E;
class AWarlustEffectBase;
class UCurveFloat;

UCLASS()
class INSERTNAMEV2_API AMaster_Enemy : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

  AMaster_Enemy();

  UPROPERTY(BlueprintReadOnly, Category = "Debuffs")
  TArray<AMaster_Debuff_E*> CurrentDebuffs;

  UPROPERTY(BlueprintReadOnly, Category = "Buffs")
  TArray<AMaster_Buff_E*> CurrentBuffs;

  UPROPERTY(BlueprintReadWrite, Category = "Debuffs")
  bool bIsCurrentlyOnFire;

  UPROPERTY(BlueprintReadWrite, Category = "Debuffs")
  AWarlustEffectBase* WarlustEffect;

  UPROPERTY(BlueprintReadWrite, Category = "Debuffs")
  bool bDidEnemyTouchFlameMagnet;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP Values")
  float CurrentHP;

  UPROPERTY(BlueprintReadWrite, Category = "HP Values")
  bool bTakenDamage;

  /* The delay before a actor despawns */
  UPROPERTY(EditAnywhere, Category = "HP Values", meta = (ClampMin=".001"))
  float ActorDespawnDelay;
  
  UPROPERTY(EditAnywhere, Category = "HP Values")
  bool bCanBeStunned;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UFloatingCombatTextComponent* CombatTextComp;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  USplineComponent* EnemySpline;
  /* If true the given enemy is using a behavior tree so stunning will need to use different code */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
  bool bUseBT;
  /* If true enemy will add to the player's overall kill count */
  UPROPERTY(EditAnywhere, Category = "AI")
  bool bAddToKillCount;

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
  bool bIsFlying;

  UPROPERTY(BlueprintReadWrite, Category = "AI")
  bool bIsPlayerOnEnemy;

  UPROPERTY(BlueprintReadWrite, Category = "AI")
  bool bHitByRage;

  UFUNCTION(BlueprintCallable, Category = "AI")
  void Stun(float Duration);
  /* Will check to see if current gravity scale is < 1 if so updates gravity so enemy can be knocked backed */
  UFUNCTION(BlueprintCallable, Category = "AI")
  void GravityCheck(float NewGravityScale);
  /* Called when player uses the bark spell to bounce the enemy if the enemy does not die this is called */
  UFUNCTION(BlueprintCallable, Category = "AI")
  void BarkCollisionReset();
  /* Called when player uses the bark spell will apply a short stun and damage to enemy */
  UFUNCTION(BlueprintCallable, Category = "AI")
  void BarkDamage(float BarkStunDuration, float BarkDamage);
  /* This will instantly kill the enemy */
  UFUNCTION(BlueprintCallable, Category = "Damage")
  void KillEnemy();
  /* This function will change both Current and Max HP at runtime */
  UFUNCTION(BlueprintCallable, Category = "HP Values")
  void UpdateCurrentHP(float NewCurrent);

  UFUNCTION(BlueprintCallable, Category = "Sprite")
  void ResetSpriteColor();

  UFUNCTION(BlueprintCallable, Category = "Debuffs")
  AActor* ApplyDebuff(TSubclassOf<AMaster_Debuff_E> DebuffToApply, AActor* Target);

  UFUNCTION(BlueprintCallable, Category = "Buffs")
  AActor* ApplyBuff(TSubclassOf<AMaster_Buff_E> BuffToApply);

  /* Will look for Buff in the enemy buff array will look by ID */
  UFUNCTION(BlueprintCallable, Category = "Buffs")
  void RemoveBuffByID(AMaster_Buff_E* BuffToRemove);

  UFUNCTION(BlueprintCallable, Category = "Debuffs")
  bool FireCheck(float GunDamage, bool Heal, bool Damage, float BuffAmount);

  UFUNCTION(BlueprintPure, Category = "Debuffs")
  AMaster_Debuff_E* FindDebuffByType(EDebuffType DebuffType);

  UFUNCTION(BlueprintPure, Category = "Buffs")
  AMaster_Buff_E* FindBuffByType(EBuffType BuffType);

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

  /* Returns the MaxHP of the enemy MaxHP is the default value of CurrentHP */
  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetMaxHP();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetDefaultMaxAcceleration();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const float GetDefaultDamageToPlayer();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  const bool GetIsDead();

  UFUNCTION(BlueprintPure, Category = "Getter Functions")
  AActor* GetHitActor();

  /* Apply damage to enemy */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
  void DamageEnemy(float Damage, bool bShowText, AActor* DamageInstigator);
  virtual void DamageEnemy_Implementation(float Damage, bool bShowText, AActor* DamageInstigator);

  /* What to do after enemy is killed */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
  void OnDeath();
  virtual void OnDeath_Implementation();
  /* Is called after all default values are set in EventBeginPlay */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Utility")
  void AfterBeginPlay();
  virtual void AfterBeginPlay_Implementation();
  /* Called when enemy is knocked back */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Basic Enemy Events")
  void OnKnockBack();
  virtual void OnKnockBack_Implementation();
  /* Increase enemies speed by a set multiplier will increase both MaxWalkSpeed and MaxAcceleration */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Basic Enemy Events")
  void IncreaseSpeed(float SpeedMultiplier);
  virtual void IncreaseSpeed_Implementation(float SpeedMultiplier);
  /* Reset speed back to default speed */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Basic Enemy Events")
  void ResetSpeed();
  virtual void ResetSpeed_Implementation();
  /* Will make enemy jump into the air */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Basic Enemy Events")
  void AIJump();
  virtual void AIJump_Implementation();
  /* Reset Gravity back to default values */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Basic Enemy Events")
  void ResetGravity();
  virtual void ResetGravity_Implementation();
  /* Enemy tick replacement called on enemy timeline */
  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Basic Enemy Events")
  void EnemyTick(float TimelineValue);
  virtual void EnemyTick_Implementation(float TimelineValue);

  UFUNCTION()
  void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  UPROPERTY(BlueprintReadWrite, Category = "Buff Effects")
  AActor* CurrentLeech;

  UFUNCTION()
  void TimelineProgress(float Value);

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  FTimeline CurveTimeline;

  UPROPERTY()
  UCurveFloat* CurveFloat;

private:

  void ResetStun();

  AActor* HitActor;

  int32 ID;

  // Home location is the location the actor is the point the actor first spawned
  FVector HomeLocation;

  bool bIsStunned;

  bool bIsDead;

  float StunDuration;

  bool bIsJumping;

  float DefaultSpeed;

  float DefaultGravityScale;

  float DefaultMaxAcceleration;

  float DefaultDamageToPlayer;

  float MaxHP;

  AMaster_Debuff_E* MostRecentDebuff;
};
