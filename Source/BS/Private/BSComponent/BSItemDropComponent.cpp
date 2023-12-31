// Fill out your copyright notice in the Description page of Project Settings.


#include "BSComponent/BSItemDropComponent.h"
#include "Item/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/BSEnemyCharacter.h"

UBSItemDropComponent::UBSItemDropComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBSItemDropComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UBSItemDropComponent::ItemDropStart(int32 DropCoin, int32 DropMaterial)
{
	int32 CoinNum = GetItemRand(DropCoin);
	int32 MaterialNum = GetItemRand(DropMaterial);
	EAttackMaterial MaterialRand = static_cast<EAttackMaterial>(FMath::RandRange(0, 5));

	if (!GetOwner()) return;

	FVector Location = GetOwner()->GetActorLocation();

	if (const auto EnemyMesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>())
	{
		FVector MeshLocation = EnemyMesh->GetRelativeLocation();
		Location.Z += MeshLocation.Z;
	}
	FTransform Transform;
	Transform.SetLocation(Location);

	int32 RandNum = FMath::RandRange(1, 10);
	if (1 <= RandNum && RandNum <= 5) // Coin Drop
	{
		auto SpawnCoin = GetWorld()->SpawnActorDeferred<AItemBase>(CoinClass, Transform);
		if (SpawnCoin)
		{
			SpawnCoin->SetCoinAmount(CoinNum);
			SpawnCoin->FinishSpawning(Transform);
		}
	}
	else if (6 <= RandNum && RandNum <= 10) // Material Drop
	{
		auto SpawnMaterial = GetWorld()->SpawnActorDeferred<AItemBase>(MaterialClass, Transform);
		if (SpawnMaterial)
		{
			SpawnMaterial->SetMaterialAmount(MaterialRand, MaterialNum);
			SpawnMaterial->FinishSpawning(Transform);
		}
	}

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
	{
		return ceil(AverageNum * 0.4f);
	}
	else if (5 <= RandNum && RandNum <= 8)
	{
		return ceil(AverageNum);
	}
	else if (9 <= RandNum && RandNum <= 10)
	{
		return ceil(AverageNum * 1.8);
	}

	return 0;

}
