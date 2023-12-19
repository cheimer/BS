// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSCoreTypes.h"
#include "ItemBase.generated.h"

UCLASS()
class BS_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:
	AItemBase();

	void SetCoinAmount(int32 SetAmount) { CoinAmount = SetAmount; }
	int32 GetCoinAmount() { return CoinAmount; }
	void SetMaterialAmount(EAttackMaterial SetMaterial, int32 SetAmount);
	int32 GetMaterial(EAttackMaterial& OutMaterial);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* MeshComponent;

private:
	UFUNCTION()
	void ItemAcquire(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	int32 CoinAmount = 0;
	EAttackMaterial MaterialType;
	int32 MaterialAmount = 0;

};
