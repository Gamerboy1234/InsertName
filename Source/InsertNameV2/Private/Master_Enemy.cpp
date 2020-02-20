// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Blueprint.h"
#include "Master_AIController.h"
#include "SideScrollerGamemode.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GeneralFunctions.h"
#include "PaperFlipbookComponent.h"
#include "Components/SplineComponent.h"
#include "Master_Debuff_E.h"
#include "Master_Buff_E.h"
#include "WarlustEffectBase.h"
#include "AIController.h"
#include "PaperWarden.h"
#include "Master_Buff_E.h"
#include "InsertNameV2.h"
#include "Math/Color.h"
#include "BrainComponent.h"
#include "FloatingCombatTextComponent.h"


AMaster_Enemy::AMaster_Enemy()
{
  PrimaryActorTick.bCanEverTick = true;

  // HP Setup
  CurrentHP = 10;
  ActorDespawnDelay = 2.0;
  bCanBeStunned = true;

  DamageToPlayer = 1.0;

  bAddToKillCount = true;

  CombatTextComp = CreateDefaultSubobject<UFloatingCombatTextComponent>(TEXT("FloatingCombatTextComponent"));
  if (!ensure(CombatTextComp != nullptr)) { return; }

  EnemySpline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
  if (!ensure(EnemySpline != nullptr)) { return; }
  EnemySpline->SetupAttachment(RootComponent);
}

// Setup default values for enemy when game starts
void AMaster_Enemy::BeginPlay()
{
  Super::BeginPlay();

  bIsDead = false;

  MaxHP = CurrentHP;

  HomeLocation = GetActorLocation();

  ID = UGeneralFunctions::GetIDFromGamemode(this, this);

  auto MovementComp = this->GetCharacterMovement();
  DefaultSpeed = MovementComp->GetMaxSpeed();
  DefaultGravityScale = MovementComp->GravityScale;
  DefaultMaxAcceleration = MovementComp->GetMaxAcceleration();

  GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMaster_Enemy::OnCompHit);

  // All defaults values are now set the enemy can now do stuff
  AfterBeginPlay();
}

void AMaster_Enemy::Stun(float Duration)
{
  if (bCanBeStunned)
  {
    StunDuration = Duration;
    bIsStunned = true;
    GetCharacterMovement()->StopMovementImmediately();
    if (bUseBT)
    {
      UBrainComponent* BrainComp = AIControllerClass->GetDefaultObject<AAIController>()->GetBrainComponent();
      if (BrainComp)
      {
        BrainComp->StopLogic("Stunned");
      }
    }
    FTimerHandle StunTimer;
    GetWorldTimerManager().SetTimer(StunTimer, this, &AMaster_Enemy::ResetStun, StunDuration, false);
  }
  else
  {
    UGeneralFunctions::CreateOnScreenMessage(this, TEXT("This enemy can't be stunned"));
  }
}

void AMaster_Enemy::GravityCheck(float NewGravityScale)
{
  if (GetCharacterMovement()->GravityScale < 0.5f)
  {
    GetCharacterMovement()->GravityScale = NewGravityScale;
  }
}

