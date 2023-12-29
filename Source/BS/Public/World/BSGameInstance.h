// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BSCoreTypes.h"
#include "BSGameInstance.generated.h"


UCLASS()
class BS_API UBSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBSGameInstance();

	UFUNCTION(BlueprintCallable)
	void SetEnemyList(EEnemyList Enemy, int32 EnemyNum);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EEnemyList, int32> EnemyList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MapLevel;
	EAttackMaterial MapMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EAttackType, int32> TypeLevel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EAttackMaterial, int32> MaterialLevel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EAttackMaterial, int32> MaterialNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CoinNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 RestoreHealthCost;

	float PlayerCurrentHealth;
	EAttackMaterial CurrentMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PlayerMaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MinRestoreCost = 10;

private:
	void EnemyListDefaultSetting();
	void TypeLevelDefaultSetting();
	void MaterialLevelDefaultSetting();
	void MaterialNumDefaultSetting();

};
