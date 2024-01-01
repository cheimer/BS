// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BSCoreTypes.h"
#include "BSGameModeBase.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEndSignature, bool);

UCLASS()
class BS_API ABSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABSGameModeBase();

	FOnGameEndSignature OnGameEndSignature;

	virtual void Tick(float DeltaTime) override;

	void PlayerDeath();
	void EnemyDeath();

	UFUNCTION(BlueprintCallable)
	float GetRemainTime();

	UFUNCTION(BlueprintCallable)
	EAttackMaterial GetMapMaterial() { return MapMaterial; }

	UFUNCTION(BlueprintCallable)
	bool IsClear() { return bClear; }

	bool IsAdvantageType(EAttackMaterial Attacker, EAttackMaterial Defender);

	UFUNCTION(BlueprintCallable)
	int32 GetEnemyNum() { return EnemyNum; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnEnemyTimer();

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	float TimeLimit = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	TMap<EEnemyList, TSubclassOf<class ABSEnemyCharacter>> EnemyListClass;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	FBox2D MapSize;

	bool bClear = false;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	int32 MaxEnemyNum = 99;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	int32 SpawnEnemyAddRound = 3;
	int32 EnemyNum = 0;

private:
	void TimeOver();
	void EnemyOver();
	FVector CalcSpawnLocation();
	void SpawnEnemyNumAdd();

	float GameStartTime = -1.0f;
	float RemainTime = -1.0f;

	EAttackMaterial MapMaterial;

};
