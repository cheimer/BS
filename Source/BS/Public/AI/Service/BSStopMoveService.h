// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BSStopMoveService.generated.h"

/**
 * 
 */
UCLASS()
class BS_API UBSStopMoveService : public UBTService
{
	GENERATED_BODY()

public:
	UBSStopMoveService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool PlayerInRange(UBehaviorTreeComponent& OwnerComp);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PlayerActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

};
