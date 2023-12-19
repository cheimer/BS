// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BSCoreTypes.h"
#include "BSInvenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BS_API UBSInvenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBSInvenComponent();

	void GetItem(class AItemBase* const Item);

	int32 GetCoin() { return CoinNum; }
	int32 GetMaterialTotal();
	int GetAttackMaterialNum(EAttackMaterial AttackMaterial);

	void AttackTypeEnforce(EAttackType AttackType);
	void AttackMaterialEnforce(EAttackMaterial AttackMaterial);

	bool CanAttackTypeEnforce();
	bool CanAttackMaterialEnforce(EAttackMaterial AttackMaterial);

protected:
	virtual void BeginPlay() override;

private:
	void MaterialSetZero();

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 CoinNum = 0;

	UPROPERTY(EditAnywhere, Category = "Item")
	TMap<EAttackMaterial, int> MaterialNum;

	int EnforceCost;
};
