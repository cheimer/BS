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

	int32 GetItemRand(int32 AverageNum);

protected:
	virtual void BeginPlay() override;

};
