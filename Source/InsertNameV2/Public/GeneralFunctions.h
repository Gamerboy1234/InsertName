// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "GeneralFunctions.generated.h"

class AMaster_Pickup;
class APaperWarden;
class AWardenCameraManager;
class APaperCharacter;

/**
 *  This function library contains many useful functions for managing gameplay
 */
UCLASS()
class INSERTNAMEV2_API UGeneralFunctions : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:
  /* Checks to see if given number is >= to 0 if false it's negative */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "IsNumberNegative", CompactNodeTitle = "NumberNegative", Keywords = "IsNumberNegative"), Category = Math)
  static bool IsNumberNegative(float number);
  /* Applies a buff to GunDamage based on given Tick amount and BuffAmount (Tick * BuffAmount + 1 + GunDamage) */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "TickBuff", CompactNodeTitle = "Buff", Keywords = "TickBuff"), Category = Math)
  static float TickDamage(float Tick, float GunDamage, float BuffAmount);
  /* Calculates a reflection vector (1 * -2 * DotProduct * Normal + VectorToReflect) */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "CalcReflectionVector", CompactNodeTitle = "CalcReflectionVector", Keywords = "CalcReflectionVector"), Category = Math)
  static FVector CalcReflectionVector(FVector VectorToReflect, FVector Normal);
  /* takes in the current mouse and checks to see if the mouse X is greater than the Viewport / 2  if true mouse is on the right side of the screen else it's on the left */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "LeftOrRight?", CompactNodeTitle = "LeftOrRight?", Keywords = "LeftOrRight"), Category = Game)
  static bool MouseLeftOrRight(float mouseX, float mouseY);
  /* Generates a random number between the min and max values */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "RandomNumberNoRepeat", CompactNodeTitle = "RandomNumber", Keywords = "RandomNumber"), Category = Math)
  static int32 RandomNumber(int32 max, int32 min);
  /* Gamemode will randomly generate an ID and assign it to the given actor */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetIDFromGameMode", CompactNodeTitle = "GetID", Keywords = "GetID"), Category = "Utility")
  static int32 GetIDFromGamemode(UObject* WorldContextObject, AActor* ActorToAssign);
  /* Will try to find given ID with in the gamemode then remove it */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveIDFromGamemode", CompactNodeTitle = "RemoveID", Keywords = "RemoveID"), Category = "Utility")
  static void RemoveIDFromGamemode(UObject* WorldContextObject, int32 ID, AActor* ActorToRemove);
  /* Creates an ItemObtain widget on screen */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "DisplayItemObtainMessage", CompactNodeTitle = "ItemObtain", Keywords = "DisplayItemObtainMessage"), Category = "HUD")
  static void DisplayItemObtainMessage(UObject* WorldContextObject, AMaster_Pickup* Pickup, int32 Amount);
  /* Adds a message to the message box widget */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateOnScreenMessage", CompactNodeTitle = "ScreenMessage", Keywords = "CreateOnScreenMessage"), Category = "HUD")
  static void CreateOnScreenMessage(UObject* WorldContextObject, const FString& Message);
  /* Sets the given actors Y rotation and Y location to 0 */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveActorsY_C++", CompactNodeTitle = "RemoveActorsY_C", Keywords = "RemoveActorsY_C"), Category = "Utility")
  static void RemoveActorsY(UObject* WorldContextObject, AActor* ActorRef);
  /* Checks to see if the given pickup is at the given location */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsActorAtLocation", CompactNodeTitle = "ActorAtLocation", Keywords = "IsActorAtLocation"), Category = "Utility")
  static AMaster_Pickup* IsPickupAtLocation(UObject* WorldContextObject, FVector Location);
  /* Checks to see if the given pickup is in the current level */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "DoesPickupExistInWorld", CompactNodeTitle = "DoesPickExist", Keywords = "DoesPickupExistInWorld"), Category = "Utility")
  static AMaster_Pickup* DoesPickupExistInWorld(UObject* WorldContextObject, AMaster_Pickup* Pickup);
  /* Finds the direction vector from one position to another */
  static FVector GetUnitVector(FVector From, FVector To);
  /* Checks to if there are any enemies within the level if the amount of enemies is less than EnemyTolerance returns false */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "AreEneimesInLevel", CompactNodeTitle = "AreEneimesInLevel", Keywords = "AreEneimesInLevel"), Category = "Utility")
  static bool AreEneimesInLevel(UObject* WorldContextObject, int32 EnemyTolerance);
  /* Calls the players CheckCoolDowns functions */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "CheckPlayerCooldowns", CompactNodeTitle = "CheckCD", Keywords = "CheckPlayerCooldowns"), Category = "Utility")
  static void CheckPlayerCooldowns(UObject* WorldContextObject);
  /* Gets the Warden Camera Manager */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetWardenCameraManager", CompactNodeTitle = "GetWCM", Keywords = "GetWardenCameraManager"), Category = "Utility")
  static AWardenCameraManager* GetWardenCameraManager(UObject* WorldContextObject);
  /* Gets the player character */
  static APaperWarden* GetPlayer(UObject* WorldContextObject);
  /* Will cast to many different actor classes to determine what damage function to call */
  static bool DamageHitActor(AActor* HitActor, float Damage, AActor* Instigator, bool bShowDamageText);
  /* Will launch the given character away from the given actor */
  static void LaunchCharacterAwayFromActor(APaperCharacter* CharacterToLaunch, AActor* ActorToLaunchAwayfrom, float LaunchVelocityMultipler);
  /* Checks to see if there is a check point in the level */
  static bool IsCheckPointInLevel(UObject* WorldContextObject);
  /* Will rotate actor to face the direction of the given vector */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "RotateActorToVector", CompactNodeTitle = "RotateActorV", Keywords = "RotateActorToVector"), Category = "Utility")
  static void RotateActorToVector(AActor* ActorToRotate, FVector VectorToRotateTo);
  /* Will rotate actor to face the direction of the given actor */
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "RotateActorToActorLocation", CompactNodeTitle = "RotateActorA", Keywords = "RotateActorToActorLocation"), Category = "Utility")
  static void RotateActorToActorLocation(AActor* ActorToRotate, AActor* ActorToRotateTo);
  /* Determines if the provided characters sprite is currently moving right returns false if facing left if true character is facing right */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "IsCharacterMovingLeftOrRight", CompactNodeTitle = "SpriteMovingLeftOrRight", Keywords = "IsCharacterSpriteMovingLeftOrRight"), Category = "Utility")
  static bool IsCharacterSpriteMovingLeftOrRight(APaperCharacter* Character);
  /* Determines if the provided characters root is currently moving right returns false if facing left if true character is facing right */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "IsCharacterRootMovingLeftOrRight", CompactNodeTitle = "RootMovingLeftOrRight", Keywords = "IsCharacterRootMovingLeftOrRight"), Category = "Utility")
  static bool IsCharacterRootMovingLeftOrRight(APaperCharacter* Character);
  /* Gets the players current movement speed */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "GetPlayerMovementSpeed", CompactNodeTitle = "GetPlayerSpeed", Keywords = "GetPlayerMovementSpeed"), Category = "Utility")
  static const float GetPlayerMovementSpeed(UObject* WorldContextObject);
  /* Inverts the given rotation */
  UFUNCTION(BlueprintPure, meta = (DisplayName = "InvertRotation", CompactNodeTitle = "InvertRotation", Keywords = "InvertRotation"), Category = "Utility")
  static FRotator InvertRotation(FRotator RotationToInvert);


  /* Will insert a item into an array at a given index */
  template <typename TAr>
  static void SetArrayElement(TAr item, TArray<TAr>& item_array, int32 index)
  {
    if (item_array.Num() - 1 < index)
      item_array.SetNum(index);

    item_array.Insert(item, index);
  }
};
