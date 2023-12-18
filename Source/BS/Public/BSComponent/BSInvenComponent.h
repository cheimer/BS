// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BSInvenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BS_API UBSInvenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBSInvenComponent();

	void GetItem(class AItemBase* const Item);

protected:
	virtual void BeginPlay() override;

	void AutoLevelUp();

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 Coin = 0;

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 Material = 0;

	
};
