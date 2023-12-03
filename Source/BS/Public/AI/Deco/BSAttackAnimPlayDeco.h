// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BSAttackAnimPlayDeco.generated.h"

/**
 * 
 */
UCLASS()
class BS_API UBSAttackAnimPlayDeco : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBSAttackAnimPlayDeco();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

};
