// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSItemDropComponent.h"

UBSItemDropComponent::UBSItemDropComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBSItemDropComponent::BeginPlay()
{
	Super::BeginPlay();

}

/// <summary>
/// 0.4-60%, 0.4-100%, 0.2-180%
/// </summary>
/// <param name="AverageNum"></param>
/// <returns></returns>
int32 UBSItemDropComponent::GetItemRand(int32 AverageNum)
{
	int32 RandNum = FMath::RandRange(1, 10);

	if (1 <= RandNum && RandNum <= 4)
		return AverageNum * 0.6;
	else if (5 <= RandNum && RandNum <= 8)
		return AverageNum;
	else if (9 <= RandNum && RandNum <= 10)
		return AverageNum * 1.8;

	return 0;

}
