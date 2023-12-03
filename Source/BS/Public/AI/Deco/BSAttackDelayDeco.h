// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Cooldown.h"
#include "BSAttackDelayDeco.generated.h"


UCLASS()
class BS_API UBSAttackDelayDeco : public UBTDecorator_Cooldown
{
	GENERATED_BODY()

public:
	UBSAttackDelayDeco();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};