void AMaster_Enemy::BarkCollisionReset()
{
  APaperWarden* PlayerRef = Cast<APaperWarden>(UGameplayStatics::GetPlayerPawn(this, 0));
  if (PlayerRef)
  {
    if (CurrentHP > 0.00f)
    {
      // Disable Bark Collision and reset capsule collision
      PlayerRef->BarkInnerCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
      PlayerRef->BarkOuterCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
      PlayerRef->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Unable to get PlayerRef"))
  }
}

void AMaster_Enemy::BarkDamage(float BarkStunDuration, float BarkDamage)
{
  auto PlayerRef = UGameplayStatics::GetPlayerCharacter(this, 0);
  Stun(BarkStunDuration);
  DamageEnemy(BarkDamage, true, PlayerRef);
}

void AMaster_Enemy::ResetStun()
{
  if (bIsFlying)
  {
    GetCharacterMovement()->SetMovementMode(MOVE_Flying);
    if (bUseBT)
    {
      UBrainComponent* BrainComp = AIControllerClass->GetDefaultObject<AAIController>()->GetBrainComponent();
      if (BrainComp)
      {
        BrainComp->RestartLogic();
      }
    }
    bIsStunned = false;
  }
  else
  {
    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
    if (bUseBT)
    {
      UBrainComponent* BrainComp = AIControllerClass->GetDefaultObject<AAIController>()->GetBrainComponent();
      if (BrainComp)
      {
        BrainComp->RestartLogic();
      }
    }
    bIsStunned = false;
  }
}

AActor* AMaster_Enemy::ApplyDebuff(TSubclassOf<AMaster_Debuff_E> DebuffToApply, AActor* Target)
{
  if (Target)
  {
    MostRecentDebuff = GetWorld()->SpawnActor<AMaster_Debuff_E>(DebuffToApply, FVector(0), FRotator(0));
    if (MostRecentDebuff)
    {
      MostRecentDebuff->StartDamageTimer(MostRecentDebuff, this);
      return MostRecentDebuff;
    }
    else
    {
      UE_LOG(LogMasterEnemy, Error, TEXT("Was unable to apply Debuff"))
      return nullptr;
    }
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Debuff target is not valid"))
    return nullptr;
  }
}

AActor* AMaster_Enemy::ApplyBuff(TSubclassOf<AMaster_Buff_E> BuffToApply)
{
  AMaster_Buff_E* Buff = GetWorld()->SpawnActor<AMaster_Buff_E>(BuffToApply, FVector(0), FRotator(0));
  if (Buff)
  {
    Buff->SetUpBuff(this, Buff);
    CurrentBuffs.Add(Buff);
    return Buff;
  }
  else
  {
    UE_LOG(LogMasterEnemy, Error, TEXT("Was unable to apply Buff"))
    return nullptr;
  }
}

bool AMaster_Enemy::FireCheck(float GunDamage, bool Heal, bool Damage, float BuffAmount)
{
  AMaster_Debuff_E* FireDebuff = FindDebuffByType(EDebuffType::Fire);
  auto PlayerRef = UGameplayStatics::GetPlayerCharacter(this, 0);

  if (FireDebuff)
  {
    if (!Heal)
    {
      float BuffedDamaged = UGeneralFunctions::TickDamage(FireDebuff->GetCurrentTickCount(), GunDamage, BuffAmount);
      DamageEnemy(BuffedDamaged, true, PlayerRef);
      FireDebuff->RemoveDebuff(FireDebuff, this);
      return true;
    }
    else
    {
      auto Player = Cast<APaperWarden>(GetWorld()->GetFirstPlayerController());
      float HealAmount = UGeneralFunctions::TickDamage(FireDebuff->GetCurrentTickCount(), GunDamage, BuffAmount);
      Player->HealPlayer(HealAmount);
      FireDebuff->RemoveDebuff(FireDebuff, this);
      return true;
    }
  }
  else
  {
    return false;
  }
}

AMaster_Debuff_E* AMaster_Enemy::FindDebuffByType(EDebuffType DebuffType)
{
  AMaster_Debuff_E* LocalDebuff = nullptr;

  for (AMaster_Debuff_E* Debuff : CurrentDebuffs)
  {
    if (Debuff->DebuffType == DebuffType)
    {
      LocalDebuff = Debuff;
      break;
    }
    else
    {
      LocalDebuff = nullptr;
      continue;
    }
  }
  return LocalDebuff;
}

AMaster_Buff_E* AMaster_Enemy::FindBuffByType(EBuffType BuffType)
{
  AMaster_Buff_E* LocalBuff = nullptr;

  for (AMaster_Buff_E* Buff : CurrentBuffs)
  {
    if (Buff->BuffType == BuffType)
    {
      LocalBuff = Buff;
      break;
    }
    else
    {
      LocalBuff = nullptr;
      continue;
    }
  }
  return LocalBuff;
}

void AMaster_Enemy::DamageEnemy_Implementation(float Damage, bool bShowText, AActor* DamageInstigator)
{
  if (!bIsDead)
  {
    CurrentHP = FMath::Clamp<float>(CurrentHP - Damage, 0.0f, MaxHP);

    bTakenDamage = true;

    if (bShowText && Damage > 0)
    {
      if (CombatTextComp)
      {
        CombatTextComp->SpawnCombatText(Damage, this);
      }
    }

    if (CurrentHP <= 0.0f)
    {
      bIsDead = true;

      SetActorEnableCollision(false);

      if (bAddToKillCount)
      {
        auto PlayerCharacter = Cast<APaperWarden>(UGameplayStatics::GetPlayerCharacter(this, 0));
        PlayerCharacter->AddToKillCount(1);
      }

      if (WarlustEffect)
      {
        WarlustEffect->RemoveLine();
      }

      UGeneralFunctions::RemoveIDFromGamemode(this, ID, this);
      OnDeath();
    }
  }
}

void AMaster_Enemy::KillEnemy()
{
  this->DamageEnemy(MaxHP, false, this);
}

void AMaster_Enemy::UpdateCurrentHP(float NewCurrent)
{
  CurrentHP = NewCurrent;
  MaxHP = NewCurrent;
}

void AMaster_Enemy::OnDeath_Implementation()
{
  // Despawn the actor after a set delay
  SetLifeSpan(ActorDespawnDelay);
}

void AMaster_Enemy::AfterBeginPlay_Implementation()
{
  // for use in children
}

void AMaster_Enemy::OnKnockBack_Implementation()
{
  this->Stun(0.01f);
  ResetSpeed();
}

void AMaster_Enemy::IncreaseSpeed_Implementation(float SpeedMultiplier)
{
  float NewSpeed = GetCharacterMovement()->MaxWalkSpeed * SpeedMultiplier;
  GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
  float NewAccleration = GetCharacterMovement()->MaxAcceleration * SpeedMultiplier;
  GetCharacterMovement()->MaxAcceleration = NewAccleration;
}

void AMaster_Enemy::ResetSpeed_Implementation()
{
  GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
  GetCharacterMovement()->MaxAcceleration = DefaultMaxAcceleration;
}

void AMaster_Enemy::AIJump_Implementation()
{
  this->Jump();
}

void AMaster_Enemy::ResetGravity_Implementation()
{
  GetCharacterMovement()->GravityScale = DefaultGravityScale;
}

void AMaster_Enemy::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  APaperWarden* PlayerRef = Cast<APaperWarden>(UGameplayStatics::GetPlayerPawn(this, 0));

  if (PlayerRef)
  {
    if (OtherActor && HitComp && PlayerRef->bWasBarkUsed)
    {
      HitActor = HitComp->GetOwner();
    }

    if (PlayerRef->bFlameMagnetActive)
    {
      PlayerRef->Damage(DamageToPlayer, true, this);
      PlayerRef->bFlameMagnetActive = false;
    }
  }
}

