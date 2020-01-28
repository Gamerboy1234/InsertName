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
#include "AIController.h"
#include "PaperWarden.h"
#include "Math/Color.h"
#include "BrainComponent.h"
#include "FloatingCombatTextComponent.h"


AMaster_Enemy::AMaster_Enemy()
{
  PrimaryActorTick.bCanEverTick = true;

  // HP Setup
  CurrentHP = 10;
  MaxHP = 10;
  ActorDespawnDelay = 2.0;
  HPBarHideDelay = 3.0;
  bCanBeStunned = true;

  DamageToPlayer = 1.0;

  bAddToKillCount = true;

  ControllerToUse = AMaster_AIController::StaticClass();
  if (!ensure(ControllerToUse != nullptr)) { return; }

  CombatTextComp = CreateDefaultSubobject<UFloatingCombatTextComponent>(TEXT("FloatingCombatTextComponent"));
  if (!ensure(CombatTextComp != nullptr)) { return; }

  EnemySpline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
  if (!ensure(EnemySpline != nullptr)) { return; }
}

// Setup default values for enemy when game starts
void AMaster_Enemy::BeginPlay()
{
  Super::BeginPlay();

  bIsDead = false;

  HomeLocation = GetActorLocation();

  ID = UGeneralFunctions::GetIDFromGamemode(this, this);

  auto MovementComp = this->GetCharacterMovement();
  DefaultSpeed = MovementComp->GetMaxSpeed();
  DefaultGravityScale = MovementComp->GravityScale;
  DefaultMaxAcceleration = MovementComp->GetMaxAcceleration();

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
    if (ControllerToUse)
    {
      auto LocalController = Cast<AMaster_AIController>(ControllerToUse->GetDefaultObject());
      UBrainComponent* BrainComp = LocalController->GetBrainComponent();
      if (BrainComp)
      {
        BrainComp->StopLogic("Stunned");
      }
    }
    FTimerHandle StunTimer;
    GetWorldTimerManager().SetTimer(StunTimer, this, &AMaster_Enemy::ResetStun, StunDuration, false);
  }
}

void AMaster_Enemy::ResetStun()
{
  if (bIsFlying)
  {
    GetCharacterMovement()->SetMovementMode(MOVE_Flying);
    if (ControllerToUse)
    {
      auto LocalController = Cast<AMaster_AIController>(ControllerToUse->GetDefaultObject());
      UBrainComponent* BrainComp = LocalController->GetBrainComponent();
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
    if (ControllerToUse)
    {
      auto LocalController = Cast<AMaster_AIController>(ControllerToUse->GetDefaultObject());
      UBrainComponent* BrainComp = LocalController->GetBrainComponent();
      if (BrainComp)
      {
        BrainComp->RestartLogic();
      }
    }
    bIsStunned = false;
  }
}

AActor* AMaster_Enemy::ApplyDebuff(TSubclassOf<AMaster_Debuff_E> DebuffToApply, FDebuffData DebuffData, AActor* Target)
{
  if (Target)
  {
    MostRecentDebuff = GetWorld()->SpawnActor<AMaster_Debuff_E>(DebuffToApply, FVector(0), FRotator(0));
    if (MostRecentDebuff)
    {
      MostRecentDebuff->StartDamageTimer(MostRecentDebuff, this, DebuffData);
      CurrentDebuffs.Add(MostRecentDebuff);
      return MostRecentDebuff;
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Was unable to apply debuff"))
      return MostRecentDebuff;
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Debuff target is not valid"))
    return nullptr;
  }
}

bool AMaster_Enemy::FireCheck(float GunDamage, bool Heal, bool Damage, float BuffAmount)
{
  AMaster_Debuff_E* FireDebuff = FindFire();
  if (FireDebuff)
  {
    if (!Heal)
    {
      float BuffedDamaged = UGeneralFunctions::TickDamage(FireDebuff->GetCurrentTickCount(), GunDamage, BuffAmount);
      DamageEnemy(BuffedDamaged);
      FireDebuff->RemoveDebuff(FireDebuff);
      return true;
    }
    else
    {
      auto Player = Cast<APaperWarden>(GetWorld()->GetFirstPlayerController());
      float HealAmount = UGeneralFunctions::TickDamage(FireDebuff->GetCurrentTickCount(), GunDamage, BuffAmount);
      Player->HealPlayer(HealAmount);
      FireDebuff->RemoveDebuff(FireDebuff);
      return true;
    }
  }
  else
  {
    return false;
  }
}

AMaster_Debuff_E* AMaster_Enemy::FindFire()
{
  AMaster_Debuff_E* LocalDebuff = nullptr;

  for (AMaster_Debuff_E* Debuff : CurrentDebuffs)
  {
    if (Debuff->DebuffType == EDebuffType::Fire)
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

void AMaster_Enemy::DamageEnemy_Implementation(float Damage)
{
  if (!bIsDead)
  {
    CurrentHP = FMath::Clamp<float>(CurrentHP - Damage, 0.0f, MaxHP);

    UE_LOG(LogTemp, Log, TEXT("Current HP is : %f"), CurrentHP)

    bTakenDamage = true;

    if (CombatTextComp)
    {
      CombatTextComp->SpawnCombatText(Damage, this);
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

      UGeneralFunctions::RemoveIDFromGamemode(this, ID, this);
      OnDeath();
    }
  }
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

void AMaster_Enemy::BarkKnockBack_Implementation(float BarkStunDuration, float LaunchVelocityMultiplier)
{
  this->Stun(BarkStunDuration);
  APaperWarden* PlayerRef = Cast<APaperWarden>(UGameplayStatics::GetPlayerPawn(this, 0));
  if (PlayerRef)
  {
    // Disable Bark Collision and reset capsule collision
    PlayerRef->BarkInnerCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlayerRef->BarkOuterCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlayerRef->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    // Calculate launch direction and velocity
    FVector LaunchDirection = FVector(0, 0, 0);
    float Size = GetActorLocation().Size();
    GetActorLocation().ToDirectionAndLength(LaunchDirection, Size);
    auto LaunchVelocity = LaunchDirection * LaunchVelocityMultiplier;
    // Launch Player away from hit enemy
    PlayerRef->LaunchCharacter(LaunchVelocity, false, false);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Unable to get PlayerRef"))
  }
}

void AMaster_Enemy::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);
  // Keep Actor on Y level 0
  UGeneralFunctions::RemoveActorsY(this, this);
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
