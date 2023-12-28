// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSInvenComponent.h"
#include "Player/BSPlayerCharacter.h"
#include "Item/ItemBase.h"
#include "BSGameModeBase.h"

UBSInvenComponent::UBSInvenComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBSInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	MaterialSetZero();

	auto BSGameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	check(BSGameMode);

}

void UBSInvenComponent::MaterialSetZero()
{
	MaterialNum.Add(EAttackMaterial::Dark, 0);
	MaterialNum.Add(EAttackMaterial::Shine, 0);
	MaterialNum.Add(EAttackMaterial::Fire, 0);
	MaterialNum.Add(EAttackMaterial::Ice, 0);
	MaterialNum.Add(EAttackMaterial::Water, 0);
	MaterialNum.Add(EAttackMaterial::Thunder, 0);
}

void UBSInvenComponent::GetItem(AItemBase* const Item)
{
	CoinNum += Item->GetCoinAmount();

	EAttackMaterial GetMaterialType;
	int GetMaterialNum = Item->GetMaterial(GetMaterialType);

	Item->Destroy();

	*MaterialNum.Find(GetMaterialType) += GetMaterialNum;

}

int32 UBSInvenComponent::GetMaterialTotal()
{
	int32 total = 0;
	for (auto Index : MaterialNum)
	{
		total += Index.Value;
	}

	return total;
}

int UBSInvenComponent::GetAttackMaterialNum(EAttackMaterial AttackMaterial)
{
	return MaterialNum[AttackMaterial];
}

void UBSInvenComponent::AttackTypeEnforce(EAttackType AttackType)
{
	CoinNum -= EnforceCost;
}

void UBSInvenComponent::AttackMaterialEnforce(EAttackMaterial AttackMaterial)
{
	*MaterialNum.Find(AttackMaterial) -= EnforceCost;
}

bool UBSInvenComponent::CanAttackTypeEnforce()
{
	if (CoinNum >= EnforceCost)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBSInvenComponent::CanAttackMaterialEnforce(EAttackMaterial AttackMaterial)
{
	if (MaterialNum[AttackMaterial] >= EnforceCost)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UBSInvenComponent::RerollMaterial()
{
	int32 Total = GetMaterialTotal() * RerollRate;

	TArray<int32> MaterialDistribute;

	for (int i = 0; i < MaterialNum.Num() - 1; i++)
	{
		MaterialDistribute.Add(FMath::RandRange(0, Total));
	}
	MaterialDistribute.Add(0);
	MaterialDistribute.Add(Total);
	MaterialDistribute.Sort();

	for (int i = 1; i < MaterialDistribute.Num(); i++)
	{
		int32 NewMaterialNum = MaterialDistribute[i] - MaterialDistribute[i - 1];
		*MaterialNum.Find(static_cast<EAttackMaterial>(i - 1)) = NewMaterialNum;
	}

}

bool UBSInvenComponent::CoinUseRestoreHealth()
{
	if (CoinNum < RestoreCost)
	{
		return false;
	}
	else
	{
		CoinNum -= RestoreCost;
		RestoreCost *= RestoreRate;
		return true;
	}

}
