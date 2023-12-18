// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BSItemDropComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BS_API UBSItemDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBSItemDropComponent();

	void ItemDropStart(int32 DropCoin, int32 DropMaterial);

protected:
	virtual void BeginPlay() override;

	int32 GetItemRand(int32 AverageNum);


	
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class AItemBase> CoinClass;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class AItemBase> MaterialClass;

};
