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
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<ABSPlayerWeapon>> PlayerWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<FAttackState> WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TMap<EAttackMaterial, int> AttackMaterialLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool IsDrawDebugSphere = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (EditCondition = "IsDrawDebugSphere"))
	FColor DebugSphereColor = FColor::Black;

private:
	UFUNCTION()
	void PlayerAttack(ABSPlayerWeapon* PlayerWeapon, FAttackState WeaponState);

	void SetAttackTypesTimer();
	void AttackMaterialSetting();
	int AttackTypeToIndex(EAttackType AttackType);
};
