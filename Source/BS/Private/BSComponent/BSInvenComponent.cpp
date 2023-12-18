// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSInvenComponent.h"
#include "Item/ItemBase.h"

UBSInvenComponent::UBSInvenComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBSInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UBSInvenComponent::GetItem(AItemBase* const Item)
{
	Coin = Item->GetCoinAmount();
	Material = Item->GetMaterialAmount();

	Item->Destroy();

}
