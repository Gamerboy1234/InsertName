// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "Master_Pickup.generated.h"

UCLASS()
class INSERTNAMEV2_API AMaster_Pickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_Pickup();

  UPROPERTY(VisibleAnywhere, Category = "Components")
  class UPaperSpriteComponent* PaperSprite;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  class UBoxComponent* BoxTrigger;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Info")
  FItemData ItemInfo;

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Events")
  void OnInteract();
  void OnInteract_Implementation();

  UFUNCTION(BlueprintCallable, Category = "Pickup Functions")
  void DestroyPickUp(AMaster_Pickup* PickupToDestroy);

  UFUNCTION(BlueprintPure, Category = "Pickup Functions")
  const int32 GetID();

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

  int32 ID;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
