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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EEnemyList, int32> EnemyList;

	UFUNCTION(BlueprintCallable)
	void SetEnemyList(EEnemyList Enemy, int32 EnemyNum);

private:
	void EnemyListDefaultSetting();

};
