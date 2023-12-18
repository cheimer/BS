// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSInvenComponent.h"
#include "Player/BSPlayerCharacter.h"
#include "Item/ItemBase.h"

UBSInvenComponent::UBSInvenComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBSInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UBSInvenComponent::AutoLevelUp()
{
	if (!GetOwner() || !Cast<ABSPlayerCharacter>(GetOwner())) return;
	ABSPlayerCharacter* Player = Cast<ABSPlayerCharacter>(GetOwner());

	if (Coin >= 10)
	{
		Player->AttackTypeEnforce(EAttackType::Arrow);

		Coin -= 10;
	}

	if (Material >= 10)
	{
		Player->AttackMaterialEnforce(EAttackMaterial::Thunder);

		Material -= 10;

	}

}

void UBSInvenComponent::GetItem(AItemBase* const Item)
{
	Coin = Item->GetCoinAmount();
	Material = Item->GetMaterialAmount();

	Item->Destroy();

	UE_LOG(LogTemp, Warning, TEXT("Coin %d, Material %d"), Coin, Material);
	AutoLevelUp();
}
