// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSInvenComponent.h"
#include "Player/BSPlayerCharacter.h"
#include "Item/ItemBase.h"
#include "World/BSGameModeBase.h"
#include "World/BSGameInstance.h"

UBSInvenComponent::UBSInvenComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBSInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	CoinNum = GameIns->CoinNum;
	RestoreCost = GameIns->RestoreHealthCost;
	MinRestoreCost = GameIns->MinRestoreCost;
	SetMaterialNum();

	auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->OnGameEndSignature.AddUObject(this, &UBSInvenComponent::OnGameEnd);
}

void UBSInvenComponent::SetMaterialNum()
{
	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	for (int index = 0; index < GameIns->MaterialNum.Num(); index++)
	{
		EAttackMaterial AttackMaterial = StaticCast<EAttackMaterial>(index);
		MaterialNum.Add(AttackMaterial, *GameIns->MaterialNum.Find(AttackMaterial));
	}
}

void UBSInvenComponent::OnGameEnd(bool bClear)
{
	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	if (bClear)
	{
		if (RestoreCost >= MinRestoreCost * 2)
		{
			RestoreCost /= 2.0f;
		}
		GameIns->RestoreHealthCost = RestoreCost;
		GameIns->CoinNum = CoinNum;
		SetGameInstanceMaterialNum();
	}
	else
	{
		//
	}

}

void UBSInvenComponent::SetGameInstanceMaterialNum()
{
	const auto GameIns = Cast<UBSGameInstance>(GetWorld()->GetGameInstance());
	if (!GameIns) return;

	for (auto MaterialPair : MaterialNum)
	{
		*GameIns->MaterialNum.Find(MaterialPair.Key) = MaterialPair.Value;
	}

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
