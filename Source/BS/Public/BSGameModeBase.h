// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BSCoreTypes.h"
#include "BSGameModeBase.generated.h"


UCLASS()
class BS_API ABSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABSGameModeBase();

	virtual void Tick(float DeltaTime) override;

	int GetEnforceCost() { return EnforceCost; }	

	UFUNCTION(BlueprintCallable)
	float GetRemainTime();

	void PlayerDeath();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	float TimeLimit = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	int EnforceCost = 1;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	TMap<EEnemyList, TSubclassOf<class ABSEnemyCharacter>> EnemyListClass;

	UFUNCTION()
	void SpawnEnemyTimer();

private:
	void TimeOver();

	FVector CalcSpawnLocation();

	float GameStartTime = -1.0f;
	float RemainTime = -1.0f;

	// 사망시 호출, 적 스폰 비율 -> 시간 당 소환(0.5 - 2초마다 1번 스폰)

};
