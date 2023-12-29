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

	void PlayerDeath(); //temp

	UFUNCTION(BlueprintCallable)
	float GetRemainTime();

	UFUNCTION(BlueprintCallable)
	EAttackMaterial GetMapMaterial() { return MapMaterial; }

	bool IsAdvantageType(EAttackMaterial Attacker, EAttackMaterial Defender);

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

	UPROPERTY(BlueprintReadOnly)
	bool isClear = false;

private:
	void TimeOver();
	FVector CalcSpawnLocation();
	void SetMapMaterialRand();

	float GameStartTime = -1.0f;
	float RemainTime = -1.0f;

	EAttackMaterial MapMaterial;

};
