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

	UFUNCTION()
	void SpawnEnemyTimer();

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	float TimeLimit = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	int EnforceCost = 1;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	TMap<EEnemyList, TSubclassOf<class ABSEnemyCharacter>> EnemyListClass;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultSetting")
	FBox2D MapSize;

	UPROPERTY(BlueprintReadOnly)
	bool isClear = false;

private:
	void TimeOver();
	FVector CalcSpawnLocation();

	float GameStartTime = -1.0f;
	float RemainTime = -1.0f;

};