void AMaster_Enemy::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);
  // Keep Enemy on Y level 0
  UGeneralFunctions::RemoveActorsY(this, this);
}

void AMaster_Enemy::ResetSpriteColor()
{
  FLinearColor DefaultColor = FLinearColor(1, 1, 1, 1);
  this->GetSprite()->SetSpriteColor(DefaultColor);
}

// Getter Functions for private var's 
const FVector AMaster_Enemy::GetHomeLocation()
{
  return HomeLocation;
}

const int32 AMaster_Enemy::GetID()
{
  return ID;
}

const bool AMaster_Enemy::GetTakenDamage()
{
  return bTakenDamage;
}

const bool AMaster_Enemy::GetIsStunned()
{
  return bIsStunned;
}

const float AMaster_Enemy::GetDefaultSpeed()
{
  return DefaultSpeed;
}

const float AMaster_Enemy::GetDefaultGravityScale()
{
  return DefaultGravityScale;
}

const float AMaster_Enemy::GetDefaultMaxAcceleration()
{
  return DefaultMaxAcceleration;
}

const bool AMaster_Enemy::GetIsDead()
{
  return bIsDead;
}

const float AMaster_Enemy::GetMaxHP()
{
  return MaxHP;
}

AActor* AMaster_Enemy::GetHitActor()
{
  return HitActor;
}
