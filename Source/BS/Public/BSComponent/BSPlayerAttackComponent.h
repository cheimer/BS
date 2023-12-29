// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BSCoreTypes.h"
#include "BSPlayerAttackComponent.generated.h"

class ABSPlayerWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BS_API UBSPlayerAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBSPlayerAttackComponent();

	EAttackMaterial CurrentAttackMaterial;
	float GetWeaponDamage(EAttackType AttackType);

	void ChangeMaterialSequence();

	void AttackTypeEnforce(EAttackType AttackType);
	void AttackMaterialEnforce(EAttackMaterial AttackMaterial);
	int GetAttackTypeLevel(EAttackType AttackType);
	int GetAttackMaterialLevel(EAttackMaterial AttackMaterial);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGameEnd(bool bClear);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<ABSPlayerWeapon>> PlayerWeaponClass;

	TArray<FAttackState> WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TMap<EAttackMaterial, int> AttackMaterialLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	class UDataTable* DTWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool IsDrawDebugSphere = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (EditCondition = "IsDrawDebugSphere"))
	FColor DebugSphereColor = FColor::Black;

private:
	UFUNCTION()
	void PlayerAttack(ABSPlayerWeapon* PlayerWeapon, FAttackState WeaponState);

	void SetAttackTypesTimer();

	void AttackMaterialSetting();
	void AttackTypeSetting();
	void SetGameInstanceMaterialLevel();
	void SetGameInstanceTypeLevel();

	int AttackTypeToIndex(EAttackType AttackType);

};
