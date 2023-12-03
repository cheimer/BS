// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BSAttackTask.h"
#include "Enemy/BSEnemyCharacter.h"
#include "Enemy/BSEnemyAIController.h"

UBSAttackTask::UBSAttackTask()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBSAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	const auto TaskOwner = Cast<ABSEnemyCharacter>(Controller->GetPawn());
	if (!TaskOwner) return EBTNodeResult::Failed;

	TaskOwner->PlayAttackAnim();
	
	return EBTNodeResult::Succeeded;
}
