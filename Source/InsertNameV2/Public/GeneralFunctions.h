// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "GeneralFunctions.generated.h"

class AMaster_Pickup;

/**
 * 
 */
UCLASS()
class INSERTNAMEV2_API UGeneralFunctions : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:

  UFUNCTION(BlueprintPure, meta = (DisplayName = "IsNumberNegative", CompactNodeTitle = "NumberNegative", Keywords = "IsNumberNegative"), Category = Math)
  static bool IsNumberNegative(float number);

  UFUNCTION(BlueprintPure, meta = (DisplayName = "TickBuff", CompactNodeTitle = "Buff", Keywords = "TickBuff"), Category = Math)
  static float TickDamage(float Tick, float GunDamage, float BuffAmount);

  UFUNCTION(BlueprintPure, meta = (DisplayName = "CalcReflectionVector", CompactNodeTitle = "CalcReflectionVector", Keywords = "CalcReflectionVector"), Category = Math)
  static FVector CalcReflectionVector(FVector VectorToReflect, FVector Normal);

  UFUNCTION(BlueprintPure, meta = (DisplayName = "LeftOrRight?", CompactNodeTitle = "LeftOrRight?", Keywords = "LeftOrRight"), Category = Game)
  static bool MouseLeftOrRight(float mouseX, float mouseY);

  UFUNCTION(BlueprintPure, meta = (DisplayName = "RandomNumberNoRepeat", CompactNodeTitle = "RandomNumber", Keywords = "RandomNumber"), Category = Math)
  static int32 RandomNumber(int32 max, int32 min);

  UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetIDFromGameMode", CompactNodeTitle = "GetID", Keywords = "GetID"), Category = "Utility")
  static int32 GetIDFromGamemode(UObject* WorldContextObject, AActor* ActorToAssign);

  UFUNCTION(BlueprintCallable, meta = (DisplayName = "AddActorToGamemode", CompactNodeTitle = "AddActorToGM", Keywords = "AddActorToGamemode"), Category = "Utility")
  static void AddPickupToGamemode(UObject* WorldContextObject, AMaster_Pickup* PickupToAdd);

  UFUNCTION(BlueprintPure, meta = (DisplayName = "GetAllActorsFromGamemode", CompactNodeTitle = "GetActorsFromGM", Keywords = "GetAllActorsFromGamemode"), Category = "Utility")
  static TArray<AActor*> GetAllActorsFromGamemode(UObject* WorldContextObject);

  UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveIDFromGamemode", CompactNodeTitle = "RemoveID", Keywords = "RemoveID"), Category = "Utility")
  static void RemoveIDFromGamemode(UObject* WorldContextObject, int32 ID, AActor* ActorToRemove);

  UFUNCTION(BlueprintCallable, meta = (DisplayName = "DisplayItemObtainMessage", CompactNodeTitle = "ItemObtain", Keywords = "DisplayItemObtainMessage"), Category = "HUD")
  static void DisplayItemObtainMessage(UObject* WorldContextObject, AMaster_Pickup* Pickup, int32 Amount);

  UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateOnScreenMessage", CompactNodeTitle = "ScreenMessage", Keywords = "CreateOnScreenMessage"), Category = "HUD")
  static void CreateOnScreenMessage(UObject* WorldContextObject, const FString& Message);

  UFUNCTION(BlueprintCallable, meta = (DisplayName = "RemoveActorsY_C++", CompactNodeTitle = "RemoveActorsY_C", Keywords = "RemoveActorsY_C"), Category = "Utility")
  static void RemoveActorsY(UObject* WorldContextObject, AActor* ActorRef);

  UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsActorAtLocation", CompactNodeTitle = "ActorAtLocation", Keywords = "IsActorAtLocation"), Category = "Utility")
  static AMaster_Pickup* IsPickupAtLocation(UObject* WorldContextObject, FVector Location);


  template <typename TAr>
  static void SetArrayElement(TAr item, TArray<TAr>& item_array, int32 index)
  {
    if (item_array.Num() - 1 < index)
      item_array.SetNum(index);

    item_array.Insert(item, index);
  }
};
